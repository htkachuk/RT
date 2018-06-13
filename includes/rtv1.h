/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:20:09 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/09 15:20:11 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "vectors.h"
# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include "../libft/get_next_line.h"
# define MIN(a,b) (((a) < (b)) ? (a) : (b))
# define PIOVER180 0.0174532925199
# define WIDTH 800
# define HEIGHT 800

typedef struct		s_ray
{
	t_vector		start;
	t_vector		dir;
}					t_ray;

typedef struct		s_img
{
	void			*self;
	char			*pxl;
	int				bpp;
	int				bpl;
	int				endian;
}					t_img;

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	int				level;
	double			coef;
	double			op;
}					t_color;

typedef struct		s_light
{
	t_vector		pos;
}					t_lgt;

typedef struct		s_mtr
{
	t_color			diffuse;
	double			spec;
}					t_mtr;

typedef	struct		s_math
{
	t_vector		scaled;
	t_vector		new_start;
	t_vector		norm;
	float			t;
	double			x[2];
	t_ray			r;
	t_color			color;
	t_ray			l_ray;
}					t_math;

typedef struct		s_object
{
	t_vector		pos;
	double			radius;
	t_mtr			material;
	int				(*inter)(t_math *m, struct s_object *s, t_ray *r);
	t_vector		rot;
	t_vector		dir;
}					t_obj;

typedef struct		s_cam
{
	t_vector		pos;
	t_vector		rot_deg;
	float			fov;
}					t_cam;

typedef struct		s_env
{
	t_obj			*objects;
	t_lgt			*lights;
	t_img			*img;
	void			*mlx;
	void			*win;
	t_cam			cam;
	int				fd;
	int				i;
	int				cur;
	int				obj_count;
	int				lgt_count;
	int				real_obj_cnt;
	int				y;
	int				x;
	int				limit;
	double			t[2];
}					t_env;

int					end(void);
void				default_init(t_env *e);
void				fill_mat(t_env *e, char *s);
void				find_shape(t_env *e, char *s);
int					get_number(char *str);
void				fill_structure(t_env *e, char *s);
void				fill_obj(t_env *e, char *s);
void				fill_cam(t_env *e, char *s);
void				fill_obj_pos(t_env *e, char *s);
void				fill_lights(t_env *e, char *s);
int					error_end(char *str);
int					ft_parse(t_env *e);
void				ft_put_pxl(t_img *re, int x, int y, t_color *c);
int					intersect_sphere(t_math *m, t_obj *s, t_ray *r);
int					intersect_cyl(t_math *m, t_obj *c, t_ray *r);
int					intersect_cone(t_math *m, t_obj *cone, t_ray *r);
int					intersect_plane(t_math *m, t_obj *p, t_ray *r);
void				object_test_init(t_obj obj[3], t_lgt lights[3]);
void				raytrace_helper(t_math *m, t_obj *o, t_env *e);
void				find_light_value(t_math *m, t_env *e, t_mtr *cur_m);
void				find_inter(t_math *m, t_env *e);
void 				*raytrace(void *data);
void 				thread(t_env *e); 
void 				init_ray(t_ray *r, int x, int y, t_env *e);
void				init(t_env *e);
void				set_color(t_color *c);
int					ft_parse(t_env *e);
float				get_float(char *str);
void				check_rot(t_obj *o, t_vector *dir);
int					keyboard(int keycode, void *data);
void				obj_init(t_env *e);
void				ray_start_and_dir(t_math *m);

#endif
