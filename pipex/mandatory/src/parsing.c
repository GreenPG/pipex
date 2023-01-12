/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:04:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/12 15:29:34 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	**get_splitted_envp(char *const *envp)
{
	int		i;
	char	**splitted_envp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	splitted_envp = ft_split(envp[i] + 5, ':');
	return (splitted_envp);
}

static char	**get_paths(char *const *envp)
{
	int		i;
	char	**paths;
	char	**splitted_envp;

	splitted_envp = get_splitted_envp(envp);
	if (!splitted_envp)
		return (NULL);
	paths = malloc((strtab_len(splitted_envp) + 1) * sizeof(char *));
	if (!paths)
	{
		free_tab(splitted_envp);
		return (NULL);
	}
	i = 0;
	while (splitted_envp[i])
	{
		paths[i] = ft_strjoin(splitted_envp[i], "/");
		i++;
	}
	paths[i] = 0;
	free_tab(splitted_envp);
	return (paths);
}

static char	*get_cmds(char *av, char *const *envp)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = get_paths(envp);
	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], av);
		if (access(cmd, X_OK) == 0)
		{
			free_tab(paths);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

t_input	*parsing(char **av, char *const *envp)
{
	t_input	*input;

	input = init_struct();
	input->file1 = ft_strdup(av[0]);
	input->file2 = ft_strdup(av[3]);
	input->args1 = ft_split(av[1], ' ');
	input->args2 = ft_split(av[2], ' ');
	if (!input->args1[0])
		input->cmd1 = ft_strdup("NULL");
	else if (input->args1[0][0] == '/')
		input->cmd1 = ft_strdup(input->args1[0]);
	else
		input->cmd1 = get_cmds(input->args1[0], envp);
	if (!input->args2[0])
		input->cmd2 = ft_strdup("NULL");
	else if (input->args2[0][0] == '/')
		input->cmd2 = ft_strdup(input->args2[0]);
	else
		input->cmd2 = get_cmds(input->args2[0], envp);
	return (input);
}
