/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 17:13:22 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/11 11:21:52 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "ft_scop.h"

static const t_mat_p	g_parse[] =
{
	{"newmtl", ft_new_material},
	{"Ns", ft_get_specular_exp},
	{"Ka", ft_get_ambient},
	{"Kd", ft_get_diffuse},
	{"Ks", ft_get_specular},
	{"Ni", ft_get_density},
	{"d", ft_get_transparency},
	{"illum", ft_get_light_calc},
	{"map_ka", ft_get_map_ka},
	{"map_kd", ft_get_map_kd},
	{"map_ks", ft_get_map_ks},
	{"map_ns", ft_get_map_ns},
	{"map_d", ft_get_map_d}
};

static int	ft_open_file_mat(const char *file_mat, const char *file_obj)
{
	char	*filename;
	int		fd;

	if (file_obj)
		filename = ft_strjoin(file_obj, file_mat);
	else
		filename = ft_strdup(file_mat);
	fd = open(filename, O_RDONLY);
	ft_strdel(&filename);
	return (fd);
}

void		ft_get_materials(t_data *d, char *file_mat, char *file_obj)
{
	int		fd;
	char	*line;
	char	**tab;
	int		i;
	size_t	j;

	i = -1;
	fd = ft_open_file_mat(file_mat, file_obj);
	while (get_next_line(fd, &line) > 0 && !(j = 0))
	{
		tab = ft_strsplit_space(line);
		if (tab[0] && tab[0][0] != '#')
		{
			while (j < sizeof(g_parse) / sizeof(*g_parse))
			{
				if (!ft_strcasecmp(tab[0], g_parse[j].cmp))
					g_parse[j].func(d, &i, tab);
				j++;
			}
		}
		ft_tabdel(&tab);
		ft_strdel(&line);
	}
	close(fd);
}
