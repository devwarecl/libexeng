/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
#define __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__

#include <exeng/Timer.hpp>
#include <exeng/framework/Application.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/graphics/ShaderLibrary.hpp>
#include <exeng/graphics/MaterialLibrary.hpp>
#include <exeng/graphics/Mesh.hpp>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/scenegraph/AssetsLibrary.hpp>
#include <exeng/scenegraph/GeometryLibrary.hpp>
#include <exeng/scenegraph/SceneRenderer.hpp>

namespace exeng { namespace framework {
    /**
     * @brief Basic application skeleton for graphics-based multimedia applications.
     */
    class EXENGAPI GraphicsApplication : public Application {
    public:
		GraphicsApplication();
		virtual ~GraphicsApplication();
        
        virtual int run(int argc, char **argv) override;

		virtual ApplicationStatus::Enum getApplicationStatus() const override;

		exeng::graphics::GraphicsDriver* getGraphicsDriver();
		exeng::graphics::ShaderLibrary* getShaderLibrary();
		exeng::scenegraph::GeometryLibrary* getGeometryLibrary();
		exeng::graphics::MaterialLibrary* getMaterialLibrary();
		exeng::scenegraph::AssetLibrary* getAssetLibrary();
		exeng::scenegraph::Scene* getScene();
		exeng::scenegraph::SceneRenderer* getSceneRenderer();

		const exeng::graphics::GraphicsDriver* getGraphicsDriver() const;
		const exeng::graphics::ShaderLibrary* getShaderLibrary() const;
		const exeng::scenegraph::GeometryLibrary* getGeometryLibrary() const;
		const exeng::graphics::MaterialLibrary* getMaterialLibrary() const;
		const exeng::scenegraph::AssetLibrary* getAssetLibrary() const;
		const exeng::scenegraph::Scene* getScene() const;
		const exeng::scenegraph::SceneRenderer* getSceneRenderer() const;

    protected:
		void setExitCode(int code);
        int getExitCode() const;

		void setApplicationStatus(ApplicationStatus::Enum status);

		virtual BufferPtr getAssetsXmlData() = 0;
		virtual exeng::graphics::GraphicsDriverPtr createGraphicsDriver() = 0;
		virtual exeng::scenegraph::AssetLibraryPtr createAssetLibrary() = 0;
		virtual exeng::scenegraph::SceneRendererPtr createSceneRenderer(exeng::graphics::GraphicsDriver *graphicsDriver) = 0;

		virtual void pollEvents();
        virtual void update(float frameTime);
		virtual void render();

        // utility render functions
        void renderMesh(const exeng::graphics::Mesh* mesh);

		/**
		 * Post initialization routine
		 */
		virtual bool onInitialize() = 0;

	private:
		void initialize(int argc, char **argv);
		void terminate();

	private:
		struct Private;
		Private *impl = nullptr;
    };
}}

#endif // __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
