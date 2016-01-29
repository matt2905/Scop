/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:53:50 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/29 13:40:18 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static void		ft_create_object(t_data *d, t_obj o, int *begin)
{
	int			i;

	i = -1;
	while (++i < o.nb_f)
	{
		ft_cutt_triangle(d, begin, o, o.f[i]);
/*		j = 0;
		while (++j < o.f[i][0].len)
		{
			tmp = o.f[i][j].iv - 1;
			tmp = (tmp >= 0 ? tmp : 0);
			d->v[index] = o.v[tmp].x;
			d->v[index + 1] = o.v[tmp].y;
			d->v[index + 2] = o.v[tmp].z;
			ft_genere_color(d, index);
			index += 6;
		}
*/	}
}

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
	return (size * 6);
}

static void		ft_init_object_opengl(t_data *d)
{
	glGenBuffers(1, &d->vid);
	glBindBuffer(GL_ARRAY_BUFFER, d->vid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*d->v) * d->size_v,
			&d->v[0], GL_STATIC_DRAW);
}

void			ft_create_objects(t_data *d)
{
	int		i;
	int		begin;

	i = 0;
	begin = 0;
	d->v = NULL;
	d->size_v = ft_get_size(d->objs, d->nb_obj);
	d->v = (float *)ft_memalloc(sizeof(*d->v) * d->size_v);
	while (i < d->nb_obj)
	{
		ft_create_object(d, d->objs[i], &begin);
		i++;
	}
	if (!d->v)
		return ;
	ft_init_object_opengl(d);
}
