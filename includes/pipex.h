/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:33:37 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/27 11:33:41 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/wait.h>
# include <libft.h>
# include <get_next_line.h>

typedef struct s_command
{
	char	*name;
	char	**args;
	char	*path;
	int		n_args;
}	t_command;

// Parsing of commands and paths

char		**get_paths(char **env);
char		*get_path(char **paths, char *command);
t_command	*parse_commands(char *argv[], int argc, char *env[]);

// Command utils

void		display_commands(t_command *commands);
int			n_commands(t_command *commands);

#endif
