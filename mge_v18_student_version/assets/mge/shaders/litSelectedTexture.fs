//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

struct DirLight{
	vec3 lightCol;
	vec3 lightRot;
};

struct SpotLight{
	vec3 lightCol;
	vec3 lightPos;
	vec3 lightRot;
	float cutOff;
	float outerCutOff;
};

uniform DirLight dirLight;
#define NR_SPOT_LIGHTS 1
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform sampler2D diffuseTexture;
uniform float mixIntensity;

in vec3 Normal;
in vec3 ambientColor;
in vec3 FragPos;
in vec2 texCoord;

out vec4 fragment_color;

vec3 CalcDirLight(DirLight _dirLight, vec3 normal)
{
	vec3 norm = normalize(normal);
	vec3 lightDir = -_dirLight.lightRot;
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * _dirLight.lightCol;

	vec3 result = (ambientColor + diffuse) * vec3(texture(diffuseTexture,texCoord));
	return result;	
}

vec3 CalcSpotLight(SpotLight _spotLight, vec3 normal, vec3 fragPos)
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(_spotLight.lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * _spotLight.lightCol;

	float theta = dot(lightDir, normalize(-_spotLight.lightRot));
	float epsilon = (_spotLight.cutOff - _spotLight.outerCutOff);
	float intensity = clamp((theta - _spotLight.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;

	vec3 result = (ambientColor + diffuse) * vec3(texture(diffuseTexture,texCoord));
	return result;	
}

void main( void ) {

	vec3 result = vec3(0, 0, 0);

	result += CalcDirLight(dirLight, Normal);

	for(int i = 0; i < NR_SPOT_LIGHTS; i++)
		result += CalcSpotLight(spotLights[i], Normal, FragPos);

	fragment_color = mix(vec4(result, 1), vec4(1,1,1,0.8f), mixIntensity);
}
