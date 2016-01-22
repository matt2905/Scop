
#version 410

layout	(location = 0) in vec3	vertexPosition_modelspace;
layout	(location = 1) in vec3	vertexColor;

out		vec3	fragmentColor;

uniform	mat4	model;
uniform	mat4	view;
uniform	mat4	projection;

void	main()
{
	gl_Position = projection * view * model * vec4(vertexPosition_modelspace, 1);

	fragmentColor = vertexColor;
}
