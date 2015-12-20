/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
#define __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__

#include <xe/Timer.hpp>
#include <xe/fw/Application.hpp>
#include <xe/gfx/GraphicsDriver.hpp>
#include <xe/gfx/ShaderLibrary.hpp>
#include <xe/gfx/MaterialLibrary.hpp>
#include <xe/gfx/Mesh.hpp>
#include <xe/sg/Scene.hpp>
#include <xe/sg/AssetsLibrary.hpp>
#include <xe/sg/GeometryLibrary.hpp>
#include <xe/sg/SceneRenderer.hpp>

namespace xe { namespace fw {
    /**
     * @brief Basic application skeleton for graphics-based multimedia applications.
     */
    class EXENGAPI GraphicsApplication : public Application {
    public:
		GraphicsApplication();
		virtual ~GraphicsApplication();
        
        virtual int run(int argc, char **argv) override;

		virtual ApplicationStatus::Enum getApplicationStatus() const override;

		xe::gfx::GraphicsDriver* getGraphicsDriver();
		xe::gfx::ShaderLibrary* getShaderLibrary();
		xe::sg::GeometryLibrary* getGeometryLibrary();
		xe::gfx::MaterialLibrary* getMaterialLibrary();
		xe::sg::AssetLibrary* getAssetLibrary();
		xe::sg::Scene* getScene();
		xe::sg::SceneRenderer* getSceneRenderer();

		const xe::gfx::GraphicsDriver* getGraphicsDriver() const;
		const xe::gfx::ShaderLibrary* getShaderLibrary() const;
		const xe::sg::GeometryLibrary* getGeometryLibrary() const;
		const xe::gfx::MaterialLibrary* getMaterialLibrary() const;
		const xe::sg::AssetLibrary* getAssetLibrary() const;
		const xe::sg::Scene* getScene() const;
		const xe::sg::SceneRenderer* getSceneRenderer() const;

    protected:
		void setExitCode(int code);
        int getExitCode() const;

		void setApplicationStatus(ApplicationStatus::Enum status);

		virtual BufferPtr getAssetsXmlData() = 0;
		virtual xe::gfx::GraphicsDriverPtr createGraphicsDriver() = 0;
		virtual xe::sg::AssetLibraryPtr createAssetLibrary() = 0;
		virtual xe::sg::SceneRendererPtr createSceneRenderer(xe::gfx::GraphicsDriver *graphicsDriver) = 0;

		virtual void pollEvents();
        virtual void update(float frameTime);
		virtual void render();

        // utility render functions
        void renderMesh(const xe::gfx::Mesh* mesh);

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
