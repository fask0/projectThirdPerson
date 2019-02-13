//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;

uniform vec3 mousePos;
uniform bool gridVisible = true;
uniform float gridSize;
uniform float lineThiccness;

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
			fragment_color = mix(fragment_color, vec4(0.4f,0.4f,0.9f,1.0f), 0.3f);
		}

		if((mod(FragPos[0], gridSize) >= -lineThiccness && mod(FragPos[0], gridSize) <= lineThiccness)
		|| (mod(FragPos[2], gridSize) >= -lineThiccness && mod(FragPos[2], gridSize) <= lineThiccness))
		{
			fragment_color = vec4(0,0,0, 1);
		}
	}
}
