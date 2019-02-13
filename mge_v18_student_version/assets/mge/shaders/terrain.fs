//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D splatMap;
uniform sampler2D diffuseTexture0;
uniform sampler2D diffuseTexture1;
uniform sampler2D diffuseTexture2;
uniform sampler2D diffuseTexture3;

uniform float time;
uniform vec3 mousePos;

in vec2 texCoord;
in vec3 FragPos;

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
	float lineThickness = 0.1f;
	int gridSize = 3;

	if(floor(FragPos[0] / gridSize) == floor(mousePos[0] / gridSize) && floor(FragPos[2] / gridSize) == floor(mousePos[2] / gridSize))
	{
		fragment_color = mix(fragment_color, vec4(0.4f,0.4f,0.9f,1.0f), 0.3f);
	}

	if((mod(FragPos[0], gridSize) >= -lineThickness && mod(FragPos[0], gridSize) <= lineThickness)
	|| (mod(FragPos[2], gridSize) >= -lineThickness && mod(FragPos[2], gridSize) <= lineThickness))
	{
		fragment_color = vec4(0,0,0,1);
	}
}
