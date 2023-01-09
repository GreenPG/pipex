/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:24:27 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/09 16:25:34 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_error(t_input *input)
{
	if (errno == 2)
		no_file_function(input);
	if (errno == 13)
		no_permission_function(input);
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
	ft_putstr_fd ("pipex: ", 2);
	ft_putstr_fd(input->file1, 2);
	ft_putstr_fd (": permission denied\n", 2);
	free_struct(input);
	exit(EXIT_FAILURE);
}

void	command_error(t_input *input, int cmd_nb)
{
	ft_putstr_fd ("pipex: ", 2);
	if (cmd_nb == 1)
		ft_putstr_fd(input->args1[0], 2);
	else
		ft_putstr_fd(input->args2[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_struct(input);
	exit(127);
}
