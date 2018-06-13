/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 20:43:23 by atilegen          #+#    #+#             */
/*   Updated: 2018/06/07 20:43:25 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	rotate_vec_y(t_vector *v, t_vector *rot)
{
	t_vector	res;
	double		deg;

	deg = rot->y * PIOVER180;
	res.x = v->x * cos(deg) + sin(deg) * v->z;
	res.y = v->y;
	res.z = -v->x * sin(deg) + v->z * cos(deg);
	return (res);
}

t_vector	rotate_vec_z(t_vector *v, t_vector *rot)
{
	t_vector	res;
	double		deg;

	deg = rot->z * PIOVER180;
	res.x = v->x * cos(deg) + sin(deg) * v->y;
	res.y = -v->x * sin(deg) + cos(deg) * v->y;
	res.z = v->z;
	return (res);
}

t_vector	rotate_vec_x(t_vector *v, t_vector *rot)
{
	t_vector	res;
	double		deg;

	deg = rot->x * PIOVER180;
	res.x = v->x;
	res.y = v->y * cos(deg) + v->z * sin(deg);
	res.z = -v->y * sin(deg) + v->z * cos(deg);
	return (res);
}
