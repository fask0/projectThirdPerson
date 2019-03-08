//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

struct DirLight{
	vec3 lightCol;
	vec3 lightPos;
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

in vec3 Normal;
in vec3 ambientColor;
in vec3 FragPos;
in vec2 texCoord;
flat in int vertexID;

out vec4 fragment_color;

//Grid stuff
uniform vec3 mousePos;
uniform vec3 towerPos;

uniform bool gridVisible = true;
uniform bool showRange = false;

uniform float gridSize;
uniform float lineThiccness;
uniform float range;
uniform bool isColliding;

//Dynamic object loading stuff
#define NR_OF_TEXTURES 100
uniform sampler2D textures[NR_OF_TEXTURES];
uniform int splitter[NR_OF_TEXTURES];
in int index;

vec4 CalcDirLight(DirLight _dirLight, vec3 normal)
{
	vec3 norm = normalize(normal);
    vec3 lightDir = normalize(_dirLight.lightPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * _dirLight.lightCol;

    int iToUse = 0;
    for(int i = 0; i < NR_OF_TEXTURES; i++)
    {
        if(splitter[i] != 0 && vertexID >= splitter[i])
        {
            iToUse = i;
        }
    }

    vec4 color = vec4(texture(textures[iToUse],texCoord));

    //Shadow                   
    vec4 result = (vec4((ambientColor + diffuse), 1.0) * color);

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

	vec3 result = (ambientColor + diffuse) * vec3(texture(textures[0],texCoord));
	for(int i = 0; i < NR_OF_TEXTURES; i++)
	{
		if(splitter[i] != 0 && vertexID >= splitter[i])
		{
			result = (ambientColor + diffuse) * vec3(texture(textures[i],texCoord));
		}
	}

	return result;
}

void main( void ) {

	vec4 result = vec4(0, 0, 0, 0);

	result += CalcDirLight(dirLight, Normal);

	// for(int i = 0; i < NR_SPOT_LIGHTS; i++)
	// 	result += CalcSpotLight(spotLights[i], Normal, FragPos);

	fragment_color = result;		

	//GRID
	if(gridVisible)
	{
		//Line Thicccness
		if((mod(FragPos[0], gridSize) >= -lineThiccness && mod(FragPos[0], gridSize) <= lineThiccness)
		|| (mod(FragPos[2], gridSize) >= -lineThiccness && mod(FragPos[2], gridSize) <= lineThiccness))
		{
			fragment_color = vec4(0,0,0, 1);
		}
	}

	if(showRange)
	{
		if(isColliding)
		{
			if(distance(vec3(FragPos[0], 0, FragPos[2]), towerPos) <= range)
			{
				fragment_color = mix(fragment_color, vec4(0.8f, 0.0f, 0.0f, 1.0f), 0.5f);
			}
			else if(distance(vec3(FragPos[0], 0, FragPos[2]), towerPos) <= range + 0.1f)
			{
				fragment_color = mix(fragment_color, vec4(0.5f, 0.0f, 0.0f, 1.0f), 0.5f);
				
			}
		}
		else{
			if(distance(vec3(FragPos[0], 0, FragPos[2]), towerPos) <= range)
			{
				fragment_color = mix(fragment_color, vec4(0.8f, 0.8f, 0.8f, 1.0f), 0.5f);
			}
			else if(distance(vec3(FragPos[0], 0, FragPos[2]), towerPos) <= range + 0.1f)
			{
				fragment_color = mix(fragment_color, vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.5f);
				
			}
		}
	}
}
