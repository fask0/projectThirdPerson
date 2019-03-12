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
in vec4 FragPosLightSpace;

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

uniform sampler2D shadowMap;
//Dynamic object loading stuff
#define NR_OF_TEXTURES 100
uniform sampler2D textures[NR_OF_TEXTURES];
uniform int splitter[NR_OF_TEXTURES];
in int index;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow	
	
	//float bias = max(0.05 * (1.0 - dot(Normal, dirLight.lightPos)), 0.005);
	float bias = 0.00001f;

	float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 0.5 : 0.0;        
        }    
    }
    shadow /= 9.0;

	if(projCoords.z > 1.0)
        shadow = 0.0;
    
    return shadow;
}

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

	int iToUse = 0;
	for(int i = 0; i < NR_OF_TEXTURES; i++)
	{
		if(splitter[i] != 0 && vertexID >= splitter[i])
		{
			iToUse = i;
		}
	}
	vec3 result = (ambientColor + diffuse) * vec3(texture(textures[iToUse],texCoord));

	return result;
}

void main( void ) {

	vec4 result = vec4(0, 0, 0, 0);

	result += CalcDirLight(dirLight, Normal);

	float shadow = ShadowCalculation(FragPosLightSpace);
	result = vec4(vec3(result * (1.0f - shadow)), result[3]);
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
