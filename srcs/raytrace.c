/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 13:04:58 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/13 13:05:00 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	lambert(t_math *m, t_mtr *cur_m, t_env *e)
{
	float		lambert;
	int			i;
	int			in_shadow;

	in_shadow = 0;
	i = -1;
	while (++i < e->obj_count)
	{
		if (e->objects[i].inter(m, &e->objects[i], &m->l_ray))
		{
			in_shadow = 1;
			break ;
		}
	}
	if (!in_shadow)
	{
		lambert = vector_dot(m->l_ray.dir, m->norm) * m->color.coef;
		m->color.r += (1 - cur_m->diffuse.r) * pow(lambert, 30) * cur_m->spec;
		m->color.g += (1 - cur_m->diffuse.g) * pow(lambert, 30) * cur_m->spec;
		m->color.b += (1 - cur_m->diffuse.b) * pow(lambert, 30) * cur_m->spec;
		m->color.op *= (1 - pow(lambert, 2));
	}
}

void 	ray_start_and_dir(t_math *m)
{
	float reflect;
	t_vector tmp;

	m->r.start = m->new_start;
	// m->r.start = unit_vector(&m->r.start);
	reflect = 2.0f * vector_dot(m->r.dir, m->norm);
	tmp = vector_scale(reflect, m->norm);
	m->r.dir = vector_sub(m->r.dir, tmp);
	m->r.dir = unit_vector(&m->r.dir);
}

void	find_light_value(t_math *m, t_env *e, t_mtr *c_m)
{
	int			j;
	t_lgt		cur_l;
	t_vector	dist;

	j = -1;
	while (++j < e->lgt_count && j <= 10)
	{
		m->color.r = c_m->diffuse.r;
		m->color.g = c_m->diffuse.g;
		m->color.b = c_m->diffuse.b;
		cur_l = e->lights[j];
		dist = vector_sub(cur_l.pos, m->new_start);
		m->t = sqrtf(vector_dot(dist, dist));
		if (vector_dot(m->norm, dist) <= 0.0f || (m->t <= 0.0f && m->t > 1.0f))
			continue ;
		m->l_ray.start = m->new_start;
		m->l_ray.dir = dist;
		m->l_ray.dir = unit_vector(&m->l_ray.dir);
		lambert(m, c_m, e);
	}
}

void	*raytrace(void *data)
{
	t_math m;
	t_env *e;
	double tmp;

	e = data;
	tmp = e->y;
	e->x = 0;
	while (e->x < HEIGHT)
	{
		e->y = tmp;
		while (e->y < e->limit)
		{
			set_color(&m.color);
			init_ray(&m.r, e->x, e->y, e);
			find_inter(&m, e);
			ft_put_pxl(e->img, e->x, e->y, &m.color);
			e->y++;
		}
		e->x++;
	}
	pthread_exit(0);
}

void	thread(t_env *e)
{
	pthread_t	tid[200];
	t_env		env_arr[200];
	int i;

	i = 0;
	while (i < 4)
	{
		env_arr[i] = *e;
		env_arr[i].y = 200 * i;
		env_arr[i].limit = 200 * (i + 1);
		i++;
	}
	i = 0;
	while (++i <= 4)
		pthread_create(&tid[i - 1], NULL, raytrace, &env_arr[i - 1]);
	while (i--)
		pthread_join(tid[i], NULL);
}
