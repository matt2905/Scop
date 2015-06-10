/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 16:46:52 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/10 13:45:38 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include <mlx_opengl.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ft_scop.h"

int					ft_key_press(int keycode, t_data *d)
{
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(1);
	}
	d->camera_pos[0] += (keycode == 123 || keycode == 0 ? -1 : 0);
	d->camera_pos[0] += (keycode == 124 || keycode == 2 ? 1 : 0);
	d->camera_pos[1] += (keycode == 125 || keycode == 1 ? -1 : 0);
	d->camera_pos[1] += (keycode == 126 || keycode == 13 ? 1 : 0);
	d->camera_pos[2] += (keycode == 69 || keycode == 24 ? -1 : 0);
	d->camera_pos[2] += (keycode == 78 || keycode == 27 ? 1 : 0);
	return (0);
}

int					ft_expose(t_data *d)
{
	(void)d;
	return (0);
}

static unsigned int	ft_get_ticks(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

static void			ft_render(t_data *d)
{
	size_t	size;

	size = (d->objs[0].nb_f + 1) * 2 * 8;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(d->program);
	glUniform3fv(d->camera_pos_loc, 1, d->camera_pos);
	glUniform3fv(d->light_pos_loc, 1, d->light_pos);
	glUniform3fv(d->light_col_loc, 1, d->light_col);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, size);
	glUseProgram(0);
	mlx_opengl_swap_buffers(d->win);
}

int					ft_loop_hook(t_data *d)
{
	static unsigned int	prev;
	unsigned int		ticks;
	float				seconds;

	if (!prev)
		prev = ft_get_ticks();
	ticks = ft_get_ticks();
	seconds = (float)(ticks - prev) / 1000.0f;
	prev = ticks;
	d->rotate += (M_PI / 4.0f) * seconds;
	ft_render(d);
	return (0);
}
