/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:54:27 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/16 13:54:29 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		find_normal_cyl(t_math *m, t_obj *o)
{
	double	m_;

	t_vector x = vector_sub(m->r.start, o->pos);
	m_ = vector_dot(vector_scale(m->t, o->dir), m->r.dir) + vector_dot(o->dir, x);
	m->norm = vector_sub(m->norm, vector_scale(m_, o->dir));
	return (1);
}

int		find_normal_cone(t_math *m, t_obj *o)
{
	double m_;
	double a;

	a = tan(o->radius);
	t_vector x = vector_sub(m->r.start, o->pos);
	m_ = vector_dot(vector_scale(m->t, o->dir), m->r.dir) + vector_dot(o->dir, x);
	m->norm = vector_sub(m->norm, vector_scale((1 + a * a), vector_scale(m_, o->dir)));
	return (1);
}

int		find_normal_all(t_math *m, t_obj *o, t_env *e)
{
	int	i;

	i = 1;
	m->scaled = vector_scale(m->t, m->r.dir);
	m->new_start = vector_add(m->r.start, m->scaled);
	m->norm = vector_sub(m->new_start, o->pos);
	if (o->inter == intersect_cyl)
		i = find_normal_cyl(m, o);
	else if (o->inter == intersect_cone)
		i = find_normal_cone(m, o);
	m->norm = unit_vector(&m->norm);
	if (i)
		find_light_value(m, e, &o->material);
	// float x = m->color.coef * 0.8;
	// m->color.coef = (o->inter == intersect_cyl) ? x : 0;
	// ray_start_and_dir(m);
	m->color.level++;
	return (i);
}

void		find_inter(t_math *m, t_env *e)
{
	int		c;
	int		i;

	// while ((m->color.level < 5))
	// {
		m->t = 20000.0f;
		c = -1;
		i = -1;
		while (++i < e->obj_count)
			if (e->objects[i].inter(m, &e->objects[i], &m->r))
				c = i;
		if (c == -1)
			return ;
		if (!(find_normal_all(m, &e->objects[c], e)))
			return ;

	// }
}

void		fill_mat(t_env *e, char *s)
{
	if (ft_strstr(s, "color") && e->i < e->obj_count)
	{
		if (ft_strchr(s, '-'))
			error_end("Shoud not be negative number");
		e->objects[e->i].material.diffuse.r = get_float(s);
		s = ft_strtrim(s);
		e->objects[e->i].material.diffuse.g = strtof(s + 13, NULL);
		e->objects[e->i].material.diffuse.b = strtof(s + 16, NULL);
		free(s);
	}
}

void		fill_structure(t_env *e, char *s)
{
	int n;

	n = get_number(s);
	if (ft_strstr(s, "objects"))
		e->obj_count = n;
	else if ((ft_strstr(s, "lights")))
		e->lgt_count = n;
	else if (ft_strstr(s, "FOV"))
		e->cam.fov = n;
}

void		find_shape(t_env *e, char *s)
{
	if (e->objects[e->i].inter == 0)
	{
		if (ft_strstr(s, "sphere"))
			e->objects[e->i].inter = intersect_sphere;
		else if (ft_strstr(s, "cone"))
			e->objects[e->i].inter = intersect_cone;
		else if (ft_strstr(s, "plane"))
			e->objects[e->i].inter = intersect_plane;
		else if (ft_strstr(s, "cylind"))
			e->objects[e->i].inter = intersect_cyl;
	}
}
