/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.json                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:57:24 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/27 12:50:20 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_output(char **argv, int argc)
{
	int	fd;

	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	**alloc_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = galloc (sizeof(int *) * n - 1);
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < n - 1)
	{
		pipes[i] = galloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	return (pipes);
}



int	**initialise(int **cpids, char **argv, int argc, int n)
{
	int	**pipes;
	int	i;

	redirect_output(argv, argc);
	*cpids = galloc(sizeof(pid_t) * n);
	if (!*cpids)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	pipes = alloc_pipes(n);
	i = 0;
	ft_printf("Hello");
	while (i < n - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (pipes);
}

void	close_pipes(int **pipes, int n)
{
	int	i;

	i = -1;
	while (++i < n - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	execute(t_command *commands, pid_t **cpids, int ***pipes, char **env)
{
	int	i;

	i = -1;
	while (commands[i].name != NULL)
	{
		(*cpids)[i] = fork();
		if ((*cpids)[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if ((*cpids)[i] == 0)
		{
			if (i > 0)
			{
				dup2((*pipes)[i - 1][0], STDIN_FILENO);
				close((*pipes)[i - 1][1]);
			}

			if (i < n_commands(commands) - 1)
			{
				dup2((*pipes)[i][1], STDOUT_FILENO);
				close((*pipes)[i][0]);
			}

			//close_pipes(*pipes, n_commands(commands));
			execve(commands[i].path, commands[i].args, env);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (i > 0)
			{
				close((*pipes)[i - 1][0]);
				close((*pipes)[i - 1][1]);
			}
			ft_printf("Parent closed pipes for child %d\n", i);
		}
	}
}

void	wait_for_children(int n, pid_t *cpids)
{
	int	i;
	int	status;

	i = -1;
	while (++i < n)
	{
		waitpid(cpids[i], &status, 0);
		if (WIFEXITED(status))
			ft_printf("Child %d exited with status %d\n",
				cpids[i], WEXITSTATUS(status));
	}
}


int	main(int argc, char *argv[], char *env[])
{
	t_command	*commands;
	pid_t		*cpids;
	int			**pipes;
	int			n;

	commands = parse_commands(argv, argc, env);
	n = n_commands(commands);
	//display_commands(commands);
	ft_printf("Outfile: %s\n", argv[argc - 1]);
	pipes = initialise(&cpids, argv, argc, n);
	ft_printf("Execute");
	execute(commands, &cpids, &pipes, env);
	close_pipes(pipes, n);
	wait_for_children(n, cpids);
	exit(1);
	return (0);
}
