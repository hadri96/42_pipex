/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:42:10 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/08 17:42:10 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_output(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf(2, "pipex: permission denied: %s\n", outfile);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	redirect_input(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "pipex: %s: No such file or directory\n",
			infile);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
