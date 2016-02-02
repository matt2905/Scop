
#version 410

in		vec3	fragmentColor;
in		vec2	UV;

out		vec3	color;

uniform	sampler2D	myTextureSampler;
uniform lowp float	textureFlag;

void	main()
{
	color = mix(
				fragmentColor,
				texture(myTextureSampler, UV).rgb,
				textureFlag
				);
}
