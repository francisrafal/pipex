/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:50:19 by frafal            #+#    #+#             */
/*   Updated: 2023/01/12 16:23:07 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	print_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		ft_printf("%s\n", str_arr[i]);
		i++;
	}
}

void	perror_exit(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

char	*get_cmd_path(t_data data)
{
	char	*cmd_path;
	int		i;

	if (ft_strncmp(data.cmd_args[0], "./", 2) == 0)
		return (data.cmd_args[0]);
	cmd_path = NULL;
	i = 0;
	while ((data.paths)[i] != NULL)
	{
		cmd_path = ft_strjoin(data.paths[i], data.cmd_args[0]);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	perror_exit("access");
	return (NULL);
}

void	remove_quotes(t_data *data)
{
	int	i;

	char	*tmp;
	char	*trim;

	tmp = NULL;
	i = 0;
	while (data->cmd_args[i] != NULL)
	{
		tmp = data->cmd_args[i];
		trim = ft_strtrim(data->cmd_args[i], "\"'");
		data->cmd_args[i] = trim;
		free(tmp);
		i++;
	}
}

void	child1_process(t_data data, char **argv, char **envp)
{
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
	close(data.pipefd[1]);
	dup2(data.file2, STDOUT_FILENO);
	dup2(data.pipefd[0], STDIN_FILENO);
	data.cmd_args = ft_split(argv[3], ' ');
	data.cmd_path = get_cmd_path(data);	
	execve(data.cmd_path, data.cmd_args, envp);
	perror_exit("execve");
}

void	parent_process(t_data data)
{
	close(data.pipefd[1]);
	close(data.pipefd[0]);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	free_str_arr(data.paths);
	//free_str_arr(data.cmd_args);
	exit(EXIT_SUCCESS);
}

void	append_str(char ***paths, char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while ((*paths)[i] != NULL)
	{
		tmp = (*paths)[i];
		(*paths)[i] = ft_strjoin(tmp, str);
		free(tmp);
		i++;
	}
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5)	== 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	append_str(&paths, "/");
	return (paths);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		ft_putstr_fd("usage: ./pipex <file1> \"cmd1\" \"cmd2\" <file2>\n", 2);
		exit (EXIT_FAILURE);
	}
	data.paths = get_paths(envp);
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
		else
			parent_process(data);
	}
	return (0);
}
