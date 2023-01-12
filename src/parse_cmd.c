/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frafal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:38:08 by frafal            #+#    #+#             */
/*   Updated: 2023/01/12 17:39:04 by frafal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	append_str(&paths, "/");
	return (paths);
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
	return (data.cmd_args[0]);
}

void	remove_quotes(t_data *data)
{
	int		i;
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
