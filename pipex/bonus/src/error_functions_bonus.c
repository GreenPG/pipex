/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:37:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/12 16:20:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
	ft_putstr_fd("pipex: ", 2);
	if (cmd_nb == 1)
		ft_putstr_fd(input->file1, 2);
	else
		ft_putstr_fd(input->file2, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_struct(input);
	exit(EXIT_FAILURE);
}

void	no_permission_function(t_input *input, int cmd_nb)
{
	ft_putstr_fd ("pipex: ", 2);
	if (cmd_nb == 1)
		ft_putstr_fd(input->file1, 2);
	else
		ft_putstr_fd(input->file2, 2);
	ft_putstr_fd(": Permssion denied\n", 2);
	free_struct(input);
	exit(EXIT_FAILURE);
}

void	command_error(t_input *input, int cmd_nb)
{
	ft_putstr_fd(input->cmd[cmd_nb], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_struct(input);
	exit(127);
}
