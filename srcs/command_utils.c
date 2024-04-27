/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:55:57 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/27 10:56:59 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_commands(t_command *commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i].name != NULL)
	{
		ft_printf("Command %d:\n", i);
		ft_printf("Name: %s\n", commands[i].name);
		ft_printf("Arguments:\n");
		j = 1;
		while (commands[i].args[j] != NULL)
		{
			ft_printf("\t%s\n", commands[i].args[j]);
			j++;
		}
		ft_printf("Path: %s\n", commands[i].path);
		ft_printf("Number of arguments: %d\n", commands[i].n_args);
		i++;
	}
}

int	n_commands(t_command *commands)
{
	int	i;

	i = 0;
	while (commands[i++].name != NULL)
		;
	return (i);
}
