/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:53:50 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/11 16:48:31 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static float	*ft_create_object(t_obj o, float *v, int *begin)
{
	int			index;
	int			i;
	unsigned	j;

	index = *begin;
	i = -1;
	while (++i < o.nb_f)
	{
		j = 0;
		while (++j < o.f[i][0].len)
		{
			v[index] = o.v[o.f[i][j].iv - 1].x;
			v[index + 1] = o.v[o.f[i][j].iv - 1].y;
			v[index + 2] = o.v[o.f[i][j].iv - 1].z;
			v[index + 3] = o.nb_vn ? o.v[o.f[i][j].ivn - 1].x : 0;
			v[index + 4] = o.nb_vn ? o.v[o.f[i][j].ivn - 1].y : 0;
			v[index + 5] = o.nb_vn ? o.v[o.f[i][j].ivn - 1].z : 0;
			index += 6;
		}
	}
	*begin = index;
	return (v);
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
			size += (o[i].f[j][0].len - 1) * 2;
			j++;
		}
		i++;
	}
	return (size * 3);
}

static void		ft_init_object_opengl(t_data *d, float *v)
{
	GLuint	id;

	(void)d;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(float) * 6, 0);
	glNormalPointer(GL_FLOAT, sizeof(float) * 6,
			(const GLvoid *)(sizeof(float) * 3));
}

void			ft_create_objects(t_data *d)
{
	int		i;
	float	*v;
	int		begin;

	i = 0;
	begin = 0;
	d->size = ft_get_size(d->objs, d->nb_obj);
	v = (float *)ft_memalloc(sizeof(*v) * d->size);
	while (i < d->nb_obj)
	{
		ft_create_object(d->objs[i], v, &begin);
		i++;
	}
	if (!v)
		return ;
	ft_init_object_opengl(d, v);
	ft_memdel((void **)&v);
}
