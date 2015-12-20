#version 330 core

attribute vec3 vertexCoord;
attribute vec3 vertexNormal;
attribute vec2 vertexTexCoord;

varying vec2 fVertexTexCoord;

uniform mat4 projMatrix;
uniform mat4 modelMatrix;

void main() {
	mat4 mvpMatrix = projMatrix * modelMatrix;
	gl_Position = mvpMatrix * vec4(vertexCoord, 1.0);

	fVertexTexCoord = vertexTexCoord;	// Pass to the fragment shader
}
