/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:30:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/09 15:54:09 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

t_input	*init_struct(void)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(*input));
	if (!input)
		return (0);
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
	cmd = ft_strdup(av);
	return (cmd);
}

char	**get_paths(char *const *envp)
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
