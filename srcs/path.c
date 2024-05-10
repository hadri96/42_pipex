/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:24:15 by hmorand           #+#    #+#             */
/*   Updated: 2024/05/09 14:24:15 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
