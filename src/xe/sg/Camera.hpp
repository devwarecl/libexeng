/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_CAMERA_HPP__
#define __EXENG_SCENEGRAPH_CAMERA_HPP__

#include <xe/Object.hpp>
#include <xe/Matrix.hpp>
#include <xe/Boundary.hpp>
#include <xe/sg/Renderable.hpp>

namespace xe { namespace sg {
    /**
     * @brief Camera interface
     */
    class EXENGAPI Camera : public Object, public Renderable {
    public:
        virtual ~Camera();

		virtual Matrix4f computeView() const = 0;
		virtual Matrix4f computeProj() const = 0;

		virtual Rectf getViewport() const = 0;

		virtual void renderWith(xe::sg::Renderer *renderer) override;
    };

	typedef std::unique_ptr<Camera> CameraPtr;
}}

#endif // __EXENG_SCENEGRAPH_CAMERA_HPP__
