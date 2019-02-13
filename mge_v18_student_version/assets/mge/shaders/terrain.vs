//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	mvpMatrix;
uniform mat4    modelMatrix;

uniform sampler2D heightMap;
uniform float terrainHeight;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated
out vec3 FragPos;

void main( void ){
    float heightValue = texture2D(heightMap, uv)[0];

    gl_Position = mvpMatrix * vec4(vertex, 1.f) + vec4(0, (terrainHeight * heightValue), 0, 0);
	texCoord = uv;

    FragPos = vec3(modelMatrix * vec4(vec3(vertex), 1.0f));
}
