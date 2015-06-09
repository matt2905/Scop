/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 17:51:51 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/09 12:02:07 by mmartin          ###   ########.fr       */
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
	int		obj;

	obj = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (!(d = (t_data *)ft_memalloc(sizeof(*d))))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strncmp(line, "mtllib ", 7))
			ft_get_materials(d, line + 7, file);
		else if (!ft_strncmp(line, "o ", 2))
			ft_get_object(d, fd, line);
		ft_strdel(&line);
	}
	close(fd);
	return (d);
}
