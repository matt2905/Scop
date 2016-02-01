/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:53:50 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/01 10:28:05 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static size_t	ft_get_size(t_obj *o, int len)
{
	int		i;
	int		j;
	size_t	size;
	int		tmp;

	i = 0;
	size = 0;
	while (i < len)
	{
		j = 0;
		while (j < o[i].nb_f)
		{
			tmp = o[i].f[j][0].len - 1;
			size += (tmp - 2) * 3;
			j++;
		}
		i++;
	}
	return (size * 8);
}

static void		ft_init_object_opengl(t_data *d)
{
	glGenBuffers(1, &d->vid);
	glBindBuffer(GL_ARRAY_BUFFER, d->vid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*d->v) * d->size_v,
			&d->v[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void *)(3 * sizeof(float)));
}

void			ft_create_objects(t_data *d)
{
	int		i;
	int		j;
	int		begin;

	i = -1;
	begin = 0;
	d->v = NULL;
	d->size_v = ft_get_size(d->objs, d->nb_obj);
	d->v = (float *)ft_memalloc(sizeof(*d->v) * d->size_v);
	while (++i < d->nb_obj)
	{
		j = -1;
		while (++j < d->objs[i].nb_f)
			ft_cutt_triangle(d, &begin, d->objs[i], d->objs[i].f[j]);
	}
	if (!d->v)
		return ;
	ft_init_object_opengl(d);
}
