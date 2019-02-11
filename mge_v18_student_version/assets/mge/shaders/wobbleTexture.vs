//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 mvpMatrix;
uniform float time;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated

void main( void ){
    vec3 newVertex = vertex;
	newVertex *= 0.25f * sin(time) * sin(gl_VertexID) + 1;
    
    //Set gl position to the new vertex multiplied by the existing one
    gl_Position = mvpMatrix * vec4(newVertex, 1.f);
	texCoord = uv;
}
