/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutt_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 13:28:21 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/29 19:58:14 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_scop.h"

static const float	g_color[3][3] =
{
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f}
};

static void		ft_push_triangle(t_data *d, t_vertex v, t_vertex vt, int *index)
{
	static int	i = 0;

	if (i >= 3)
		i = 0;
	d->v[(*index)++] = v.x;
	d->v[(*index)++] = v.y;
	d->v[(*index)++] = v.z;
	d->v[(*index)++] = g_color[i][0];
	d->v[(*index)++] = g_color[i][1];
	d->v[(*index)++] = g_color[i][2];
	d->v[(*index)++] = vt.x;
	d->v[(*index)++] = vt.y;
	i++;
}

static t_vertex	ft_def(void)
{
	t_vertex	nul;

	nul.x = 0;
	nul.y = 0;
	nul.z = 0;
	return (nul);
}

void			ft_cutt_triangle(t_data *d, int *index, t_obj o, t_face *f)
{
	size_t		i;
	t_vertex	v;
	t_vertex	vt;
	t_vertex	c;
	t_vertex	ct;

	i = 0;
	c = o.v[f[f[0].len - 1].iv - 1];
	ct = ((int)f[f[0].len - 1].ivt - 1 >= 0 ?
			o.vt[f[f[0].len - 1].ivt - 1] : ft_def());
	while (++i < f[0].len - 2)
	{
		v = o.v[f[i].iv - 1];
		vt = ((int)f[i].ivt - 1 >= 0 ? o.vt[f[i].ivt - 1] : ft_def());
		ft_push_triangle(d, v, vt, index);
		v = o.v[f[i + 1].iv - 1];
		vt = ((int)f[i + 1].ivt - 1 >= 0 ? o.vt[f[i + 1].ivt - 1] : ft_def());
		ft_push_triangle(d, v, vt, index);
		ft_push_triangle(d, c, ct, index);
	}
}
