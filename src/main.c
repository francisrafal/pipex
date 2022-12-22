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

void	child1_process(t_data data, char **argv, char **envp)
{
	close(data.pipefd[0]);
	dup2(data.file1, STDIN_FILENO);
	dup2(data.pipefd[1], STDOUT_FILENO);
	data.cmd_args = ft_split(argv[2], ' ');
	ft_printf((data.cmd_args)[0]);
	execve("/usr/bin/ls", data.cmd_args, envp);
	//ft_putstr_fd("Hello1\n", STDOUT_FILENO);
}

void	child2_process(t_data data, char **argv, char **envp)
{
	//char	buf[8];

	close(data.pipefd[1]);
	dup2(data.file2, STDOUT_FILENO);
	dup2(data.pipefd[0], STDIN_FILENO);
	data.cmd_args = ft_split(argv[3], ' ');
	ft_printf((data.cmd_args)[0]);
	execve("/usr/bin/wc", data.cmd_args, envp);
	//read(STDIN_FILENO, buf, 8);
	//ft_putstr_fd(buf, STDOUT_FILENO);
}

void	parent_process(t_data data)
{
	waitpid(data.pid1, &(data.wstatus), 0);
	waitpid(data.pid2, &(data.wstatus), 0);

	close(data.pipefd[0]);
	close(data.pipefd[1]);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
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
		child1_process(data, argv, envp);
	else
	{
		data.pid2 = fork();
		if (data.pid2 == -1)
			perror_exit("fork");
		if (data.pid2 == 0)
			child2_process(data, argv, envp);
		parent_process(data);
	}
	return (0);
}
