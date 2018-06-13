/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 19:25:05 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/09 19:25:07 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <stdio.h>

void		fill_other_structure(t_env *e, char *s)
{
	int i;

	i = -1;
	if (e->cur == 0)
	{
		fill_obj_pos(e, s);
		find_shape(e, s);
	}
	else if (e->cur == 1)
		fill_lights(e, s);
	else if (e->cur == 2)
		fill_cam(e, s);
	else
		return ;
}

void		set_structure(t_env *e, char *s)
{
	if (ft_strchr(s, '#'))
		e->i = get_number(s);
	if (ft_strchr(s, '{'))
	{
		if (ft_strstr(s, "objects"))
			e->cur = 0;
		else if (ft_strstr(s, "lights"))
			e->cur = 1;
		else if (ft_strstr(s, "amera"))
			e->cur = 2;
		else
			error_end("Invalid scene");
	}
	fill_other_structure(e, s);
}

int			get_number(char *str)
{
	int		i;
	char	*s2;
	char	*s1;

	s2 = ft_strchr(str, '=');
	i = 0;
	if (s2)
	{
		s1 = ft_strtrim(s2 + 1);
		if (s1)
		{
			i = ft_atoi(s1);
			free(s1);
		}
		else
			error_end("Wrong input");
	}
	return (i);
}

void		init_structure(t_env *e)
{
	t_obj		*obj;
	t_lgt		*lights;
	int			i;

	i = -1;
	lights = (t_lgt *)malloc(sizeof(t_lgt) * (e->lgt_count + 1));
	obj = (t_obj *)malloc(sizeof(t_obj) * (e->obj_count + 1));
	if (e->lgt_count >= 10)
		error_end("Too much lights");
	if (lights && obj && e->obj_count > 0 && e->lgt_count > 0)
	{
		e->lights = lights;
		e->objects = obj;
	}
	else
		error_end("Couldn't allocate memory for lights and/or objects");
	obj_init(e);
}

int			ft_parse(t_env *e)
{
	char		*line;
	int			i;

	i = -1;
	if (get_next_line(e->fd, &line) <= 0)
		return (-1);
	fill_structure(e, line);
	free(line);
	while (++i < 3 && get_next_line(e->fd, &line) > 0)
	{
		fill_structure(e, line);
		free(line);
	}
	init_structure(e);
	default_init(e);
	while ((get_next_line(e->fd, &line)) > 0)
	{
		set_structure(e, line);
		free(line);
	}
	i = -1;
	close(e->fd);
	if (e->real_obj_cnt != e->obj_count)
		error_end("Wrong number of lights or objects");
	while (++i < e->real_obj_cnt)
		(e->objects[i].inter == 0) ? error_end("Parse error") : 0;
	return (0);
}
