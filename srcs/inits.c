/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:57:24 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/16 13:57:26 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	obj_init(t_env *e)
{
	int i;

	i = -1;
	while (++i < e->obj_count)
	{
		e->objects[i].inter = 0;
		e->objects[i].material.spec = 0;
		e->objects[i].radius = 0;
		e->objects[i].pos.x = 0;
		e->objects[i].pos.y = 0;
		e->objects[i].pos.z = 0;
		e->objects[i].material.diffuse.r = 1;
		e->objects[i].material.diffuse.g = 0;
		e->objects[i].material.diffuse.b = 0;
		e->objects[i].dir.y = 0;
		e->objects[i].dir.x = 0;
		e->objects[i].dir.z = 0;
	}
	i = -1;
	while (++i < e->lgt_count && i < 10)
	{
		e->lights[i].pos.x = 100;
		e->lights[i].pos.y = 100;
		e->lights[i].pos.z = 100;
	}
}

void	init(t_env *env)
{
	env->img = (t_img *)malloc(sizeof(t_img));
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "RTV1");
	env->img->self = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->img->pxl = mlx_get_data_addr(env->img->self, &env->img->bpp,
					&env->img->bpl, &env->img->endian);
	thread(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img->self, 0, 0);
	mlx_hook(env->win, 17, 1L << 17, end, env);
	mlx_hook(env->win, 2, 5, keyboard, (void *)env);
	mlx_loop(env->mlx);
}

void	default_init(t_env *e)
{
	e->real_obj_cnt = 0;
	e->cur = -1;
	e->cam.fov = 60;
	e->cam.pos.x = 0;
	e->cam.pos.y = 0;
	e->cam.pos.z = 0;
	e->cam.rot_deg.x = 0;
	e->cam.rot_deg.y = 0;
	e->cam.rot_deg.z = 0;
}

void	check_cam_rot(t_ray *r, t_vector *dir, t_env *e)
{
	if (e->cam.rot_deg.x != 0)
		r->dir = rotate_vec_x(dir, &e->cam.rot_deg);
	if (e->cam.rot_deg.y != 0)
		r->dir = rotate_vec_y(dir, &e->cam.rot_deg);
	if (e->cam.rot_deg.z != 0)
		r->dir = rotate_vec_z(dir, &e->cam.rot_deg);
}

void	init_ray(t_ray *r, int x, int y, t_env *e)
{
	r->dir.x = (double)x / WIDTH;
	r->dir.y = (double)y / HEIGHT;
	r->dir.x = (2 * r->dir.x) - 1;
	r->dir.y = 1 - (2 * r->dir.y);
	r->dir.x *= tan(e->cam.fov);
	r->dir.y *= tan(e->cam.fov);
	r->dir.z = 1;
	check_cam_rot(r, &r->dir, e);
	r->start.x = e->cam.pos.x;
	r->start.y = e->cam.pos.y;
	r->start.z = e->cam.pos.z;
}
