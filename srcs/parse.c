/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:52:34 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/08 17:20:42 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_paths(char **env)
{
	char	**paths;

	while (ft_strncmp("PATH=", *env, 5))
		env++;
	paths = ft_split(ft_strchr(*env, '/'), ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_path(char **paths, char *command)
{
	char	*path;
	char	*subcommand;

	if (access(command, F_OK) == 0)
		return (command);
	subcommand = ft_strjoin("/", command);
	while (*paths)
	{
		path = ft_strjoin(*paths, subcommand);
		if (access(path, F_OK) == 0)
			break ;
		paths++;
	}
	if (access(path, F_OK) == 0)
		return (path);
	return (NULL);
}

char	*parse_arg(char *args)
{
	int		i;
	char	*arg;

	i = 1;
	if (args[0] == '"' || args[0] == '\'')
	{
		while (args[i] != args[0] || args[i - 1] == '\\')
			i++;
		arg = galloc(sizeof(char) * i - 1);
		if (!arg)
			return (NULL);
		ft_strlcpy(arg, args + 1, (size_t)(i));
	}
	else
		arg = ft_split(args, ' ')[0];
	return (arg);
}

char	*append_arg(t_command *command, char *args)
{
	char	*arg;
	char	**new_args;
	int		i;

	if (args[0] == '"' || args[0] == '\'')
	{
		arg = parse_arg(args);
		args += ft_strlen(arg) + 2;
	}
	else
	{
		arg = ft_split(args, ' ')[0];
		args += ft_strlen(arg);
	}
	new_args = galloc(sizeof(char *) * ++command->n_args + 1);
	if (!new_args)
		return (args);
	i = -1;
	while (command->args && command->args[++i])
		new_args[i] = ft_strdup(command->args[i]);
	new_args[i++] = arg;
	new_args[i] = NULL;
	free_strarr(command->args);
	command->args = new_args;
	return (args);
}

t_command	parse_command(char *command)
{
	t_command	comm;

	command = ft_strtrim(command, " ");
	comm.name = ft_split(command, ' ')[0];
	command = ft_strchr(command, ' ');
	comm.n_args = 0;
	comm.args = galloc(1);
	if (!comm.args)
	{
		comm.args = NULL;
		return (comm);
	}
	comm.args[0] = NULL;
	if (!command)
		return (comm);
	while (command[0] == ' ')
		command++;
	while (command[0])
	{
		command = append_arg(&comm, command);
		while (*command == ' ')
			command++;
	}
	return (comm);
}

t_command	*parse_commands(char *argv[], int argc, char *env[])
{
	int			i;
	t_command	*commands;
	char		**paths;

	paths = get_paths(env);
	commands = galloc(sizeof(t_command) * (argc - 3 + 1));
	if (!commands)
		return (NULL);
	i = 1;
	while (++i < argc - 1)
	{
		commands[i - 2] = parse_command(argv[i]);
		commands[i - 2].args = arr_insert(commands[i - 2].args,
				0, commands[i - 2].name);
		commands[i - 2].path = get_path(paths, commands[i - 2].name);
	}
	free_strarr(paths);
	commands[i - 2] = (t_command){0, 0, 0, 0};
	return (commands);
}

/* int	main(int argc, char *argv[], char **env)
{
	char		**paths;
	t_command	*commands;
	int			i;

	paths = get_paths(env);
	ft_printf("\n\nPaths:\n");
	for (int i = 0; paths[i]; i++)
		ft_printf("%s\n", paths[i]);
	ft_printf("\n\nArgv:\n");
	for (int i = 0; i < argc; i++)
		ft_printf("%s\n", argv[i]);
	commands = parse_commands(argv, argc, env);
	for (int j = 0; commands[j].name != 0; j++)
	{
		ft_printf("Path for command: %s\n", commands[j].path);
		ft_printf("Command: %s\n", commands[j].name);
		i = 0;
		while (i < commands[j].n_args)
			printf("\t- %s\n", commands[j].args[++i]);
	}
	cleargarbage();
} */
