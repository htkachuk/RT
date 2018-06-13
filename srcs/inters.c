/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:28:09 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/14 17:28:11 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int		if_cut(t_math *m, t_obj *o, int id)
{
	double		m1;
	double		m2;
	int			max;
	int			min;
	t_vector	x;

	min = ((id == 0) ? 0 : 1); // 1 for conuse, this value from scene
	max = ((id == 0) ? 100 : 100); //both values from scene (id = 0) => figure = cylinder
	x = vector_sub(m->r.start, o->pos);
	m1 = vector_dot(vector_scale(m->x[0], o->dir), m->r.dir) + vector_dot(o->dir, x);
	if (m1 < min || m1 > max)
		return (0);
	m2 = vector_dot(vector_scale(m->x[1], o->dir), m->r.dir) + vector_dot(o->dir, x);
	if (m2 < min || m2 > max)
		return (0);
	return (1);
}

int				discriminant(double a, double b, double c, t_math *m, t_obj *o, int id)
{
	double		disc;
	double		t[2];

	disc = (b * b) - (4.0 * a * c);
	if (disc < 0)
		return (0);
	t[0] = (-b - sqrt(disc)) / (2.0 * a);
	t[1] = (-b + sqrt(disc)) / (2.0 * a);
	m->x[0] = t[0];
	m->x[1] = t[1];
	if (id != -1)
		if (!(if_cut(m, o, id)))
			return (0); 
	if (t[0] > t[1])
		t[0] = t[1];
	if ((t[0] > 0.01f) && (t[0] < m->t))
	{
		m->t = t[0];
		return (1);
	}
	return (0);
}

int				intersect_sphere(t_math *m, t_obj *s, t_ray *r)
{
	t_vector	v;
	double		ab[2];
	double		c;

	v = vector_sub(r->start, s->pos);
	ab[0] = vector_dot(r->dir, r->dir);
	ab[1] = 2.0 * vector_dot(r->dir, v);
	c = vector_dot(v, v) - s->radius;
	if (discriminant(ab[0], ab[1], c, m, s, -1))
		return (1);
	return (0);
}

int				intersect_cyl(t_math *m, t_obj *cyl, t_ray *r)
{
	t_vector	v;
	double		abc[3];
	t_vector	test;

	cyl->dir = unit_vector(&cyl->dir);
	v = vector_sub(r->start, cyl->pos);
	abc[0] = vector_dot(r->dir, r->dir) - pow(vector_dot(r->dir, cyl->dir), 2);
	abc[1] = 2.0 * (vector_dot(r->dir, v) - vector_dot(r->dir, cyl->dir) * vector_dot(v, cyl->dir));
	abc[2] = vector_dot(v, v) - pow(vector_dot(v, cyl->dir), 2) - pow(cyl->radius, 2);
	if (discriminant(abc[0], abc[1], abc[2], m, cyl, 0))
		return (1);
	return (0);
}

int				intersect_cone(t_math *m, t_obj *cone, t_ray *r)
{
	t_vector	v;
	double		abc[3];
	double		k;
	double		a;
	double 		dot_dir[2];

	k = tan(cone->radius);
	a = (1 + k * k);
	v = vector_sub(r->start, cone->pos);
	cone->dir = unit_vector(&cone->dir);
	dot_dir[0] = vector_dot(r->dir, cone->dir);
	dot_dir[1] = vector_dot(v, cone->dir);
	abc[0] = vector_dot(r->dir, r->dir)  - pow((dot_dir[0]), 2) * a;
	abc[1] = 2.0 * (vector_dot(r->dir, v) - dot_dir[0] * dot_dir[1] * a);
	abc[2] = vector_dot(v, v) - pow(dot_dir[1], 2) * a;
	if (discriminant(abc[0], abc[1], abc[2], m, cone, 1))
		return (1);
	return (0);
}

int				intersect_plane(t_math *m, t_obj *p, t_ray *r)
{
	float a;
	float b;
	float res;

	a = vector_dot(p->pos, r->dir);
	if (!a)
		return (0);
	b = -(vector_dot(p->pos, r->start) + p->radius);
	res = b / a;
	if (res > 0.0001f)
	{
		if (res < m->t)
		{
			m->t = res;
			return (1);
		}
	}
	return (0);
}
