/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scop.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 16:16:04 by mmartin           #+#    #+#             */
/*   Updated: 2016/01/29 13:22:16 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCOP_H
# define FT_SCOP_H

# include <string.h>
# include <OpenGL/gl3.h>
# define GLFW_INCLUDE_NONE
# include <GLFW/glfw3.h>

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
	t_vertex	*v;

	int			nb_vt;
	t_vertex	*vt;

	int			nb_vn;
	t_vertex	*vn;

	int			nb_f;
	t_face		**f;

	char		*name;
	t_mat		m;
}				t_obj;

typedef struct	s_data
{
	GLFWwindow	*win;
	GLuint		program;

	t_mat		*mat;
	int			nb_mat;
	t_obj		*objs;
	int			nb_obj;

	float		rotate;
	t_vertex	camera_pos;
	t_vertex	camera_look;
	t_vertex	camera_up;

	float		light_pos[3];
	float		light_col[3];

	GLuint		proj_id;
	float		*projection;
	GLuint		view_id;
	float		*view;
	GLuint		mode_id;
	float		*model;

	float		angle_horizontal;
	float		angle_vertical;
	float		fov;
	float		speed;
	float		mouse_speed;
	float		last_time;

	GLuint		vid;
	float		*v;
	size_t		size_v;
	GLuint		iid;
	size_t		*i;
	size_t		size_i;
}				t_data;

/*
**	Structure for array of pointer of function
*/

typedef struct	s_key
{
	int			key;
	int			(*func)(t_data *, double);
}				t_key;

t_data			*ft_parse(char *file);

/*
**		srcs/ft_vector.c
*/

t_vertex		ft_vector_min(t_vertex a, t_vertex b);
t_vertex		ft_vector_add(t_vertex a, t_vertex b);
t_vertex		ft_vector_neg(t_vertex src);
t_vertex		ft_float_to_vector(float *src);
t_vertex		ft_cross(t_vertex a, t_vertex b);

/*
**		srcs/ft_vector_tool.c
*/

void			ft_normalize_vector(t_vertex *src);
float			ft_dot(t_vertex a, t_vertex b);
void			ft_search_center(t_data *d, t_vertex *center);

/*
**		srcs/ft_matrix.c
*/

float			*ft_new_matrix(void);

/*
**		srcs/ft_matrix_cal.c
*/

float			*ft_translate(t_vertex center);
float			*ft_look_at(t_vertex e, t_vertex c, t_vertex u);
float			*ft_mult_matrix(float *a, float *b);

/*
**		srcs/ft_event.c
*/
int				ft_event(t_data *d);
void			ft_render(t_data *d);

int				ft_escape(t_data *d, double deltatime);
int				ft_right(t_data *d, double deltatime);
int				ft_left(t_data *d, double deltatime);
int				ft_up(t_data *d, double deltatime);
int				ft_down(t_data *d, double deltatime);
int				ft_forward(t_data *d, double deltatime);
int				ft_backward(t_data *d, double deltatime);

void			ft_init(t_data *d);
void			ft_set_perspective(t_data *d);
void			ft_create_objects(t_data *d);
GLuint			ft_get_shader(GLenum type, const char *file);
void			ft_attach_shader(GLuint program, GLuint shader);
void			ft_triangulate(t_data *d);

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
