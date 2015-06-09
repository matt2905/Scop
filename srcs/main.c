/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 14:11:07 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/09 12:29:14 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <mlx_opengl.h>
#include "libft.h"
#include "ft_scop.h"

int		ft_usage(char *cmd)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(" file.obj", 2);
	return (1);
}

int		ft_init_mlx(t_data *d)
{
	if ((d->mlx = mlx_init()) == NULL)
		return (1);
	d->win = mlx_new_opengl_window(d->mlx, 1024, 1024, "Scop by mmartin");
	mlx_opengl_window_set_context(d->win);
	mlx_expose_hook(d->win, &ft_expose, d);
	mlx_hook(d->win, 2, 0, ft_key_press, d);
	mlx_loop_hook(d->mlx, &ft_loop_hook, d);
	mlx_loop(d->mlx);
	return (0);
}

int		main(int argc, char **argv)
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
