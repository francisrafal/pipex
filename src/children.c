/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:29:47 by frafal            #+#    #+#             */
/*   Updated: 2023/01/12 17:31:43 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process(t_data data, char **argv, char **envp)
{
	data.file1 = open(argv[1], O_RDONLY);
	if (data.file1 == -1)
		perror_exit("open file1");
	close(data.pipefd[0]);
	dup2(data.file1, STDIN_FILENO);
	dup2(data.pipefd[1], STDOUT_FILENO);
	data.cmd_args = ft_split(argv[2], ' ');
	remove_quotes(&data);
	data.cmd_path = get_cmd_path(data);
	execve(data.cmd_path, data.cmd_args, envp);
	perror_exit("execve");
}

void	child2_process(t_data data, char **argv, char **envp)
{
	data.file2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (data.file2 == -1)
		perror_exit("open file2");
	close(data.pipefd[1]);
	dup2(data.file2, STDOUT_FILENO);
	dup2(data.pipefd[0], STDIN_FILENO);
	data.cmd_args = ft_split(argv[3], ' ');
	data.cmd_path = get_cmd_path(data);
	execve(data.cmd_path, data.cmd_args, envp);
	perror_exit("execve");
}
