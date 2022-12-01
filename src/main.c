/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:19 by frafal            #+#    #+#             */
/*   Updated: 2022/12/01 14:03:11 by frafal           ###   ########.fr       */
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

void	perror_exit(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		pipefd[2];

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
	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	data.pid1 = fork();
	if (data.pid1 == -1)
		perror_exit("fork");
	if (data.pid1 == 0)
		child_process(pipefd);
	else
		parent_process(pipefd);
	return (0);
}
