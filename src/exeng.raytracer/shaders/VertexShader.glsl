
#version 330 \n"

// vertex attributes
layout(location=0) in vec4 position; 
layout(location=1) in vec2 texCoord; 

// transformations
uniform mat4 WorldTransform; 
uniform mat4 ViewTransform; 
uniform mat4 ProjectionTransform; 

// out value
out vec2 uv; 

void main() {
    gl_Position = position * WorldTransform;
    uv = texCoord;
}
