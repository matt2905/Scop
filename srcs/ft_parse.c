/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 17:51:51 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/11 11:21:42 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ft_scop.h"
#include "libft.h"

t_data		*ft_parse(char *file)
{
	int		fd;
	t_data	*d;
	char	*line;
	char	**tab;
	char	*tmp;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (!(d = (t_data *)ft_memalloc(sizeof(*d))))
		return (NULL);
	tmp = ft_strrchr(file, '/');
	*(tmp + 1) = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit_space(line);
		if (!ft_strcmp(tab[0], "mtllib"))
			ft_get_materials(d, tab[1], file);
		else if (!ft_strcmp(tab[0], "o") || !ft_strcmp(tab[0], "v"))
			ft_get_object(d, fd, line);
		ft_strdel(&line);
		ft_tabdel(&tab);
	}
	close(fd);
	d->filename = file;
	return (d);
}
