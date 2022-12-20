/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:04:26 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/20 15:57:16 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_input	*parsing(char **av)
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
	get_cmds(av, input);
	if (!input->file1 || !input->file2 || !input->cmd1 || !input->cmd2
		|| !input->args1 || !input->args2)
	{
		free_struct(input);
		return (NULL);
	}
	return (input);
}

void	get_cmds(char **av, t_input	*input)
{
	char	***splitted_input;
	char	*bin;

	bin = "/bin/";
	splitted_input = get_splitted_input(av);
	if (!splitted_input)
	{
		ft_printf("Error in ft_split");
		return ;
	}
	input->cmd1 = ft_strjoin(bin, splitted_input[0][0]);
	input->cmd2 = ft_strjoin(bin, splitted_input[1][0]);
	input->args1 = get_args(splitted_input[0]);
	input->args2 = get_args(splitted_input[1]);
	if (!input->cmd1 || !input->cmd2 || !input->args1 || !input->args2)
	{
		free_struct(input);
		return ;
	}
	free_tab_tab(splitted_input);
}

char	***get_splitted_input(char **av)
{
	char	***splitted_input;

	splitted_input = ft_calloc(3, sizeof(*splitted_input));
	splitted_input[0] = ft_split(av[1], ' ');
	if (!splitted_input[0])
	{
		free(splitted_input);
		ft_printf("Error in ft_split");
		return (NULL);
	}
	splitted_input[1] = ft_split(av[2], ' ');
	if (!splitted_input[1])
	{
		free_tab_tab(splitted_input);
		ft_printf("Error in ft_split");
		return (NULL);
	}
	return (splitted_input);
}

char	**get_args(char	**splitted_input)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (strtab_len(splitted_input) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (splitted_input[i])
	{
		args[i] = ft_strdup(splitted_input[i]);
		if (!args[i])
		{
			free_tab(args);
			return (NULL);
		}
		i++;
	}
	args[i] = 0;
	return (args);
}
