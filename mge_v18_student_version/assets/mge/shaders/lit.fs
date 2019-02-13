//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

struct DirLight{
	uniform vec3 lightCol;
	uniform vec3 lightRot;
}

struct SpotLight{
	uniform vec3 lightCol;
	uniform vec3 lightPos;
	uniform vec3 lightRot;
	uniform float cutOff;
	uniform float outerCutOff;
}

uniform vec3 lightCol;
uniform vec3 lightPos;
uniform vec3 lightRot;
uniform float cutOff;
uniform float outerCutOff;
uniform bool isSpotlight;

uniform vec3 diffuseColor;

in vec3 Normal;
in vec3 ambientColor;
in vec3 FragPos;

out vec4 fragment_color;

void main( void ) {
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	if(!isSpotlight){ lightDir = -lightRot; }
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightCol;


	//Spotlight
	if(isSpotlight)
	{
		float theta = dot(lightDir, normalize(-lightRot));
		float epsilon = (cutOff - outerCutOff);
		float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
		diffuse *= intensity;
	}


	vec3 result = (ambientColor + diffuse) * diffuseColor;
	fragment_color = vec4(result, 1.0);		
}
