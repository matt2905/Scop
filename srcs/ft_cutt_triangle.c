/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutt_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 13:28:21 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/29 13:45:31 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_scop.h"

static const float	g_color[3][3] =
{
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f}
};

static void	ft_push_triangle(t_data *d, t_vertex src, int *index)
{
	static int	i = 0;

	if (i >= 3)
		i = 0;
	d->v[(*index)++] = src.x;
	d->v[(*index)++] = src.y;
	d->v[(*index)++] = src.z;
	d->v[(*index)++] = g_color[i][0];
	d->v[(*index)++] = g_color[i][1];
	d->v[(*index)++] = g_color[i][2];
	i++;
}

void		ft_cutt_triangle(t_data *d, int *index, t_obj o, t_face *f)
{
	size_t		i;
	t_vertex	a;
	t_vertex	b;
	t_vertex	c;

	i = 0;
	c = o.v[f[f[0].len - 1].iv - 1];
	while (++i < f[0].len - 2)
	{
		a = o.v[f[i].iv - 1];
		b = o.v[f[i + 1].iv - 1];
		ft_push_triangle(d, a, index);
		ft_push_triangle(d, b, index);
		ft_push_triangle(d, c, index);
	}
}
