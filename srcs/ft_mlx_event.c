/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 16:46:52 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/19 20:56:42 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include <mlx_opengl.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ft_scop.h"
#include "libft.h"

static unsigned int	ft_get_ticks(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

static void			ft_render(t_data *d)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(d->program);
	glUniformMatrix4fv(d->mid, 1, GL_FALSE, &d->mvp[0]);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, d->vid);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			6 * sizeof(float), (void *)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			6 * sizeof(float), (void *)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, d->size / 6);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	mlx_opengl_swap_buffers(d->win);
}

int					ft_key_press(int keycode, t_data *d)
{
	static unsigned int	prev;
	unsigned int		ticks;
	float				deltatime;

	if (!prev)
		prev = ft_get_ticks();
	ticks = ft_get_ticks();
	deltatime = (float)(ticks - prev) / 1000.0f;
	prev = ticks;
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx, d->win);
		ft_memdel((void **)&d->v);
		exit(1);
	}
	if (keycode == 123 || keycode == 0)
		ft_left(d, deltatime);
	if (keycode == 124 || keycode == 2)
		ft_right(d, deltatime);
	if (keycode == 125 || keycode == 1)
		ft_down(d, deltatime);
	if (keycode == 126 || keycode == 13)
		ft_up(d, deltatime);
//	d->camera_pos.z += (keycode == 69 || keycode == 24 ? -1 : 0);
//	d->camera_pos.z += (keycode == 78 || keycode == 27 ? 1 : 0);
	ft_set_perspective(d);
	ft_render(d);
	return (0);
}

int					ft_expose(t_data *d)
{
	ft_render(d);
	return (0);
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
	ft_key_press(-1, d);
	return (0);
}
