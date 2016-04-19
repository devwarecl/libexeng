
#include "SoftwarePipeline.hpp"

#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/gfx/Vertex.hpp>
#include <xe/gfx/MeshSubsetGeneratorPlane.hpp>
#include <xe/sg/Light.hpp>
#include <xe/sg/Camera.hpp>

namespace xe { namespace sg {

    struct SoftwarePipeline::Private {
        xe::Matrix4f model = xe::identity<float, 4>();
        xe::Matrix4f view = xe::identity<float, 4>();
        xe::Matrix4f proj = xe::identity<float, 4>();
        xe::Vector4f color = xe::Vector4f(0.0f, 0.0f, 0.0f, 1.0f);

		xe::gfx::MaterialFormat materialFormat;
		xe::gfx::VertexFormat vertexFormat;

        xe::gfx::GraphicsDriver *driver = nullptr;
        xe::gfx::TexturePtr screenTexture;
        xe::gfx::MeshPtr screenMesh;
        xe::gfx::MaterialPtr screenMaterial;
        xe::gfx::MaterialFormat screenMF;
        xe::gfx::VertexFormat screenVF;
        xe::gfx::ShaderProgramPtr screenShader;

        xe::Vector4ub *renderTargetSurface = nullptr;

        std::vector<xe::sg::Ray> rays;
        std::vector<xe::sg::IntersectInfo> synthetizationData;
        
        int computeOffset(const xe::Vector2i &pixel, const xe::Vector2i &size) {
		    assert(pixel.x >= 0);
		    assert(pixel.y >= 0);
		    assert(pixel.x < size.x);
		    assert(pixel.y < size.y);

            return pixel.y*size.x + pixel.x;
        }
    
        xe::Vector2i computePixel(const int offset, const xe::Vector2i &size) {
            assert(offset >= 0);
            assert(offset < size.x*size.y);
        
            const int x = offset / size.y;
            const int y = offset % size.x;
        
            return xe::Vector2i(x, y);
        }
    
        xe::sg::Ray castRay (
            const xe::Vector2f &coordsf, 
            const xe::Vector2f &sizef, 
            const xe::Vector3f &cam_pos, 
            const xe::Vector3f &cam_up, 
            const xe::Vector3f &cam_dir, 
            const xe::Vector3f &cam_right) {
		
		    // normalized coordinates
		    const xe::Vector2f nc = (coordsf / (sizef - Vector2f(1.0f, 1.0f)) ) - Vector2f(0.5f, 0.5f);
		    const xe::Vector3f image_point = nc.x * cam_right + nc.y * cam_up + cam_pos + cam_dir;
    
		    const xe::sg::Ray ray = {
			    cam_pos, 
			    xe::normalize(image_point - cam_pos)
		    };
        
		    return ray;
	    }    
    
        xe::sg::IntersectInfo selectResult(const xe::sg::IntersectInfo &first, const xe::sg::IntersectInfo &candidate) {
            if (!candidate.intersect) {
                return first;
            }
        
            if (candidate.distance < first.distance) {
                return candidate;
            }
    
            return first;
	    }
    
        void generateRays (
            std::vector<xe::sg::Ray> &rays,
            const xe::Vector2i &size, 
            const xe::Vector3f &cam_pos, 
            const xe::Vector3f &cam_up, 
            const xe::Vector3f &cam_dir, 
            const xe::Vector3f &cam_right) {
            
            assert(size.x > 0);
            assert(size.y > 0);
            assert(rays.size() == size.x*size.y);
        
            const xe::Vector2f sizef = (xe::Vector2f)size;
            const int rayCount = size.x * size.y;
            
            for (int i=0; i<rayCount; i++) {
                xe::Vector2i coord = computePixel(i, size);
                xe::Vector2f coordf = static_cast<xe::Vector2f>(coord);
                xe::sg::Ray ray = castRay(coordf, sizef, cam_pos, cam_up, cam_dir, cam_right);
                
                rays[i] = ray;
            }
        }
        
        void fillSurface(const int size, const xe::Vector4ub &color) {
            assert(size > 0);
        
			xe::Vector4ub *pixels = renderTargetSurface;

            for (int i=0; i<size; i++) {   
                *pixels++ = color;
            }
        }
    };

    SoftwarePipeline::SoftwarePipeline(xe::gfx::GraphicsDriver *driver) {
        assert(driver);
        
        // shader source code
        std::string vshader = 
    R"(
    #version 330
    layout(location=0) in vec2 coord;
    layout(location=1) in vec2 tex_coord;
    
    out vec2 uv;
    
    void main() {
        uv = tex_coord;
        gl_Position = vec4(coord, 0.0f, 1.0f);
    }
    )";
    
        std::string fshader = 
    R"(#version 330
    
    in vec2 uv;
    out vec4 color;
    
    uniform sampler2D screenTexture;
    
    void main() {
        // color = texture(screenTexture, uv);    
        color = vec4(0.0, 0.0, 0.0, 1.0);
    })";

        impl = new SoftwarePipeline::Private();
		assert(impl);
        impl->driver = driver;

        // create custom material format
		impl->screenMF = xe::gfx::MaterialFormat({}, {{"screenTexture"}});

		// backbuffer texture
        impl->screenTexture = impl->driver->createTexture (
            driver->getDisplayMode().size, 
            xe::gfx::PixelFormat::R8G8B8A8
        );

		// backbuffer material
        impl->screenMaterial = std::make_unique<xe::gfx::Material>(&impl->screenMF);
        impl->screenMaterial->getLayer(0)->texture = impl->screenTexture.get();
        
		// generate custom vertex format
        impl->screenVF.fields[0] = {xe::gfx::VertexAttrib::Position, 2, xe::DataType::Float32};
        impl->screenVF.fields[1] = {xe::gfx::VertexAttrib::TexCoord, 2, xe::DataType::Float32};

		// generate backbuffer plane mesh
        xe::gfx::MeshSubsetGeneratorPlane generator(driver);
        xe::gfx::MeshSubsetPtr subset = generator.generate({&impl->screenVF});
        subset->setMaterial(impl->screenMaterial.get());
        impl->screenMesh = std::make_unique<xe::gfx::Mesh>(std::move(subset));

        // generate custom shaders
        impl->screenShader = impl->driver->getModernModule()->createShaderProgram(vshader, fshader);
        driver->getModernModule()->setShaderProgram(impl->screenShader.get());

		// create the vertex and material formats for normal rendering (phong based ray tracing)
		impl->vertexFormat = xe::gfx::StandardVertex::getFormat();

		impl->materialFormat = xe::gfx::MaterialFormat({
			{"ambient", xe::DataType::Float32, 4}, 
			{"diffuse", xe::DataType::Float32, 4}, 
			{"specular", xe::DataType::Float32, 4}, 
			{"emissive", xe::DataType::Float32, 4}, 
			{"shininess", xe::DataType::Float32, 1},
		});
    }
    
    SoftwarePipeline::~SoftwarePipeline() {
        delete impl;
    }
    
    void SoftwarePipeline::beginFrame(const xe::Vector4f &color) {
        assert(impl);

		xe::Vector3i size = impl->screenTexture->getSize();

        impl->color = color;
		impl->driver->beginFrame({1.0f, 1.0f, 1.0f, 1.0f} , xe::gfx::ClearFlags::Color);

		auto data = impl->screenTexture->getBuffer()->lock(BufferUsage::ReadWrite);

		impl->renderTargetSurface = (xe::Vector4ub*)data;
		impl->fillSurface(size.x*size.y, (color * 255.0f));
    }
    
    void SoftwarePipeline::endFrame() {
        assert(impl);

		impl->renderTargetSurface = nullptr;
		impl->screenTexture->getBuffer()->unlock();

		impl->driver->render(impl->screenMesh.get());
        impl->driver->endFrame();
    }
    
    void SoftwarePipeline::render(xe::sg::Light *light) {
        //! TODO: Add custom code
        assert(impl);
        assert(light);
    }
    
    void SoftwarePipeline::render(xe::sg::Camera *camera) {
        assert(impl);
        assert(camera);
        impl->view = camera->computeView();
        impl->proj = camera->computeProj();
    }
    
    void SoftwarePipeline::render(xe::sg::Geometry *geometry) {
        //! TODO: Add custom code
        assert(impl);
		assert(geometry);
    }
    
    void SoftwarePipeline::render(xe::gfx::Mesh *mesh) {
        //! TODO: Add custom code
        assert(impl);
		assert(mesh);
    }
    
    void SoftwarePipeline::setModel(const xe::Matrix4f &model) {
        assert(impl);

        impl->model = model;
    }

	const xe::gfx::VertexFormat* SoftwarePipeline::getVertexFormat() const {
		return &impl->vertexFormat;
	}
    
    const xe::gfx::MaterialFormat* SoftwarePipeline::getMaterialFormat() const {
		return &impl->materialFormat;
	}
}}
