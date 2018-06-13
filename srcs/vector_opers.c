/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_opers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:38:11 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/10 16:38:15 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

float		vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vector_scale(float c, t_vector v)
{
	t_vector result;

	result.x = v.x * c;
	result.y = v.y * c;
	result.z = v.z * c;
	return (result);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	unit_vector(t_vector *v)
{
	float temp;

	temp = 1.0f / sqrtf(vector_dot(*v, *v));
	*v = vector_scale(temp, *v);
	return (*v);
}
