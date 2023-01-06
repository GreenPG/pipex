/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:19:38 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/06 15:31:31 by gpasquet         ###   ########.fr       */
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

void	error_function(t_input *input, char *message)
{
	free_struct(input);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("No such file or directory\n", 2);
	exit(1);
}

void	no_file_function(t_input *input)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(input->file1, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_struct(input);
	exit(EXIT_FAILURE);
}

void	no_permission_function(t_input *input)
{
	ft_putstr_fd ("pipex: permission denied: ", 2);
	ft_putstr_fd(input->file1, 2);
	write(2, "\n", 1);
	free_struct(input);
	exit(EXIT_FAILURE);
}
