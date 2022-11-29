/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:19 by frafal            #+#    #+#             */
/*   Updated: 2022/11/28 16:52:21 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	//int	fd;
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
	/*
	ft_printf("0: %d, 1: %d\n", pipefd[0], pipefd[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	*/
	int arr[] = {1, 2, 3, 4, 5, 6};
	int id1 = fork();
	if (id1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	int id2;
	id2 = -1;
	if (id1 != 0)
	{
		id2 = fork();	
		if (id2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}
	int	start;
	int	end;
	if (id1 == 0)
	{
		start = 0;
		end = sizeof(arr) / sizeof(int) / 2;
	}
	if (id2 == 0)
	{
		start = sizeof(arr) / sizeof(int) / 2;
		end = sizeof(arr) / sizeof(int);
	}
	int	sum;
	sum = 0;
	if (id1 == 0 || id2 == 0)
	{
		int	i;
		i = start;
		while (i < end)
		{
			sum += arr[i];
			i++;
		}
		ft_printf("sum: %d\n", sum);
		close(pipefd[0]);
		write(pipefd[1], &sum, sizeof(sum));	
		close(pipefd[1]);
	}
	else
	{
		int sum_child;
		close(pipefd[1]);
		if (read(pipefd[0], &sum_child, sizeof(sum_child) == -1))
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		sum += sum_child;
		ft_printf("sum: %d\n", sum);
		wait(NULL);
		//waitpid(id1, NULL, 0);
	}
	return (0);
}
