/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:52:47 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/22 13:49:29 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_scop.h"

void		ft_normalize_vector(t_vertex *src)
{
	float		norme;

	norme = (*src).x * (*src).x + (*src).y * (*src).y + (*src).z * (*src).z;
	norme = fabs(sqrt(norme));
	(*src).x = (*src).x / norme;
	(*src).y = (*src).y / norme;
	(*src).z = (*src).z / norme;
}

float		ft_dot(t_vertex a, t_vertex b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void		ft_search_center(t_data *d, t_vertex *center)
{
	float	x;
	float	y;
	float	z;
	size_t	i;

	x = 0;
	y = 0;
	z = 0;
	i = 0;
	while (i < d->size)
	{
		x += d->v[i];
		y += d->v[i + 1];
		z += d->v[i + 2];
		i += 3;
	}
	x = x / (i / 3);
	y = y / (i / 3);
	z = z / (i / 3);
	center->x = x;
	center->y = y;
	center->z = z;
}