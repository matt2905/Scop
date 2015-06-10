/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scop.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 16:16:04 by mmartin           #+#    #+#             */
/*   Updated: 2015/06/10 13:33:38 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCOP_H
# define FT_SCOP_H

# include <OpenGL/GL.h>

# define WIDTH	1024
# define HEIGHT	1024

typedef struct	s_vertex
{
	float		x;
	float		y;
	float		z;
}				t_vertex;

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

/*
**	ns : material specular exponent is multiplied by the texture value
**	ka : material ambient is multiplied by the texture value
**	kd : material diffuse is multiplied by the texture value
**	ks : material specular is multiplied by the texture value
**	ni : optical_density
**	d : material transparency is multiplied by the texture value
**	illum : pointer of function for calculate the color.
*/

typedef struct	s_mat
{
	char		*name;
	float		ns;
	t_color		ka;
	t_color		kd;
	t_color		ks;
	float		ni;
	float		d;
	t_color		(*illum)();
	char		*map_ka;
	char		*map_kd;
	char		*map_ks;
	char		*map_ns;
	char		*map_d;
}				t_mat;

typedef struct	s_face
{
	unsigned	len;
	unsigned	iv;
	unsigned	ivt;
	unsigned	ivn;
}				t_face;

/*
**	v : all vertex of object
**	vt : coordinate of texture
**	vn : normalize vertex
**	m : material use for rendering
**	f : all set of v/vt/vn
*/

typedef struct	s_obj
{
	int			nb_v;
	int			nb_vt;
	int			nb_vn;
	int			nb_f;
	char		*name;
	t_vertex	*v;
	t_vertex	*vt;
	t_vertex	*vn;
	t_mat		m;
	t_face		**f;
}				t_obj;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_mat		*mat;
	t_obj		*objs;
	int			nb_mat;
	int			nb_obj;
	GLuint		program;
	GLuint		camera_pos_loc;
	GLuint		light_pos_loc;
	GLuint		light_col_loc;
	float		rotate;
	float		camera_pos[3];
	float		light_pos[3];
	float		light_col[3];
}				t_data;

t_data			*ft_parse(char *file);

/*
**	ft_mlx_event.c
*/
int				ft_key_press(int keycode, t_data *d);
int				ft_expose(t_data *d);
int				ft_loop_hook(t_data *d);
void			ft_init(t_data *d);
void			ft_set_perspective(float fov, float a, float near, float far);
void			ft_create_objects(t_data *d);
GLuint			ft_get_shader(GLenum type, const char *file);
void			ft_attach_shader(GLuint program, GLuint shader);

void			ft_delete_obj(t_data *d);
void			ft_delete_face(t_obj *o);

/*
**	function for parse materials
*/
void			ft_get_materials(t_data *d, char *file_mat, char *file_obj);

typedef struct	s_mat_p
{
	char		*cmp;
	void		(*func)(t_data *, int *, char **);
}				t_mat_p;

void			ft_new_material(t_data *d, int *i, char **tab);
void			ft_get_specular_exp(t_data *d, int *i, char **tab);
void			ft_get_ambient(t_data *d, int *i, char **tab);
void			ft_get_diffuse(t_data *d, int *i, char **tab);
void			ft_get_specular(t_data *d, int *i, char **tab);
void			ft_get_density(t_data *d, int *i, char **tab);
void			ft_get_transparency(t_data *d, int *i, char **tab);

void			ft_get_light_calc(t_data *d, int *i, char **tab);

/*
**	function for parse one object.
*/
void			ft_get_object(t_data *d, int fd, char *tmp);

typedef struct	s_parse
{
	char		*cmp;
	void		(*func)(t_data *, t_obj *, char **);
}				t_parse;

void			ft_get_vertex(t_data *d, t_obj *n, char **tab);
void			ft_get_texture(t_data *d, t_obj *n, char **tab);
void			ft_get_normalize(t_data *d, t_obj *n, char **tab);
void			ft_get_material(t_data *d, t_obj *n, char **tab);
void			ft_get_fragments(t_data *d, t_obj *n, char **tab);

#endif
