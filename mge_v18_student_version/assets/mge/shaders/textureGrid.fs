//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;

uniform vec3 mousePos;
uniform vec3 towerPos;

uniform bool gridVisible = true;
uniform bool showRange = false;

uniform float gridSize;
uniform float lineThiccness;
uniform float range;

in vec2 texCoord;
in vec3 FragPos;

out vec4 fragment_color;

void main( void ) 
{
	fragment_color = texture(diffuseTexture, texCoord);

	if(gridVisible)
	{
		//Line Thicccness
		if(floor(FragPos[0] / gridSize) == floor(mousePos[0] / gridSize) && floor(FragPos[2] / gridSize) == floor(mousePos[2] / gridSize))
		{
			fragment_color = mix(fragment_color, vec4(0.4f,0.4f,0.9f,1.0f), 0.6f);
		}

		if((mod(FragPos[0], gridSize) >= -lineThiccness && mod(FragPos[0], gridSize) <= lineThiccness)
		|| (mod(FragPos[2], gridSize) >= -lineThiccness && mod(FragPos[2], gridSize) <= lineThiccness))
		{
			fragment_color = vec4(0,0,0, 1);
		}
	}

	if(showRange)
	{
		if(distance(vec3(FragPos[0], 0, FragPos[2]), towerPos) <= range)
		{
			fragment_color = mix(fragment_color, vec4(0.8f, 0.8f, 0.8f, 1.0f), 0.5f);
		}
		else if(distance(vec3(FragPos[0], 0, FragPos[2]), towerPos) <= range + 0.3f)
		{
			fragment_color = mix(fragment_color, vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.5f);
			
		}
	}
}
