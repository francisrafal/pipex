/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:19 by frafal            #+#    #+#             */
/*   Updated: 2022/12/02 16:45:46 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

void	child1_process(t_data data)
{
	dup2(data.pipefd[1], 1);
	close(data.pipefd[0]);
	dup2(data.file1, 0);
	ft_putstr_fd("Hello1\n", STDOUT_FILENO);
	close(data.pipefd[0]);
	exit(EXIT_SUCCESS);
}

void	child2_process(t_data data)
{
	close(data.pipefd[1]);
	ft_putstr_fd("Hello2\n", STDOUT_FILENO);
	close(data.pipefd[0]);
	exit(EXIT_SUCCESS);
}

void	parent_process(t_data data)
{
	data.pid2 = fork();
	if (data.pid2 == -1)
		perror_exit("fork");
	if (data.pid2 == 0)
		child2_process(data);
	waitpid(data.pid1, &(data.wstatus), 0);	
	waitpid(data.pid2, &(data.wstatus), 0);	

	close(data.pipefd[0]);
	ft_putstr_fd("Let's write a secret\n", STDOUT_FILENO);
	close(data.pipefd[1]);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5)
	{
		ft_putstr_fd("usage: ./pipex <file1> \"cmd1\" \"cmd2\" <file2>\n", 2);
		exit (EXIT_FAILURE);
	}
	data.file1 = open(argv[1], O_RDONLY);	
	if (data.file1 == -1)
		perror_exit("open file1");
	data.file2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);	
	if (data.file2 == -1)
		perror_exit("open file2");
	if (pipe(data.pipefd) == -1)
		perror_exit("pipe");
	data.pid1 = fork();
	if (data.pid1 == -1)
		perror_exit("fork");
	if (data.pid1 == 0)
		child1_process(data);
	else
		parent_process(data);
	return (0);
}
