/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:42 by frafal            #+#    #+#             */
/*   Updated: 2023/01/12 14:36:22 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_data
{
	int		file1;
	int		file2;
	int		pipefd[2];
	int		wstatus1;
	int		wstatus2;
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd_path;
	char	**cmd_args;
	char	**paths;
}	t_data;

#endif
