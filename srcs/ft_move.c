/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 20:27:48 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/19 20:38:37 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_scop.h"

void		ft_right(t_data *d, float deltatime)
{
	t_vertex	right;

	right.x = sin(3.14 - (3.14 / 2));
	right.y = 0;
	right.z = cos(3.14 - (3.14 / 2));
	d->camera_pos.x += right.x * deltatime * 3;
	d->camera_pos.y += right.y * deltatime * 3;
	d->camera_pos.z += right.z * deltatime * 3;
}

void		ft_left(t_data *d, float deltatime)
{
	t_vertex	left;

	left.x = sin(3.14 - (3.14 / 2));
	left.y = 0;
	left.z = cos(3.14 - (3.14 / 2));
	d->camera_pos.x -= left.x * deltatime * 3;
	d->camera_pos.y -= left.y * deltatime * 3;
	d->camera_pos.z -= left.z * deltatime * 3;
}

void		ft_up(t_data *d, float deltatime)
{
	t_vertex	up;

	up.x = cos(0) * sin(3.14);
	up.y = sin(0);
	up.z = cos(0) * cos(3.14);
	d->camera_pos.x += up.x * deltatime * 3;
	d->camera_pos.y += up.y * deltatime * 3;
	d->camera_pos.z += up.z * deltatime * 3;
}

void		ft_down(t_data *d, float deltatime)
{
	t_vertex	down;

	down.x = cos(0) * sin(3.14);
	down.y = sin(0);
	down.z = cos(0) * cos(3.14);
	d->camera_pos.x -= down.x * deltatime * 3;
	d->camera_pos.y -= down.y * deltatime * 3;
	d->camera_pos.z -= down.z * deltatime * 3;
}
