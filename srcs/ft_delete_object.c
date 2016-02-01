/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 11:00:30 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/01 12:34:26 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static void	ft_delete_face(t_obj *o)
{
	int		y;

	y = 0;
	if (!o->f)
		return ;
	while (y < o->nb_f)
	{
		ft_memdel((void **)&o->f[y]);
		y++;
	}
	ft_memdel((void **)&o->f);
}

void		ft_delete_obj(t_data *d)
{
	int		i;

	i = 0;
	while (i < d->nb_obj)
	{
		ft_strdel(&d->objs[i].name);
		ft_memdel((void **)&d->objs[i].v);
		ft_memdel((void **)&d->objs[i].vt);
		ft_memdel((void **)&d->objs[i].vn);
		ft_delete_face(&d->objs[i]);
		ft_memdel((void **)&d->objs[i].m.name);
		ft_memdel((void **)&d->objs[i].m.map_ka);
		ft_memdel((void **)&d->objs[i].m.map_kd);
		ft_memdel((void **)&d->objs[i].m.map_ks);
		ft_memdel((void **)&d->objs[i].m.map_ns);
		ft_memdel((void **)&d->objs[i].m.map_d);
		i++;
	}
	ft_memdel((void **)&d->objs);
	d->objs = NULL;
	d->nb_obj = 0;
}
