/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 11:00:30 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/03 15:49:05 by mmartin          ###   ########.fr       */
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

void		ft_delete_mat(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->nb_mat)
	{
		ft_memdel((void **)&d->mat[i].name);
		ft_memdel((void **)&d->mat[i].map_ka);
		ft_memdel((void **)&d->mat[i].map_kd);
		ft_memdel((void **)&d->mat[i].map_ks);
		ft_memdel((void **)&d->mat[i].map_ns);
		ft_memdel((void **)&d->mat[i].map_d);
	}
	ft_memdel((void **)&d->mat);
}

void		ft_delete_obj(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->nb_obj)
	{
		ft_strdel(&d->objs[i].name);
		ft_memdel((void **)&d->objs[i].v);
		ft_memdel((void **)&d->objs[i].vt);
		ft_memdel((void **)&d->objs[i].vn);
		ft_delete_face(&d->objs[i]);
	}
	ft_memdel((void **)&d->objs);
	d->objs = NULL;
	d->nb_obj = 0;
}
