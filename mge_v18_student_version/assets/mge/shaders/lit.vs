//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform vec3    diffuseColor;
uniform vec3 	lightCol;
uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

out vec3 ambientColor;
out vec3 Normal;
out vec3 FragPos;

void main( void ){
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);
	Normal = mat3(transpose(inverse(modelMatrix))) * normal;
	FragPos = vec3(modelMatrix * vec4(vec3(vertex), 1.0f));			

	//Ambient lighting
	ambientColor = 0.5f * lightCol;
}
