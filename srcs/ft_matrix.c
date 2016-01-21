/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 09:27:32 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/21 20:16:00 by mmartin          ###   ########.fr       */
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

float	*ft_identity(void)
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

	projection = ft_projection(d->fov, (float)WIDTH / (float)HEIGHT, 0.1, 100);
	view = ft_look_at(d->camera_pos,
			ft_vector_add(d->camera_pos, d->camera_look),
			d->camera_up);
	model = ft_identity();
	tmp = ft_mult_matrix(view, projection);
	d->mvp = ft_mult_matrix(model, tmp);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&projection);
	ft_memdel((void **)&view);
	ft_memdel((void **)&model);
}
