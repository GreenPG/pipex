/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:37:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/11 13:10:09 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <stdlib.h>

void	open_error(t_input *input, int cmd_nb)
{
	if (errno == 2 || errno == 9)
		no_file_function(input, cmd_nb);
	if (errno == 13)
		no_permission_function(input, cmd_nb);
}

void	error_function(t_input *input, char *message)
{
	free_struct(input);
	perror(message);
	exit(EXIT_FAILURE);
}

void	no_file_function(t_input *input, int cmd_nb)
{
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	if (cmd_nb == 1)
		ft_putstr_fd(input->file1, 2);
	else
		ft_putstr_fd(input->file2, 2);
	ft_putstr_fd("\n", 2);
	free_struct(input);
	exit(EXIT_FAILURE);
}

void	no_permission_function(t_input *input, int cmd_nb)
{
	ft_putstr_fd ("pipex: permission denied: ", 2);
	if (cmd_nb == 1)
		ft_putstr_fd(input->file1, 2);
	else
		ft_putstr_fd(input->file2, 2);
	write(2, "\n", 1);
	free_struct(input);
	exit(EXIT_FAILURE);
}

void	command_error(t_input *input, int cmd_nb)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(input->cmd[cmd_nb], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_struct(input);
	exit(127);
}
