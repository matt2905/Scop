/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 17:11:04 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/10 10:07:13 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <OpenGL/GL.h>
#include "libft.h"
#include "printf.h"

static char	*ft_load_shader(const char *file)
{
	char	*src;
	FILE	*fp;
	size_t	size;

	if (!(fp = fopen(file, "r")))
	{
		ft_printf("ft_load_shader(): Unable to open %s\n", file);
		return (NULL);
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	if (!(src = (char *)ft_memalloc(sizeof(*src) * (size + 1))))
	{
		fclose(fp);
		ft_putendl_fd("ft_load_shader(): malloc failed", 2);
		return (NULL);
	}
	size = fread(src, size, 1, fp);
	src[size] = '\0';
	return (src);
}

GLuint		ft_get_shader(GLenum type, const char *file)
{
	char	*source;
	char	*log;
	GLuint	shader;
	GLint	len;
	GLint	ret;

	if (!(source = ft_load_shader(file)))
		return (0);
	shader = glCreateShader(type);
	len = ft_strlen(source);
	glShaderSource(shader, 1, (const char **)&source, &len);
	glCompileShader(shader);
	ft_strdel(&source);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		log = (char *)ft_memalloc(sizeof(*log) * len);
		glGetShaderInfoLog(shader, len, &ret, log);
		ft_printf("ft_get_shader(): Unable to compile %s: %s\n", file, log);
		ft_strdel(&log);
		glDeleteShader(shader);
		return (0);
	}
	return (shader);
}

void		ft_attachShader(GLuint program, GLuint shader)
{
	if (shader)
	{
		glAttachShader(program, shader);
		glDeleteShader(shader);
	}
}
