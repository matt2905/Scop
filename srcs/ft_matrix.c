/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 09:27:32 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/19 16:16:39 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "ft_scop.h"

float	*ft_new_matrix(void)
{
	float	*new;

	if (!(new = (float *)ft_memalloc(sizeof(*new) * 16)))
	{
		return (NULL);
	}
	return (new);
}

float	*ft_mult_matrix(float *a, float *b)
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

float	*ft_view(t_vertex eye, t_vertex center, t_vertex up)
{
	float		*view;
	t_vertex	x;
	t_vertex	y;
	t_vertex	z;

	view = ft_new_matrix();
	z = ft_vector_min(eye, center);
	ft_normalize_vector(&z);
	y = up;
	x = ft_cross(y, z);
	y = ft_cross(z, x);
	ft_normalize_vector(&x);
	ft_normalize_vector(&y);
	view[0] = x.x;
	view[1] = y.x;
	view[2] = z.x;
	view[3] = (ft_dot(x, eye));
	view[4] = x.y;
	view[5] = y.y;
	view[6] = z.y;
	view[7] = (ft_dot(y, eye));
	view[8] = x.z;
	view[9] = y.z;
	view[10] = z.z;
	view[11] = 0;
	view[12] = -0.0;
	view[13] = -0.0;
	view[14] = -(ft_dot(z, eye));
	view[15] = 1;
	return (view);
}

float	*ft_identity()
{
	float	*identity;

	identity = ft_new_matrix();
	identity[0] = 1;
	identity[1] = 0;
	identity[2] = 0;
	identity[3] = 0;
	identity[4] = 0;
	identity[5] = 1;
	identity[6] = 0;
	identity[7] = 0;
	identity[8] = 0;
	identity[9] = 0;
	identity[10] = 1;
	identity[11] = 0;
	identity[12] = 0;
	identity[13] = 0;
	identity[14] = 0;
	identity[15] = 1;
	return (identity);
}

float	*ft_projection(float fov, float aspect, float near, float far)
{
	float	*projection;
	float	tanhalf;

	tanhalf = tan(fov / 2);
	projection = ft_new_matrix();
	projection[0] = 1 / (aspect * tanhalf);
	projection[1] = 0;
	projection[2] = 0;
	projection[3] = 0;
	projection[4] = 0;
	projection[5] = 1 / tanhalf;
	projection[6] = 0;
	projection[7] = 0;
	projection[8] = 0;
	projection[9] = 0;
	projection[10] = -(far + near) / (far - near);
	projection[11] = -1;
	projection[12] = 0;
	projection[13] = 0;
	projection[14] = -(2 * far * near) / (far - near);
	projection[15] = 0;
	return (projection);
}

void	ft_set_perspective(t_data *d)
{
	float		*projection;
	float		*view;
	float		*model;
	float		*tmp;

	projection = ft_projection(45, (float)WIDTH / (float)HEIGHT, 0.1, 100);
	view = ft_view(d->camera_pos, d->camera_look, d->camera_up);
	model = ft_identity();
	tmp = ft_mult_matrix(view, projection);
	d->mvp = ft_mult_matrix(model, tmp);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&projection);
	ft_memdel((void **)&view);
	ft_memdel((void **)&model);
}
