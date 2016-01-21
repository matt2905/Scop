/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:52:47 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/21 16:54:15 by mmartin          ###   ########.fr       */
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
