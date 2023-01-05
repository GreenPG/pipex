/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:19:38 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/05 17:22:59 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

size_t	strtab_len(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
		i++;
	return (i);
}

void	error_function(t_input *input, char *message)
{
	free_struct(input);
	perror(message);
	exit(1);
}

void	no_file_function(t_input *input, int nb)
{
	write(2, "pipex: no such file or directory: ", 34);
	if (nb == 1)
		ft_putstr_fd(input->file1, 2);
	else
		ft_putstr_fd(input->file2, 2);
	write(2, "\n", 1);
	free_struct(input);
	exit(EXIT_FAILURE);
}
