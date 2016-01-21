/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:53:50 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/21 15:29:21 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static void		ft_genere_color(t_data *d, int index)
{
	static float	color[3] = {1.0f, 0.0f, 0.0f};
	float			new_color[3];

	d->v[index + 3] = color[0];
	d->v[index + 4] = color[1];
	d->v[index + 5] = color[2];
	new_color[0] = color[2];
	new_color[1] = color[0];
	new_color[2] = color[1];
	color[0] = new_color[0];
	color[1] = new_color[1];
	color[2] = new_color[2];
}

static void		ft_create_object(t_data *d, t_obj o, int *begin)
{
	int			index;
	int			i;
	unsigned	j;
	int			tmp;

	index = *begin;
	i = -1;
	while (++i < o.nb_f)
	{
		j = 0;
		while (++j < o.f[i][0].len)
		{
			tmp = o.f[i][j].iv - 1;
			tmp = (tmp > 0 ? tmp : tmp + 1);
			d->v[index] = o.v[tmp].x;
			d->v[index + 1] = o.v[tmp].y;
			d->v[index + 2] = o.v[tmp].z;
			ft_genere_color(d, index);
			index += 6;
		}
	}
	*begin = index;
}

static size_t	ft_get_size(t_obj *o, int len)
{
	int		i;
	int		j;
	size_t	size;

	i = 0;
	size = 0;
	while (i < len)
	{
		j = 0;
		while (j < o[i].nb_f)
		{
			size += (o[i].f[j][0].len - 1);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(*d->v) * d->size,
			d->v, GL_STATIC_DRAW);
	glGenBuffers(1, &d->cid);
	glBindBuffer(GL_ARRAY_BUFFER, d->cid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*d->v) * d->size,
			d->v, GL_STATIC_DRAW);
}

void			ft_create_objects(t_data *d)
{
	int		i;
	int		begin;

	i = 0;
	begin = 0;
	d->v = NULL;
	d->size = ft_get_size(d->objs, d->nb_obj);
	d->v = (float *)ft_memalloc(sizeof(*d->v) * d->size);
	while (i < d->nb_obj)
	{
		ft_create_object(d, d->objs[i], &begin);
		i++;
	}
	if (!d->v)
		return ;
	ft_init_object_opengl(d);
}
