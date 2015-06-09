/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 16:46:52 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/09 12:39:44 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <mlx_opengl.h>
#include <openGL/GL.h>
#include <stdlib.h>
#include "ft_scop.h"

int		ft_key_press(int keycode, t_data *d)
{
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(1);
	}
	/*	Gauche: keycode == 123 || 0	*/
	/*	Droite: keycode == 124 || 2	*/
	/*	Bas : keycode == 125 || 1	*/
	/*	Haut : keycode == 126 || 13	*/
	/*	Plus : keycode == 69 || 24	*/
	/*	Moins : keycode == 78 || 27 */
	return (0);
}

int		ft_expose(t_data *d)
{
	(void)d;
	return (0);
}

int		ft_loop_hook(t_data *d)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mlx_opengl_swap_buffers(d->win);
	return (0);
}
