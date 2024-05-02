/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trial.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:36:54 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/02 09:36:54 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		i;
	int		fd_in;
	int		status;

	if (argc < 5)
		exit(2);
	pipex = initialise_pipex(argv, env, argc);
	fd_in = -1;
	i = 2;
	while (i < argc - 1)
	{
		if (i == 2 && i == argc - 2)
			piping(&pipex, pipex.infile, pipex.outfile, fd_in);
		else if (i == 2)
			fd_in = piping(&pipex, pipex.infile, NULL, fd_in);
		else if (i == argc - 2)
			piping(&pipex, NULL, pipex.outfile, fd_in);
		else
			fd_in = piping(&pipex, NULL, NULL, fd_in);
		i++;
		pipex.current++;
	}
	status = wait_for_children(pipex.cpids);
	exit(status);
}
