/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 14:11:07 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/01 11:04:04 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scop.h"

static int		ft_usage(char *cmd)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(" file.obj", 2);
	return (1);
}

static void		ft_init_opengl(void)
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

static void		ft_loop(t_data *d)
{
	short		okay;

	okay = 1;
	while (okay)
	{
		glfwSwapBuffers(d->win);
		ft_set_perspective(d);
		ft_render(d);
		glfwPollEvents();
		okay = ft_event(d);
	}
	glfwDestroyWindow(d->win);
	glfwTerminate();
}

static int		ft_init_mlx(t_data *d)
{
	if (!glfwInit())
		return (1);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	d->win = glfwCreateWindow(WIDTH, HEIGHT, "Scop by mmartin", NULL, NULL);
	if (!d->win)
		return (1);
	glfwMakeContextCurrent(d->win);
	glfwSetInputMode(d->win, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(d->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents();
	glfwSetCursorPos(d->win, WIDTH / 2.0, HEIGHT / 2.0);
	ft_init_opengl();
	ft_init(d);
	ft_loop(d);
	return (0);
}

int				main(int argc, char **argv)
{
	char	*ext;
	t_data	*d;

	if (argc != 2)
		return (ft_usage(argv[0]));
	ext = ft_strrchr(argv[1], '.');
	if (!ext || ft_strcmp(ext, ".obj"))
		return (ft_usage(argv[0]));
	d = ft_parse(argv[1]);
	if (!d)
	{
		ft_putendl_fd("Parse Error", 2);
		return (1);
	}
	return (ft_init_mlx(d));
}
