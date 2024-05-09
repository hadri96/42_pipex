/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:00:21 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/08 14:01:11 by hmorand          ###   ########.ch       */
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
		ft_printf(STDOUT_FILENO, "Command %d:\n", i);
		ft_printf(STDOUT_FILENO, "Name: %s\n", commands[i].name);
		ft_printf(STDOUT_FILENO, "Arguments:\n");
		j = 1;
		while (commands[i].args[j] != NULL)
		{
			ft_printf(STDOUT_FILENO, "\t%s\n", commands[i].args[j]);
			j++;
		}
		ft_printf(STDOUT_FILENO, "Path: %s\n", commands[i].path);
		ft_printf(STDOUT_FILENO,
			"Number of arguments: %d\n", commands[i].n_args);
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
