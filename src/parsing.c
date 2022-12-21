/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:04:26 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/21 17:16:48 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>

t_input	*parsing(char **av, char *const *envp)
{
	t_input	*input;

	if (strtab_len(av) % 2 != 0)
	{
		ft_printf("Incorrect numbers of arguments");
		return (NULL);
	}
	input = init_struct();
	input->file1 = ft_strdup(av[0]);
	input->file2 = ft_strdup(av[3]);
	input->cmd1 = get_cmds(av[2], envp);
	input->cmd2 = get_cmds(av[3], envp);
	input->args1 = ft_split(av[2], ' ');
	input->args2 = ft_split(av[3], ' ');
	if (!input->file1 || !input->file2 || !input->cmd1 || !input->cmd2
		|| !input->args1 || !input->args2)
	{
		free_struct(input);
		return (NULL);
	}
	return (input);
}

char	*get_cmds(char *av, char *const *envp)
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

char	**get_paths(char *const *envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}
