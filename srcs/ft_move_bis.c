/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:41:12 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/21 17:41:20 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_scop.h"

int		ft_forward(t_data *d, double deltatime)
{
	d->camera_pos.x += d->camera_look.x * deltatime * 3;
	d->camera_pos.y += d->camera_look.y * deltatime * 3;
	d->camera_pos.z += d->camera_look.z * deltatime * 3;
	return (1);
}

int		ft_backward(t_data *d, double deltatime)
{
	d->camera_pos.x -= d->camera_look.x * deltatime * 3;
	d->camera_pos.y -= d->camera_look.y * deltatime * 3;
	d->camera_pos.z -= d->camera_look.z * deltatime * 3;
	return (1);
}
