
#pragma once

#ifndef __xe_sg_perspectivecamera_hpp__
#define __xe_sg_perspectivecamera_hpp__

#include <xe/sg/Camera.hpp>

namespace xe { namespace sg {

    class PerspectiveCamera : public xe::sg::Camera {
    public:
        PerspectiveCamera();
    
        virtual ~PerspectiveCamera();
    
        virtual xe::Matrix4f computeView() const;
    
        virtual xe::Matrix4f computeProj() const;
    
        virtual xe::Rectf getViewport() const override;
    
    public:
        xe::Vector3f position = xe::Vector3f(0.0f, 1.5f, 3.5f);
        xe::Vector3f lookat = xe::Vector3f(0.0f, 0.0f, 0.0f);
        xe::Vector3f up = xe::Vector3f(0.0f, 1.0f, 0.0f);
    
        float fov = xe::rad(60.0f);
        float aspect = 4.0f/3.0f;
        float znear = 0.1f;
        float zfar = 100.0f;
    
        xe::Rectf viewport;
    };
}}

#endif
