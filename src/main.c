/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:19 by frafal            #+#    #+#             */
/*   Updated: 2023/01/12 17:40:49 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(t_data data, char **argv, char **envp)
{
	data.pid2 = fork();
	if (data.pid2 == -1)
		perror_exit("fork");
	if (data.pid2 == 0)
		child2_process(data, argv, envp);
	else
	{
		close(data.pipefd[1]);
		close(data.pipefd[0]);
		waitpid(data.pid1, NULL, 0);
		waitpid(data.pid2, NULL, 0);
		free_str_arr(data.paths);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	check_argc(argc);
	data.paths = get_paths(envp);
	if (pipe(data.pipefd) == -1)
		perror_exit("pipe");
	data.pid1 = fork();
	if (data.pid1 == -1)
		perror_exit("fork");
	if (data.pid1 == 0)
		child1_process(data, argv, envp);
	else
		parent_process(data, argv, envp);
	return (0);
}
