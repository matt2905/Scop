/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:04:19 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/10 13:00:30 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "printf.h"
#include "ft_scop.h"

static void	ft_init_scene(t_data *d)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ft_set_perspective(M_PI / 4.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	d->camera_pos_loc = glGetUniformLocation(d->program, "cameraPosition");
	d->light_pos_loc = glGetUniformLocation(d->program, "lightPosition");
	d->light_col_loc = glGetUniformLocation(d->program, "lightColor");
	d->light_col[0] = 1.0f;
	d->light_col[1] = 1.0f;
	d->light_col[2] = 1.0f;
	ft_create_objects(d);
	d->rotate = 0.0f;
	ft_loop_hook(d);
	d->camera_pos[0] = 0.0f;
	d->camera_pos[1] = 0.0f;
	d->camera_pos[2] = 4.0f;
	glLoadIdentity();
	glTranslatef(-d->camera_pos[0], -d->camera_pos[1], -d->camera_pos[2]);
}

void		ft_init(t_data *d)
{
	GLint	ret;
	GLint	len;
	char	*log;

	d->program = glCreateProgram();
	ft_attach_shader(d->program, ft_get_shader(GL_VERTEX_SHADER, "shader/test.vp"));
	ft_attach_shader(d->program, ft_get_shader(GL_FRAGMENT_SHADER, "shader/test.fp"));
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
