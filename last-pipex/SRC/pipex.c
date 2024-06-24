/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 04:02:27 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/06/03 06:08:49 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	pid;
	int	pip[2];
	int	status;

	if (ac == 5)
	{
		pipe(pip);
		pid = fork();
		if (!pid)
			execute_child(pip, av, env);
		else
		{
			pid = fork();
			if (pid == 0)
				execute_parent(pip, av, env);
			else
			{
				close(pip[0]);
				close(pip[1]);
				waitpid(pid, &status, 0);
				return (WEXITSTATUS(status));
			}
		}
	}
	return (1);
}
