/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 10:53:50 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/10 12:23:47 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static float	*ft_create_object(t_obj o, size_t size)
{
	float	*v;
	int		i;

	i = 0;
	v = (float *)ft_memalloc(sizeof(*v) * size);
	while (i < o.nb_f)
	{
		v[i] = o.f[i][1].iv;
		v[i + 1] = o.f[i][2].iv;
		v[i + 2] = o.f[i][3].iv;
		v[i + 3] = o.f[i][4].iv;
		v[i + 4] = o.f[i][1].ivn;
		v[i + 5] = o.f[i][2].ivn;
		v[i + 6] = o.f[i][3].ivn;
		v[i + 7] = o.f[i][4].ivn;
		i++;
	}
	return (v);
}

void			ft_create_objects(t_data *d)
{
	GLuint	id;
	int		i;
	size_t	size;
	float	*v;

	i = 0;
	while (i < d->nb_obj)
	{
		size = (d->objs[i].nb_f + 1) * 2 * 8;
		v = ft_create_object(d->objs[i], size);
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, v, GL_STATIC_DRAW);
		ft_memdel((void **)&v);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(float) * 8, 0);
		glNormalPointer(GL_FLOAT, sizeof(float) * 8, (const GLvoid *)(sizeof(float) * 3));
		i++;
	}
}
