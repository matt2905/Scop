/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_tga.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 14:21:57 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/11 18:45:30 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_scop.h"

static void		ft_load_uncompressed(t_tex_tga *texture, FILE *file, int nop)
{
	GLuint	i;

	fread(texture->header, sizeof(texture->header), 1, file);
	texture->width = texture->header[1] * 256 + texture->header[0];
	texture->height = texture->header[3] * 256 + texture->header[2];
	texture->bpp = texture->header[4];
	if (texture->width <= 0 || texture->height <= 0 ||
			(texture->bpp != 24 && texture->bpp != 32))
		return ;
	texture->type = texture->bpp == 24 ? GL_RGB : GL_RGBA;
	texture->bpp_file = texture->bpp / 8;
	texture->size = texture->bpp_file * texture->width * texture->height;
	texture->data = (GLubyte *)ft_memalloc(texture->size);
	if (!nop && !(i = 0))
	{
		fread(texture->data, 1, texture->size, file);
		while (i < texture->size)
		{
			texture->data[i] ^= texture->data[i + 2];
			texture->data[i + 2] ^= texture->data[i];
			texture->data[i] ^= texture->data[i + 2];
			i += texture->bpp_file;
		}
	}
}

static void		ft_read_cp(t_tex_tga *t, FILE *f, GLuint *cp, GLuint *cb)
{
	GLubyte		chunkheader;
	GLubyte		colorbuffer[4];
	short		i;
	short		flag;

	i = -1;
	chunkheader = 0;
	fread(&chunkheader, sizeof(GLubyte), 1, f);
	flag = chunkheader < 128 ? 1 : 0;
	chunkheader = chunkheader < 128 ? chunkheader + 1 : chunkheader - 127;
	if (!flag)
		fread(colorbuffer, 1, t->bpp_file, f);
	while (++i < chunkheader)
	{
		if (flag)
			fread(colorbuffer, 1, t->bpp_file, f);
		t->data[(*cb)++] = colorbuffer[2];
		t->data[(*cb)++] = colorbuffer[1];
		t->data[(*cb)++] = colorbuffer[0];
		if (t->bpp_file == 4)
			t->data[(*cb)++] = colorbuffer[3];
		(*cp)++;
		if ((*cb) > t->size)
			return ;
	}
}

static void		ft_load_compressed(t_tex_tga *texture, FILE *file)
{
	GLuint		pixelcount;
	GLuint		currentpixel;
	GLuint		currentbyte;

	ft_load_uncompressed(texture, file, 1);
	currentpixel = 0;
	currentbyte = 0;
	pixelcount = texture->height * texture->width;
	while (currentpixel < pixelcount)
	{
		ft_read_cp(texture, file, &currentpixel, &currentbyte);
		if (currentpixel > pixelcount)
		{
			ft_putendl_fd("Too many pixels read", 2);
			return ;
		}
	}
}

static void		ft_read_file(t_tex_tga *texture, char *filename)
{
	static GLubyte		compressed[12] = {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	static GLubyte		uncompressed[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	FILE				*file;
	t_tga_header		header;

	if (!(file = fopen(filename, "rb")))
		return ;
	fread(&header, sizeof(t_tga_header), 1, file);
	if (!ft_memcmp(compressed, &header, sizeof(header)))
		ft_load_compressed(texture, file);
	else if (!ft_memcmp(uncompressed, &header, sizeof(header)))
		ft_load_uncompressed(texture, file, 0);
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
		glTexImage2D(GL_TEXTURE_2D, 0, d->texture[i].type, d->texture[i].width,
				d->texture[i].height, 0, d->texture[i].type,
				GL_UNSIGNED_BYTE, d->texture[i].data);
		ft_memdel((void **)&d->texture[i].data);
	}
	ft_memdel((void **)&d->texture);
}
