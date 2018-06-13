/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atilegen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 18:13:14 by atilegen          #+#    #+#             */
/*   Updated: 2018/05/06 18:13:16 by atilegen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		main(int ac, char **av)
{
	t_env	env;

	// env = (t_env*)malloc(sizeof(t_env));
	if (ac == 2)
	{
		env.fd = open(av[1], O_RDONLY);
		if (ft_parse(&env) == -1)
			error_end("Invalid scene");
		init(&env);
	}
	else
		ft_putendl("usage: ./RTv1 [-scene1]");
	return (0);
}
