/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 20:27:48 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/21 17:40:58 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_scop.h"

int		ft_right(t_data *d, double deltatime)
{
	t_vertex	right;

	right.x = sin(d->angle_horizontal - (3.14 / 2.0));
	right.y = 0;
	right.z = cos(d->angle_horizontal - (3.14 / 2.0));
	d->camera_pos.x += right.x * deltatime * 3;
	d->camera_pos.y += right.y * deltatime * 3;
	d->camera_pos.z += right.z * deltatime * 3;
	return (1);
}

int		ft_left(t_data *d, double deltatime)
{
	t_vertex	right;

	right.x = sin(d->angle_horizontal - (3.14 / 2.0));
	right.y = 0;
	right.z = cos(d->angle_horizontal - (3.14 / 2.0));
	d->camera_pos.x -= right.x * deltatime * 3;
	d->camera_pos.y -= right.y * deltatime * 3;
	d->camera_pos.z -= right.z * deltatime * 3;
	return (1);
}

int		ft_up(t_data *d, double deltatime)
{
	t_vertex	up;
	t_vertex	right;

	right.x = sin(d->angle_horizontal - (3.14 / 2.0));
	right.y = 0;
	right.z = cos(d->angle_horizontal - (3.14 / 2.0));
	up = ft_cross(d->camera_look, right);
	d->camera_pos.x -= up.x * deltatime * 3;
	d->camera_pos.y -= up.y * deltatime * 3;
	d->camera_pos.z -= up.z * deltatime * 3;
	return (1);
}

int		ft_down(t_data *d, double deltatime)
{
	t_vertex	up;
	t_vertex	right;

	right.x = sin(d->angle_horizontal - (3.14 / 2.0));
	right.y = 0;
	right.z = cos(d->angle_horizontal - (3.14 / 2.0));
	up = ft_cross(d->camera_look, right);
	d->camera_pos.x += up.x * deltatime * 3;
	d->camera_pos.y += up.y * deltatime * 3;
	d->camera_pos.z += up.z * deltatime * 3;
	return (1);
}
