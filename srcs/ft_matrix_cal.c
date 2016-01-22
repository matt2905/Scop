/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_cal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:15:41 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/22 15:41:51 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_scop.h"

float			*ft_mult_matrix(float *a, float *b)
{
	float	*ret;

	ret = ft_new_matrix();
	ret[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
	ret[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
	ret[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
	ret[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];
	ret[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
	ret[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
	ret[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
	ret[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];
	ret[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
	ret[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
	ret[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
	ret[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];
	ret[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
	ret[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
	ret[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
	ret[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];
	return (ret);
}

float			*ft_translate(t_vertex center)
{
	float		*ret;

	ret = ft_new_matrix();
	ret[0] = 1;
	ret[1] = 0;
	ret[2] = 0;
	ret[3] = 0;//center.x;
	ret[4] = 0;
	ret[5] = 1;
	ret[6] = 0;
	ret[7] = 0;//center.y;
	ret[8] = 0;
	ret[9] = 0;
	ret[10] = 1;
	ret[11] = 0;//center.z;
	ret[12] = center.x;
	ret[13] = center.y;
	ret[14] = center.z;
	ret[15] = 1;
	return (ret);
}

static float	*ft_set_look(t_vertex x, t_vertex y, t_vertex z, t_vertex eye)
{
	float		*view;

	view = ft_new_matrix();
	view[0] = x.x;
	view[1] = y.x;
	view[2] = z.x;
	view[3] = 0;
	view[4] = x.y;
	view[5] = y.y;
	view[6] = z.y;
	view[7] = 0;
	view[8] = x.z;
	view[9] = y.z;
	view[10] = z.z;
	view[11] = 0;
	view[12] = -(ft_dot(x, eye));
	view[13] = -(ft_dot(y, eye));
	view[14] = -(ft_dot(z, eye));
	view[15] = 1;
	return (view);
}

float			*ft_look_at(t_vertex eye, t_vertex center, t_vertex up)
{
	t_vertex	x;
	t_vertex	y;
	t_vertex	z;

	z = ft_vector_min(eye, center);
	ft_normalize_vector(&z);
	y = up;
	x = ft_cross(y, z);
	y = ft_cross(z, x);
	ft_normalize_vector(&x);
	ft_normalize_vector(&y);
	return (ft_set_look(x, y, z, eye));
}
