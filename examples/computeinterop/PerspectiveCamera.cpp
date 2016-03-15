
#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera() {}

PerspectiveCamera::~PerspectiveCamera() {}

xe::Matrix4f PerspectiveCamera::computeView() const {
	return xe::lookat(position, lookat, up);
}

xe::Matrix4f PerspectiveCamera::computeProj() const {
	return xe::perspective(fov, aspect, znear, zfar);
}

xe::Rectf PerspectiveCamera::getViewport() const {
	return viewport;
}
