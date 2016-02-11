/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_tga.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 14:21:57 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/11 11:19:10 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_scop.h"

static void		ft_read_file(t_tex_tga *texture, char *filename)
{
	FILE	*file;
	short	bpp;
	size_t	size;

	if (!(file = fopen(filename, "rb")))
		return ;
	fseek(file, 2, SEEK_CUR);
	fread(&(*texture).type, sizeof(GLubyte), 1, file);
	if ((*texture).type != 2 && (*texture).type != 3)
	{
		fclose(file);
		return ;
	}
	fseek(file, 4 * sizeof(short) + sizeof(GLubyte), SEEK_CUR);
	fread(&(*texture).width, sizeof(short), 1, file);
	fread(&(*texture).height, sizeof(short), 1, file);
	fread(&(*texture).bit_count, sizeof(GLubyte), 1, file);
	fseek(file, 1, SEEK_CUR);
	bpp = (*texture).bit_count / 8;
	size = (*texture).width * (*texture).height * bpp;
	(*texture).data = (GLubyte *)ft_memalloc(sizeof(GLubyte) * size);
	fread((*texture).data, sizeof(GLubyte), size, file);
	fclose(file);
}

void			ft_load_tga(t_data *d)
{
	char	*filename;
	int		i;

	i = -1;
	d->texture = (t_tex_tga *)ft_memalloc(sizeof(*d->texture) * d->nb_obj);
	d->texid = (GLuint *)ft_memalloc(sizeof(*d->texid) * d->nb_obj);
	while (++i < d->nb_obj)
	{
		filename = ft_strjoin(d->filename,
				d->objs[i].m.map_kd ? d->objs[i].m.map_kd : "../uni.tga");
		ft_read_file(&d->texture[i], filename);
		ft_strdel(&filename);
		glGenTextures(1, &d->texid[i]);
		glBindTexture(GL_TEXTURE_2D, d->texid[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d->texture[i].width,
				d->texture[i].height, 0, GL_BGRA,
				GL_UNSIGNED_BYTE, d->texture[i].data);
		ft_memdel((void **)&d->texture[i].data);
	}
	ft_memdel((void **)&d->texture);
}
