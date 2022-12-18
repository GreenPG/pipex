/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:27:03 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/18 13:20:32 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	if (input->cmd1)
		free(input->cmd1);
	if (input->cmd2)
		free(input->cmd2);
	if (input->args1)
		free_tab(input->args1);
	if (input->args1)
		free_tab(input->args2);
	free(input);
}

