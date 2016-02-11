/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 10:44:59 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/05 12:10:05 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static const t_parse	g_parse[] =
{
	{"v", ft_get_vertex},
	{"vt", ft_get_texture},
	{"vn", ft_get_normalize},
	{"usemtl", ft_get_material},
	{"f", ft_get_fragments}
};

static void		ft_loop_object(t_data *d, int fd, t_obj *new)
{
	char	*line;
	char	**tab;
	size_t	i;
	size_t	len;

	len = sizeof(g_parse) / sizeof(t_parse);
	while (get_next_line(fd, &line) > 0 && ft_strncmp(line, "o ", 2))
	{
		i = -1;
		tab = ft_strsplit_space(line);
		while (++i < len)
		{
			if (!ft_strcmp(g_parse[i].cmp, tab[0]))
				g_parse[i].func(d, new, tab);
		}
		ft_tabdel(&tab);
		ft_strdel(&line);
	}
	if (line)
	{
		ft_get_object(d, fd, line);
		ft_strdel(&line);
	}
}

static void		ft_first_line(t_data *d, t_obj *new, char *tmp)
{
	char	**tab;
	size_t	i;
	size_t	len;

	len = sizeof(g_parse) / sizeof(t_parse);
	i = -1;
	tab = ft_strsplit_space(tmp);
	while (++i < len)
	{
		if (!ft_strcmp(g_parse[i].cmp, tab[0]))
			g_parse[i].func(d, new, tab);
	}
	ft_tabdel(&tab);
}

static t_obj	ft_init_object(t_obj new)
{
	new.nb_v = 0;
	new.nb_vt = 0;
	new.nb_vn = 0;
	new.nb_f = 0;
	new.v = NULL;
	new.vt = NULL;
	new.vn = NULL;
	new.f = NULL;
	return (new);
}

void			ft_get_object(t_data *d, int fd, char *tmp)
{
	t_obj	*obj;
	t_obj	new;
	int		len;

	d->nb_obj++;
	len = d->nb_obj;
	new = ft_init_object(new);
	obj = (t_obj *)ft_memalloc(sizeof(*obj) * (d->nb_obj + 1));
	if (d->objs)
	{
		ft_memcpy(obj, d->objs, sizeof(*d->objs) * (d->nb_obj - 1));
		ft_memdel((void **)&d->objs);
		obj[len - 1] = new;
		d->nb_obj = len;
	}
	d->objs = obj;
	if (!ft_strncmp(tmp, "o ", 2))
		d->objs[len - 1].name = ft_strdup(tmp + 2);
	else
		ft_first_line(d, &d->objs[len - 1], tmp);
	ft_loop_object(d, fd, &d->objs[len - 1]);
}
