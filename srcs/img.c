/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:26:23 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/09 15:26:25 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_put_pxl(t_img *re, int x, int y, t_color *c)
{
	int		i;

	i = (x * 4) + (y * re->bpl);
	re->pxl[i] = (double)(MIN(c->b * 255, 255));
	re->pxl[++i] = (double)MIN(c->g * 255, 255);
	re->pxl[++i] = (double)MIN(c->r * 255, 255);
	re->pxl[++i] = c->op;
}

void		set_color(t_color *c)
{
	c->r = 0;
	c->g = 0;
	c->b = 0;
	c->level = 0;
	c->coef = 1;
	c->op = 100;
}

float		get_float(char *str)
{
	float	i;
	char	*s2;

	s2 = ft_strchr(str, '=');
	i = 0.0;
	if (s2)
		i = strtof(s2 + 2, NULL);
	return (i);
}
