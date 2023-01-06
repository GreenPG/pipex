/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:27:03 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/06 13:10:53 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	free_tab(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
	{
		free(str_tab[i]);
		i++;
	}
	free(str_tab);
}

void	free_struct(t_input *input)
{
	if (input->file1)
		free(input->file1);
	if (input->file2)
		free(input->file2);
	if (input->cmd)
		free_tab(input->cmd);
	if (input->args)
		free_tab_tab(input->args);
	free(input);
}

void	free_tab_tab(char ***tab_tab)
{
	int	i;

	i = 0;
	while (tab_tab[i])
	{
		free_tab(tab_tab[i]);
		i++;
	}
	free(tab_tab);
}
