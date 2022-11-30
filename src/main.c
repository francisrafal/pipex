/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:19 by frafal            #+#    #+#             */
/*   Updated: 2022/11/30 17:47:41 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int pipefd[])
{
	char	buf;

	close(pipefd[1]);
	ft_putstr_fd("I received this from my parent:\n", STDOUT_FILENO);
	while (read(pipefd[0], &buf, 1) > 0)
		ft_putchar_fd(buf, STDOUT_FILENO);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

void	parent_process(int pipefd[])
{
	close(pipefd[0]);
	ft_putstr_fd("Let's write a secret\n", STDOUT_FILENO);
	ft_putstr_fd("I am your father!\n", pipefd[1]);
	close(pipefd[1]);
	//wait(NULL);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	//int	fd;
	pid_t	pid;
	int	pipefd[2];
	(void)argv;

	if (argc != 5)
	{
		ft_putstr_fd("usage: ./pipex <file1> \"cmd1\" \"cmd2\" <file2>\n", 2);
		exit (EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process(pipefd);
	else
		parent_process(pipefd);
	/*
	ft_printf("0: %d, 1: %d\n", pipefd[0], pipefd[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	*/
	return (0);
}
