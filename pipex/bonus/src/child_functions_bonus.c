/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:32:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/11 15:43:46 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	first_cmd(t_input *input, int pipesfd[2][2], char *const *envp)
{
	int	infile;
	int	err;

	close(pipesfd[1][0]);
	if (input->file1)
	{
		infile = open(input->file1, O_RDONLY);
		if (infile == -1)
		{
			close(pipesfd[1][1]);
			close(pipesfd[0][1]);
			close(pipesfd[0][0]);
			open_error(input, 1);
		}
		dup2(infile, 0);
		close(infile);
	}
	else
	{
		dup2(pipesfd[0][0], 0);
		close(pipesfd[0][0]);
	}
	dup2(pipesfd[1][1], 1);
	close(pipesfd[1][1]);
	err = execve(input->cmd[0], input->args[0], envp);
	if (err == -1)
	{
		close(0);
		close(1);
		if (errno == 2 || errno == 13)
			command_error(input, 0);
		free_struct(input);
		exit(EXIT_FAILURE);
	}
}

void	last_cmd(t_input *input, int *pipefd, char *const *envp, int cmd_nb)
{
	int	outfile;
	int	err;

	close(pipefd[1]);
	outfile = open(input->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		close(pipefd[0]);
		open_error(input, 2);
	}
	dup2(outfile, 1);
	close(outfile);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	err = execve(input->cmd[cmd_nb], input->args[cmd_nb], envp);
	if (err == -1)
	{
		close(0);
		close(1);
		if (errno == 2 || errno == 13)
			command_error(input, cmd_nb);
		free_struct(input);
		exit(EXIT_FAILURE);
	}
}

void	child_cmd(t_input *input, int pipesfd[2][2], char *const *envp,
		int cmd_nb)
{
	int	err;

	close(pipesfd[0][1]);
	close(pipesfd[1][0]);
	dup2(pipesfd[0][0], 0);
	close(pipesfd[0][0]);
	dup2(pipesfd[1][1], 1);
	close(pipesfd[1][1]);
	err = execve(input->cmd[cmd_nb], input->args[cmd_nb], envp);
	if (err == -1)
	{
		close(0);
		close(1);
		if (errno == 2 || errno == 13)
			command_error(input, cmd_nb);
		free_struct(input);
		exit(EXIT_FAILURE);
	}
}
