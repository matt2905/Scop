
#version 410

layout	(location = 0) in vec3	vertexPosition_modelspace;
layout	(location = 1) in vec3	vertexColor;

out		vec3	fragmentColor;

uniform	mat4	MVP;
uniform	float	timer;

mat4	rotate_y(float theta)
{
	return (mat4(
		vec4(cos(theta), 0.0, -sin(theta), 0.0),
		vec4(0.0, 1.0, 0.0, 0.0),
		vec4(sin(theta), 0.0, cos(theta), 0.0),
		vec4(0.0, 0.0, 0.0, 1.0)
	));
}

void	main()
{
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	fragmentColor = vertexColor;
}
