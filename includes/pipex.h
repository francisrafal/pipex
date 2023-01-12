/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:42 by frafal            #+#    #+#             */
/*   Updated: 2023/01/12 17:37:36 by frafal           ###   ########.fr       */
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

void	free_str_arr(char **str_arr);
void	perror_exit(char *err);
char	*get_cmd_path(t_data data);
void	remove_quotes(t_data *data);
void	child1_process(t_data data, char **argv, char **envp);
void	child2_process(t_data data, char **argv, char **envp);
void	parent_process(t_data data, char **argv, char **envp);
void	append_str(char ***paths, char *str);
char	**get_paths(char **envp);
void	check_argc(int argc);

#endif
