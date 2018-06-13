/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:33:07 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/09 19:33:08 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		end(void)
{
	exit(0);
	return (0);
}

int		error_end(char *str)
{
	ft_putendl(str);
	exit(0);
	return (0);
}

void	z_opers(int keycode, t_env *e)
{
	if (keycode == 116)
		e->cam.pos.z += 20;
	if (keycode == 121)
		e->cam.pos.z -= 20;
}

void	cam_rot(int keycode, t_env *e)
{
	if (keycode == 0)
		e->cam.rot_deg.y -= 1;
	if (keycode == 2)
		e->cam.rot_deg.y += 1;
	if (keycode == 13)
		e->cam.rot_deg.x += 1;
	if (keycode == 1)
		e->cam.rot_deg.x -= 1;
	if (keycode == 115)
		e->cam.rot_deg.z += 1;
	if (keycode == 119)
		e->cam.rot_deg.z -= 1;
}

int keyboard(int keycode, void *data)
{
	t_env	*e;

	e = data;
	if (keycode == 53)
		end();
	if (keycode == 123)
		e->cam.pos.x -= 5;
	if (keycode == 124)
		e->cam.pos.x += 5;
	if (keycode == 126)
		e->cam.pos.y += 5;
	if (keycode == 125)
		e->cam.pos.y -= 5;
	cam_rot(keycode, e);
	z_opers(keycode, e);
	mlx_clear_window(e->mlx, e->win);
	thread(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->self, 0, 0);
	return (0);
}
