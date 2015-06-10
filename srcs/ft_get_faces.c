/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_faces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 11:07:54 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/10 11:54:30 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static int	ft_count_previous_vertex(t_data *d)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (i < d->nb_obj - 1)
	{
		len += d->objs[i].nb_v;
		i++;
	}
	return (len);
}

static int	ft_count_previous_texture(t_data *d)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (i < d->nb_obj - 1)
	{
		len += d->objs[i].nb_vt;
		i++;
	}
	return (len);

}

static int	ft_count_previous_normal(t_data *d)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (i < d->nb_obj - 1)
	{
		len += d->objs[i].nb_vn;
		i++;
	}
	return (len);

}

static void	ft_get_face(t_data *d, t_face *f, int len, char **tab)
{
	char	**indices;
	int		i;
	int		p_v;
	int		p_vt;
	int		p_vn;

	p_v = ft_count_previous_vertex(d);
	p_vt = ft_count_previous_texture(d);
	p_vn = ft_count_previous_normal(d);
	i = 0;
	while (++i < len)
	{
		indices = ft_strsplit(tab[i], '/');
		f[i].iv = ft_atof(indices[0]) - p_v;
		f[i].ivt = (ft_tablen(indices) > 1 ? ft_atof(indices[1]) - p_vt : 0);
		f[i].ivn = (ft_tablen(indices) > 2 ? ft_atof(indices[2]) - p_vn : 0);
		ft_tabdel(&indices);
	}
}

void		ft_get_faces(t_data *d, t_obj *new, char **tab)
{
	int		len;
	t_face	*f;
	t_face	**save;

	new->nb_f++;
	len = ft_tablen(tab);
	f = (t_face *)ft_memalloc(sizeof(*f) * (len + 1));
	f[0].len = len;
	ft_get_face(d, f, len, tab);
	save = (t_face **)ft_memalloc(sizeof(*save) * (new->nb_f));
	if (new->f)
	{
		ft_memcpy(save, new->f, sizeof(*new->f) * (new->nb_f - 1));
		ft_memdel((void **)&new->f);
	}
	save[new->nb_f - 1] = f;
	new->f = save;
}
