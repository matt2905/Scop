/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 13:08:31 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/21 17:14:46 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_scop.h"

t_vertex	ft_float_to_vector(float *src)
{
	t_vertex	dst;

	dst.x = src[0];
	dst.y = src[1];
	dst.z = src[2];
	return (dst);
}

t_vertex	ft_cross(t_vertex a, t_vertex b)
{
	t_vertex	dst;

	dst.x = a.y * b.z - a.z * b.y;
	dst.y = a.z * b.x - a.x * b.z;
	dst.z = a.x * b.y - a.y * b.x;
	return (dst);
}

t_vertex	ft_vector_min(t_vertex a, t_vertex b)
{
	t_vertex	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vertex	ft_vector_add(t_vertex a, t_vertex b)
{
	t_vertex	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}
