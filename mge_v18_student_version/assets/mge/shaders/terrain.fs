//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D splatMap;
uniform sampler2D diffuseTexture0;
uniform sampler2D diffuseTexture1;
uniform sampler2D diffuseTexture2;
uniform sampler2D diffuseTexture3;

uniform float time;

in vec2 texCoord;
out vec4 fragment_color;

void main( void ) 
{
	vec4 splat = texture(splatMap, texCoord);
	vec4 diffuse0 = splat[0] * texture(diffuseTexture0, texCoord);
	vec4 diffuse1 = splat[1] * texture(diffuseTexture1, texCoord + vec2(sin(time), cos(time)));
	vec4 diffuse2 = splat[2] * texture(diffuseTexture2, texCoord);
	vec4 diffuse3 = splat[3] * texture(diffuseTexture3, texCoord);

	fragment_color = diffuse0 + diffuse1 + diffuse2 + diffuse3;


	//Line Thicccness
	float lineThickness = 0.3f;
	int gridSize = 10;

	float stepSize = 100.0f / gridSize;
	float currentStep = 0.0f;

	for(int i = 0; i < gridSize - 1; i++)
	{
		currentStep += stepSize;
		float thing = 0;
		if(texCoord[0] * 100.0f >= currentStep - lineThickness && texCoord[0] * 100.0f <= currentStep + lineThickness)
		{
			thing = abs((currentStep - texCoord[0] * 100.0f) * 100) / 100;
			fragment_color = mix(fragment_color, vec4(0,0,0, 1.0f), 1 - (thing * (1.0f / lineThickness)));
		}
		if(texCoord[1] * 100.0f >= currentStep - lineThickness && texCoord[1] * 100.0f <= currentStep + lineThickness)
		{
			thing = abs((currentStep - texCoord[1] * 100.0f) * 100) / 100;
			fragment_color = mix(fragment_color, vec4(0,0,0, 1.0f), 1 - (thing * (1.0f / lineThickness)));
		}
	}
}
