/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:04:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/12 15:40:22 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	***parse_args(t_input *input, char **av)
{
	size_t	i;
	char	***args;

	args = malloc(sizeof(char **) * strtab_len(av) - 1);
	if (!args)
	{
		free_struct(input);
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (i < strtab_len(av) - 1)
	{
		args[i - 1] = ft_split(av[i], ' ');
		i++;
	}
	args[i - 1] = NULL;
	return (args);
}

static char	**parse_cmd(t_input *input, char **av, char *const *envp)
{
	char	**cmd;
	size_t	i;
	int		cmd_nb;

	cmd_nb = strtab_len(av) - 2;
	cmd = ft_calloc(strtab_len(av) - 1, sizeof(char *));
	if (!cmd)
	{
		free_struct(input);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < strtab_len(av) - 2)
	{
		if (!input->args[i][0])
			cmd[i] = ft_strdup("NULL");
		else if (input->args[i][0][0] == '/')
			cmd[i] = ft_strdup(input->args[i][0]);
		else
			cmd[i] = get_cmds(input->args[i][0], envp);
		if (!cmd[i])
			return (NULL);
		i++;
	}
	return (cmd);
}

char	**get_splitted_envp(char *const *envp)
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

t_input	*parsing(char **av, char *const *envp)
{
	t_input	*input;

	input = init_struct();
	if (ft_strncmp(av[0], "here_doc", ft_strlen(av[0])) == 0)
	{
		input->file1 = NULL;
		av += 1;
	}
	else
		input->file1 = ft_strdup(av[0]);
	input->file2 = ft_strdup(av[strtab_len(av) - 1]);
	input->cmd_nbs = strtab_len(av) - 2;
	input->args = parse_args(input, av);
	input->cmd = parse_cmd(input, av, envp);
	return (input);
}
