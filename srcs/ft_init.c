/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:04:19 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/11 17:48:24 by mmartin          ###   ########.fr       */
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
	glBindFragDataLocationEXT(d->program, 0, "outColor");
	ft_init_scene(d);
}
