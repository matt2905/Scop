/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:04:19 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/22 12:45:28 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "printf.h"
#include "ft_scop.h"

static void	ft_init_scene(t_data *d)
{
	GLuint	vid;

	glGenVertexArrays(1, &vid);
	glBindVertexArray(vid);
	d->mode_id = glGetUniformLocation(d->program, "model");
	d->view_id = glGetUniformLocation(d->program, "view");
	d->proj_id = glGetUniformLocation(d->program, "projection");
	d->camera_pos.x = 0;
	d->camera_pos.y = 0;
	d->camera_pos.z = 5;
	d->camera_up.x = 0;
	d->camera_up.y = 1;
	d->camera_up.z = 0;
	d->angle_horizontal = 3.14;
	d->angle_vertical = 0;
	d->fov = 45;
	d->speed = 3;
	d->mouse_speed = 0.005;
	d->last_time = glfwGetTime();
	ft_set_perspective(d);
	ft_create_objects(d);
}

void		ft_init(t_data *d)
{
	GLint	ret;
	GLint	len;
	GLuint	vertex_id;
	GLuint	fragment_id;
	char	*log;

	d->program = glCreateProgram();
	vertex_id = ft_get_shader(GL_VERTEX_SHADER, "shader/shader.vert");
	fragment_id = ft_get_shader(GL_FRAGMENT_SHADER, "shader/shader.frag");
	ft_attach_shader(d->program, vertex_id);
	ft_attach_shader(d->program, fragment_id);
	glLinkProgram(d->program);
	glGetProgramiv(d->program, GL_LINK_STATUS, &ret);
	if (ret == GL_FALSE)
	{
		glGetProgramiv(d->program, GL_INFO_LOG_LENGTH, &len);
		log = (char *)ft_memalloc(sizeof(*log) * len);
		glGetProgramInfoLog(d->program, len, &ret, log);
		ft_printf("ft_init(): Program linking failed: %s\n", log);
		ft_strdel(&log);
		glDeleteProgram(d->program);
		d->program = 0;
		return ;
	}
	ft_init_scene(d);
}
