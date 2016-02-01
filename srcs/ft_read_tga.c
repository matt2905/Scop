/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_tga.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 14:21:57 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/01 18:00:50 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_scop.h"

static void		ft_read_file(t_data *d, char *filename)
{
	FILE	*file;
	short	bpp;
	size_t	size;

	if (!(file = fopen(ft_strjoin("resources/", filename), "rb")))
		return ;
	fseek(file, 2, SEEK_CUR);
	fread(&d->texture.type, sizeof(GLubyte), 1, file);
	if (d->texture.type != 2 && d->texture.type != 3)
	{
		fclose(file);
		return ;
	}
	fseek(file, 4 * sizeof(short) + sizeof(GLubyte), SEEK_CUR);
	fread(&d->texture.width, sizeof(short), 1, file);
	fread(&d->texture.height, sizeof(short), 1, file);
	fread(&d->texture.bit_count, sizeof(GLubyte), 1, file);
	fseek(file, 1, SEEK_CUR);
	bpp = d->texture.bit_count / 8;
	size = d->texture.width * d->texture.height * bpp;
	d->texture.data = (GLubyte *)ft_memalloc(sizeof(GLubyte) * size);
	fread(d->texture.data, sizeof(GLubyte), size, file);
	fclose(file);
}

void		ft_load_tga(t_data *d)
{
	ft_read_file(d, d->mat[0].map_kd);
	glGenTextures(1, &d->texid);
	glBindTexture(GL_TEXTURE_2D, d->texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d->texture.width,
			d->texture.height, 0, GL_BGRA,
			GL_UNSIGNED_BYTE, d->texture.data);
	ft_memdel((void **)&d->texture.data);
}
