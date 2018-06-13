/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:02:37 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/17 17:02:38 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

float				vector_dot(t_vector v1, t_vector v2);
t_vector			vector_scale(float k, t_vector v1);
t_vector			vector_sub(t_vector v1, t_vector v2);
t_vector			vector_add(t_vector v1, t_vector v2);
t_vector			unit_vector(t_vector *v);
t_vector			rotate_vec_x(t_vector *v, t_vector *rot);
t_vector			rotate_vec_y(t_vector *v, t_vector *rot);
t_vector			rotate_vec_z(t_vector *v, t_vector *rot);

#endif
