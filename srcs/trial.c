/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trial.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:00 by hmorand           #+#    #+#             */
/*   Updated: 2024/04/29 14:49:15 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	add_pid(pid_t pid, pid_t *cpids)
{
	while (*cpids)
		cpids++;
	*cpids++ = pid;
	*cpids = 0;
}

int	execute(t_pipex *pipex, char *infile, char *outfile, int fd_in)
{
	int		fd_out;
	int		fds[2];
	pid_t	pid;

	if (!outfile)
		pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		if (infile)
			fd_in = redirect_input(infile);
		dup2(fd_in, STDIN_FILENO);
		if (outfile)
			fd_out = redirect_output(outfile);
		else
			dup2(fds[1], STDOUT_FILENO);
		close(fd_in);
		close(fds[0]);
		close(fds[1]);
		execve(pipex->commands[pipex->current].path,
			pipex->commands[pipex->current].args, pipex->env);
		perror("Execve");
		exit(EXIT_FAILURE);
	}
	add_pid(pid, pipex->cpids);
	if (!outfile)
	{
		close(fds[1]);
		return (fds[0]);
	}
	return (-1);

}

t_pipex	initialise_pipex(char **argv, char **env, int argc)
{
	t_pipex	pipex;

	pipex.commands = parse_commands(argv, argc, env);
	pipex.cpids = galloc(sizeof(pid_t) * (argc - 2));
	if (!pipex.cpids)
	{
		perror("malloc cpids");
		exit(EXIT_FAILURE);
	}
	pipex.env = env;
	pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	pipex.current = 0;
	return (pipex);
}


int	wait_for_children(pid_t *cpids)
{
	int	status;

	while (*cpids)
	{
		waitpid(*cpids, &status, 0);
		cpids++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

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
			execute(&pipex, pipex.infile, pipex.outfile, fd_in);
		else if (i == 2)
			fd_in = execute(&pipex, pipex.infile, NULL, fd_in);
		else if (i == argc - 2)
			execute(&pipex, NULL, pipex.outfile, fd_in);
		else
			fd_in = execute(&pipex, NULL, NULL, fd_in);
		i++;
		pipex.current++;
	}
	status = wait_for_children(pipex.cpids);
	exit(status);
}
