
#version 410

in		vec3	fragmentColor;
in		vec2	UV;

out		vec3	color;

uniform	sampler2D	myTextureSampler;

void	main()
{
	color = fragmentColor;
	color = texture(myTextureSampler, UV).rgb;
}
