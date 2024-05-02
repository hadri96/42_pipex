/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:38:35 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/02 09:38:35 by hmorand          ###   ########.ch       */
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

typedef struct s_pipex
{
	t_command	*commands;
	pid_t		*cpids;
	char		**env;
	char		*infile;
	char		*outfile;
	int			current;
	int			status;
}	t_pipex;

// Parsing of commands and paths

char		**get_paths(char **env);
char		*get_path(char **paths, char *command);
t_command	*parse_commands(char *argv[], int argc, char *env[]);

// Command utils

void		display_commands(t_command *commands);
int			n_commands(t_command *commands);

// Redirection

int			redirect_output(char *outfile);
int			redirect_input(char *infile);

// Execution

void		add_pid(pid_t pid, pid_t *cpids);
int			wait_for_children(pid_t *cpids);
void		execute(t_pipex *pipex, int fds[2], int fd_in);
int			piping(t_pipex *pipex, char *infile, char *outfile, int fd_in);
t_pipex		initialise_pipex(char **argv, char **env, int argc);

#endif
