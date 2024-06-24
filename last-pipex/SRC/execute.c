/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:29:49 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/03 07:38:36 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	with_path(char *av, char **path, char **env)
{
	char	**split;
	char	*command;
	int		i;

	i = -1;
	split = ft_split(av, ' ');
	while (path[++i])
	{
		command = ft_strjoin(path[i], split[0]);
		if (!access(command, X_OK))
			break ;
		free(command);
		command = NULL;
	}
	if (!command || execve(command, split, env) == -1)
	{
		write(2, "zsh: command not found: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(NULL, path);
		ft_free(command, split);
		exit(127);
	}
}

static void	without_path(char *av, char **env)
{
	char	**split;

	split = ft_split(av, ' ');
	if (!split || !split[0] || execve(split[0], split, env) == -1)
	{
		write(2, "zsh: command not found: ", 24);
		ft_putstr_fd(split[0], 2);
		write(2, "\n", 1);
		ft_free(NULL, split);
		exit(127);
	}
}

void	execute_child(int *pip, char **av, char **env)
{
	int		fd;
	char	**path;

	path = get_path(env);
	if (!path)
		exit (1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_free(NULL, path);
		perror("zsh");
		exit(1);
	}
	close(pip[0]);
	dup2(pip[1], 1);
	close(pip[1]);
	dup2(fd, 0);
	close(fd);
	if (!ft_strchr(av[2], '/'))
		with_path(av[2], path, env);
	else
	{
		ft_free(NULL, path);
		without_path(av[2], env);
	}
}

void	execute_parent(int *pip, char **av, char **env)
{
	int		fd;
	char	**path;

	path = get_path(env);
	if (!path)
		exit (1);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("zsh");
		ft_free(NULL, path);
		exit(1);
	}
	close(pip[1]);
	dup2(pip[0], 0);
	close(pip[0]);
	dup2(fd, 1);
	close(fd);
	if (!ft_strchr(av[3], '/'))
		with_path(av[3], path, env);
	else
	{
		ft_free(NULL, path);
		without_path(av[3], env);
	}
}
