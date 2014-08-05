#version 330 core

varying vec2 fVertexTexCoord;

uniform sampler2D currentTexture;

void main(){
	gl_FragColor = texture2D(currentTexture, fVertexTexCoord);
}
