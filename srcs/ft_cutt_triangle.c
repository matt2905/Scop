/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutt_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 13:28:21 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/15 11:19:39 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_scop.h"

static const float	g_color[3][3] =
{
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f}
};

static void		ft_push_triangle(float **d, t_vertex v, t_vertex vt, int *index)
{
	static int	i = 0;

	if (i >= 3)
		i = 0;
	(*d)[(*index)++] = v.x;
	(*d)[(*index)++] = v.y;
	(*d)[(*index)++] = v.z;
	(*d)[(*index)++] = g_color[i][0];
	(*d)[(*index)++] = g_color[i][1];
	(*d)[(*index)++] = g_color[i][2];
	(*d)[(*index)++] = vt.x;
	(*d)[(*index)++] = vt.y;
	i++;
}

static t_vertex	ft_def(t_data *d, t_vertex pt)
{
	t_vertex		nul;
	static t_vertex	min;
	static t_vertex	max;
	int				i;
	int				j;

	if (min.x == max.x && min.y == max.y && min.z == max.z && (i = -1))
	{
		while (++i < d->nb_obj && (j = -1))
		{
			while (++j < d->objs[i].nb_v)
			{
				min.x = d->objs[i].v[j].x < min.x ? d->objs[i].v[j].x : min.x;
				min.y = d->objs[i].v[j].y < min.y ? d->objs[i].v[j].y : min.y;
				max.x = d->objs[i].v[j].x > max.x ? d->objs[i].v[j].x : max.x;
				max.y = d->objs[i].v[j].y > max.y ? d->objs[i].v[j].y : max.y;
			}
		}
	}
	nul.x = (pt.x - min.x) / (max.x - min.x);
	nul.y = (pt.y - min.y) / (max.y - min.y);
	return (nul);
}

void			ft_cutt_triangle(float **dst, int *index, t_obj o, t_face *f)
{
	size_t		i;
	t_vertex	v;
	t_vertex	vt;
	t_vertex	c;
	t_vertex	ct;

	i = 0;
	c = o.v[f[f[0].len - 1].iv - 1];
	ct = ((int)f[f[0].len - 1].ivt - 1 >= 0 && o.vt ?
			o.vt[f[f[0].len - 1].ivt - 1] : ft_def(NULL, c));
	while (++i < f[0].len - 2)
	{
		v = o.v[f[i].iv - 1];
		vt = ((int)f[i].ivt - 1 >= 0 && o.vt ?
				o.vt[f[i].ivt - 1] : ft_def(NULL, v));
		ft_push_triangle(dst, v, vt, index);
		v = o.v[f[i + 1].iv - 1];
		vt = ((int)f[i + 1].ivt - 1 >= 0 && o.vt ?
				o.vt[f[i + 1].ivt - 1] : ft_def(NULL, v));
		ft_push_triangle(dst, v, vt, index);
		ft_push_triangle(dst, c, ct, index);
	}
}

void			ft_triangulate_object(t_data *d, t_obj o, int *index)
{
	int		j;

	j = -1;
	ft_def(d, d->objs[0].v[0]);
	while (++j < o.nb_f)
		ft_cutt_triangle(&d->v, index, o, o.f[j]);
}
