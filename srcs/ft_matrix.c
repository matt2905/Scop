/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 09:27:32 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/22 15:22:36 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "ft_scop.h"

float	*ft_new_matrix(void)
{
	float	*new;

	if (!(new = (float *)ft_memalloc(sizeof(*new) * 16)))
		return (NULL);
	return (new);
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

void	ft_min_center(t_data *d, t_vertex *center)
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
	center->x = -x;
	center->y = -y;
	center->z = -z;
}

float	*ft_rotate_y(float theta)
{
	float	*ret;

	ret = ft_new_matrix();
	ret[0] = cos(theta);
	ret[1] = 0;
	ret[2] = -sin(theta);
	ret[3] = 0;
	ret[4] = 0;
	ret[5] = 1;
	ret[6] = 0;
	ret[7] = 0;
	ret[8] = sin(theta);
	ret[9] = 0;
	ret[10] = cos(theta);
	ret[11] = 0;
	ret[12] = 0;
	ret[13] = 0;
	ret[14] = 0;
	ret[15] = 1;
	return (ret);
}

void	ft_set_perspective(t_data *d)
{
	static float	angle;
	t_vertex		center;
	//float			*ptr;
	//float			*tmp;
	//float			*rotate;

	angle += 3.14 * (glfwGetTime() - d->last_time) * 1000;
	d->projection = ft_projection(d->fov,
			(float)WIDTH / (float)HEIGHT, 0.1, 100);
	d->view = ft_look_at(d->camera_pos,
			ft_vector_add(d->camera_pos, d->camera_look),
			d->camera_up);
	ft_search_center(d, &center);
	//ptr = ft_translate(center);
	d->model = ft_rotate_y(angle);
	//rotate = ft_rotate_y(angle);
	//tmp = ft_mult_matrix(ptr, rotate);
	//ft_memdel((void **)&ptr);
	//center = ft_vector_neg(center);
	//ptr = ft_translate(center);
	//d->model = ft_mult_matrix(ptr, tmp);
	//ft_memdel((void **)&ptr);
	//ft_memdel((void **)&tmp);
	//ft_memdel((void **)&rotate);
}
