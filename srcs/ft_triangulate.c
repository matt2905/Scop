/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangulate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 13:37:13 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/26 13:50:36 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static const short	g_color[8][3] =
{
	{1, 0, 0},
	{1, 1, 0},
	{0, 1, 0},
	{0, 1, 1},
	{1, 1, 1},
	{1, 0, 1},
	{0, 0, 1},
	{0, 0, 0}
};

static void		ft_fillit_vertice(t_data *d)
{
	int		i;
	int		j;
	int		k;
	int		c;

	c = 0;
	i = 0;
	j = -1;
	while (++j < d->nb_obj)
	{
		k = -1;
		while (++k < d->objs[j].nb_v)
		{
			d->v[i++] = d->objs[j].v[k].x;
			d->v[i++] = d->objs[j].v[k].y;
			d->v[i++] = d->objs[j].v[k].z;
			d->v[i++] = g_color[c][0];
			d->v[i++] = g_color[c][1];
			d->v[i++] = g_color[c][2];
			c++;
			if (c >= 8)
				c = 0;
		}
	}
}

static size_t	ft_calc_size_vertice(t_data *d)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (i < d->nb_obj)
	{
		size += d->objs[i].nb_v * 6;
		i++;
	}
	return (size);
}

static void		ft_fillit_indice(t_data *d)
{
	int		index;
	int		i;
	int		j;
	size_t	k;

	index = 0;
	i = -1;
	while (++i < d->nb_obj)
	{
		j = -1;
		while (++j < d->objs[i].nb_f)
		{
			k = 0;
			while (++k < d->objs[i].f[j][0].len)
				d->i[index++] = d->objs[i].f[j][k].iv;
		}
	}
}

static size_t	ft_calc_size_indice(t_data *d)
{
	int		i;
	int		j;
	size_t	size;

	i = -1;
	size = 0;
	while (++i < d->nb_obj)
	{
		j = -1;
		while (++j < d->objs[i].nb_f)
			size += d->objs[i].f[j][0].len - 1;
	}
	return (size);
}

void			ft_triangulate(t_data *d)
{
	d->size_v = ft_calc_size_vertice(d);
	d->v = (float *)ft_memalloc(d->size_v * sizeof(*d->v));
	ft_fillit_vertice(d);
	d->size_i = ft_calc_size_indice(d);
	d->i = (size_t *)ft_memalloc(d->size_i * sizeof(*d->i));
	ft_fillit_indice(d);
}
