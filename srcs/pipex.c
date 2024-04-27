/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:04:37 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/27 11:04:37 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_command	*commands;
	int			n;
	int			*pipefd;
	int			fd;

	commands = parse_commands(argv, argc, env);
	n = n_commands(commands);
	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);



}
