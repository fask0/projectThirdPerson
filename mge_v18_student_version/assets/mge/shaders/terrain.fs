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


	//---Linear interpolation between textures instead of just adding them together
	// vec4 diffuse0 = texture(diffuseTexture0, texCoord);
	// vec4 diffuse1 = texture(diffuseTexture1, texCoord + vec2(sin(time), cos(time)));
	// vec4 diffuse2 = texture(diffuseTexture2, texCoord);
	// vec4 diffuse3 = texture(diffuseTexture3, texCoord);
	// vec4 splat = texture(splatMap, texCoord);

	// diffuse0 *= splat.r;
	// diffuse1 = mix(diffuse0, diffuse1, splat.g);
	// diffuse2 = mix(diffuse1, diffuse2, splat.b);
	// vec4 color = vec4(mix(diffuse2, diffuse3, splat.a));
	// color.w = 1;

	// fragment_color = outColor;
}
