/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:37:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/09 16:41:31 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	open_error(t_input *input, int pipefd[2])
{
	if (errno == 2)
		no_file_function(input);
	if (errno == 13)
		no_permission_function(input);
	free_struct(input);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(EXIT_FAILURE);
}

void	error_function(t_input *input, char *message)
{
	free_struct(input);
	perror(message);
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

void	command_error(t_input *input, int cmd_nb)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(input->args[cmd_nb][0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_struct(input);
	exit(127);
}
