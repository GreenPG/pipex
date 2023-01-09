/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:19:38 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/09 16:25:33 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

size_t	strtab_len(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
		i++;
	return (i);
}

void	infile_error(t_input *input, int pipefd[2])
{
	open_error(input);
	free_struct(input);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(EXIT_FAILURE);
}
