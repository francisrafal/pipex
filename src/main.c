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
	int	fd;
	int	pipefd[2];

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
	ft_printf("0: %d, 1: %d\n", pipefd[0], pipefd[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (0);
}
