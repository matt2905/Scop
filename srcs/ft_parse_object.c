/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 11:06:43 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/08 16:45:51 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

void	ft_get_vertex(t_data *d, t_obj *new, char **tab)
{
	t_vertex	v;
	t_vertex	*save;

	(void)d;
	if (ft_tablen(tab) != 4)
		return ;
	new->nb_v++;
	v.x = ft_atof(tab[1]);
	v.y = ft_atof(tab[2]);
	v.z = ft_atof(tab[3]);
	save = (t_vertex *)ft_memalloc(sizeof(*save) * (new->nb_v));
	if (new->v)
	{
		ft_memcpy(save, new->v, sizeof(*new->v) * (new->nb_v - 1));
		ft_memdel((void **)&new->v);
	}
	save[new->nb_v - 1] = v;
	new->v = save;
}

void	ft_get_texture(t_data *d, t_obj *new, char **tab)
{
	t_vertex	vt;
	t_vertex	*save;

	(void)d;
	if (ft_tablen(tab) != 3)
		return ;
	new->nb_vt++;
	vt.x = ft_atof(tab[1]);
	vt.y = ft_atof(tab[2]);
	vt.z = 0;
	save = (t_vertex *)ft_memalloc(sizeof(*save) * (new->nb_vt));
	if (new->vt)
	{
		ft_memcpy(save, new->vt, sizeof(*new->vt) * (new->nb_vt - 1));
		ft_memdel((void **)&new->vt);
	}
	save[new->nb_vt - 1] = vt;
	new->vt = save;
}

void	ft_get_normalize(t_data *d, t_obj *new, char **tab)
{
	t_vertex	vn;
	t_vertex	*save;

	(void)d;
	if (ft_tablen(tab) != 4)
		return ;
	new->nb_vn++;
	vn.x = ft_atof(tab[1]);
	vn.y = ft_atof(tab[2]);
	vn.z = ft_atof(tab[3]);
	save = (t_vertex *)ft_memalloc(sizeof(*save) * (new->nb_vn));
	if (new->vn)
	{
		ft_memcpy(save, new->vn, sizeof(*new->vn) * (new->nb_vn - 1));
		ft_memdel((void **)&new->vn);
	}
	save[new->nb_vn - 1] = vn;
	new->vn = save;
}

void	ft_get_material(t_data *d, t_obj *new, char **tab)
{
	int		i;

	i = 0;
	if (ft_tablen(tab) != 2)
		return ;
	while (i < d->nb_mat)
	{
		if (!ft_strcmp(d->mat[i].name, tab[1]))
		{
			new->m = d->mat[i];
			i = d->nb_mat;
		}
		else
			i++;
	}
}

void	ft_get_face(t_data *d, t_obj *new, char **tab)
{
	char	**indices;
	int		len;
	int		i;
	t_face	*f;
	t_face	**save;

	(void)d;
	new->nb_f++;
	i = 0;
	len = ft_tablen(tab);
	f = (t_face *)ft_memalloc(sizeof(*f) * (len + 1));
	f[0].len = len;
	while (++i < len && (indices = ft_strsplit(tab[i], '/')))
	{
		f[i].iv = ft_atof(indices[0]);
		f[i].ivt = (ft_tablen(indices) > 1 ? ft_atof(indices[1]) : 0);
		f[i].ivn = (ft_tablen(indices) > 2 ? ft_atof(indices[2]) : 0);
		ft_tabdel(&indices);
	}
	save = (t_face **)ft_memalloc(sizeof(*f) * (new->nb_f));
	if (new->f)
		ft_memcpy(save, new->f, sizeof(*new->f) * (new->nb_f - 1)),
		ft_memdel((void **)&new->f);
	save[new->nb_f - 1] = f;
	new->f = save;
}
