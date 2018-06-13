/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:26:18 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/23 17:26:20 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		check(char **s)
{
	if (ft_strstr(*s, "=") && ft_strstr(*s, ","))
		*s = ft_strtrim(ft_strchr(*s, '=') + 1);
	else
		error_end("Wrong input format");
}

void		fill_obj_pos(t_env *e, char *s)
{
	if (ft_strstr(s, "position") && e->i < e->obj_count)
	{
		if (e->i != e->real_obj_cnt)
			error_end("Wrong id");
		check(&s);
		e->objects[e->i].pos.x = ft_atoi(s);
		e->objects[e->i].pos.y = ft_atoi(ft_strchr(s, ',') + 1);
		e->objects[e->i].pos.z = ft_atoi(ft_strrchr(s, ',') + 1);
		e->real_obj_cnt++;
		free(s);
	}
	fill_obj(e, s);
}

void		fill_obj(t_env *e, char *s)
{
	if ((ft_strstr(s, "size") || ft_strstr(s, "radius") ||
		ft_strstr(s, "tan")) && e->i < e->obj_count)
		e->objects[e->i].radius = get_float(s);
	else if (ft_strstr(s, "spec"))
		e->objects[e->i].material.spec = get_float(s);
	else if (ft_strstr(s, "direction"))
	{
		check(&s);
		e->objects[e->i].dir.x = ft_atoi(s);
		e->objects[e->i].dir.y = ft_atoi(ft_strchr(s, ',') + 1);
		e->objects[e->i].dir.z = ft_atoi(ft_strrchr(s, ',') + 1);
		free(s);
	}
	fill_mat(e, s);
}

void		fill_lights(t_env *e, char *s)
{
	if (e->i < e->lgt_count)
	{
		if (ft_strstr(s, "position"))
		{
			check(&s);
			e->lights[e->i].pos.x = ft_atoi(s);
			e->lights[e->i].pos.y = ft_atoi(ft_strchr(s, ',') + 1);
			e->lights[e->i].pos.z = ft_atoi(ft_strrchr(s, ',') + 1);
			free(s);
		}
	}
}

void		fill_cam(t_env *e, char *s)
{
	if (ft_strstr(s, "position"))
	{
		check(&s);
		e->cam.pos.x = ft_atoi(s);
		e->cam.pos.y = ft_atoi(ft_strchr(s, ',') + 1);
		e->cam.pos.z = ft_atoi(ft_strrchr(s, ',') + 1);
		free(s);
	}
	else if (ft_strstr(s, "rotation"))
	{
		check(&s);
		e->cam.rot_deg.x = ft_atoi(s);
		e->cam.rot_deg.y = ft_atoi(ft_strchr(s, ',') + 1);
		e->cam.rot_deg.z = ft_atoi(ft_strrchr(s, ',') + 1);
		free(s);
	}
}
