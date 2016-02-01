/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 13:35:07 by mmartin           #+#    #+#             */
/*   Updated: 2016/02/01 12:26:07 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "ft_scop.h"

static const t_key	g_key_func[] =
{
	{GLFW_KEY_ESCAPE, ft_escape},
	{GLFW_KEY_UP, ft_forward},
	{GLFW_KEY_DOWN, ft_backward},
	{GLFW_KEY_RIGHT, ft_right},
	{GLFW_KEY_LEFT, ft_left},
	{GLFW_KEY_W, ft_up},
	{GLFW_KEY_S, ft_down}
};

int		ft_escape(t_data *d, double deltatime)
{
	(void)deltatime;
	ft_delete_obj(d);
	glDeleteBuffers(1, &d->vid);
	ft_memdel((void **)&d->v);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	return (0);
}

void	ft_render(t_data *d)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(d->program);
	glUniformMatrix4fv(d->mode_id, 1, GL_FALSE, &d->model[0]);
	glUniformMatrix4fv(d->view_id, 1, GL_FALSE, &d->view[0]);
	glUniformMatrix4fv(d->proj_id, 1, GL_FALSE, &d->projection[0]);
	glDrawArrays(GL_TRIANGLES, 0, d->size_v / 8);
}

void	ft_compute_mouse(t_data *d)
{
	d->camera_look.x = cos(d->angle_vertical) * sin(d->angle_horizontal);
	d->camera_look.y = sin(d->angle_vertical);
	d->camera_look.z = cos(d->angle_vertical) * cos(d->angle_horizontal);
}

int		ft_event(t_data *d)
{
	float			delta_time;
	double			x;
	double			y;
	int				i;

	glfwGetCursorPos(d->win, &x, &y);
	glfwSetCursorPos(d->win, (float)WIDTH / 2.0, (float)HEIGHT / 2.0);
	d->angle_horizontal += d->mouse_speed * ((float)WIDTH / 2.0 - x);
	d->angle_vertical += d->mouse_speed * ((float)HEIGHT / 2.0 - y);
	delta_time = glfwGetTime() - d->last_time;
	d->last_time = glfwGetTime();
	i = -1;
	ft_compute_mouse(d);
	while (++i < 7)
		if (glfwGetKey(d->win, g_key_func[i].key) == GLFW_PRESS)
			if (!g_key_func[i].func(d, delta_time))
				return (0);
	if (glfwWindowShouldClose(d->win))
		return (0);
	return (1);
}
