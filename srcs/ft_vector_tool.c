/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:52:47 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/29 16:26:01 by mmartin          ###   ########.fr       */
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
	int		i;
	int		j;
	size_t	size;

	size = 0;
	j = -1;
	while (++j < d->nb_obj)
	{
		i = -1;
		while (++i < d->objs[j].nb_v)
		{
			center->x += d->objs[j].v[i].x;
			center->y += d->objs[j].v[i].y;
			center->z += d->objs[j].v[i].z;
			size++;
		}
	}
	center->x /= (float)size;
	center->y /= (float)size;
	center->z /= (float)size;
}
