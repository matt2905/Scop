/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:53:50 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/03 12:39:05 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static size_t	ft_set_size(t_data *d)
{
	int		i;
	int		j;
	int		tmp;
	size_t	size;

	i = -1;
	size = 0;
	while (++i < d->nb_obj)
	{
		d->size_v[i] = 0;
		j = -1;
		while (++j < d->objs[i].nb_f)
		{
			tmp = d->objs[i].f[j][0].len - 1;
			d->size_v[i] += (tmp - 2) * 3 * 8;
		}
		size += d->size_v[i];
	}
	return (size);
}

static void		ft_init_object_opengl(t_data *d, size_t size)
{
	glGenBuffers(1, &d->vid);
	glBindBuffer(GL_ARRAY_BUFFER, d->vid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*d->v) * size,
			&d->v[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void *)(6 * sizeof(float)));
}

void			ft_create_objects(t_data *d)
{
	int		i;
	size_t	size;
	int		begin;

	i = -1;
	begin = 0;
	d->size_v = (GLsizei *)ft_memalloc(sizeof(*d->size_v) * d->nb_obj);
	d->start = (GLint *)ft_memalloc(sizeof(*d->start) * d->nb_obj);
	size = ft_set_size(d);
	d->v = (float *)ft_memalloc(sizeof(*d->v) * size);
	while (++i < d->nb_obj)
	{
		d->start[i] = begin / 8;
		ft_triangulate_object(d, d->objs[i], &begin);
	}
	if (!d->v)
		return ;
	ft_init_object_opengl(d, size);
}
