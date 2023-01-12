/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:32:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/12 15:36:48 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	open_infile(t_input *input, int *pipefd)
{
	int	infile;

	infile = open(input->file1, O_RDONLY);
	if (infile == -1)
	{
		close(pipefd[1]);
		open_error(input, 1);
	}
	dup2(infile, 0);
	close(infile);
}

static void	open_outfile(t_input *input, int *pipefd)
{
	int	outfile;

	outfile = open(input->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		close(pipefd[0]);
		open_error(input, 2);
	}
	dup2(outfile, 1);
	close(outfile);
}

void	first_cmd(t_input *input, int *pipefd, char *const *envp)
{
	int	err;

	close(pipefd[0]);
	open_infile(input, pipefd);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	if (input->cmd1)
	{
		err = execve(input->cmd1, input->args1, envp);
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
	else
		command_error(input, 1);
}

void	second_cmd(t_input *input, int *pipefd, char *const *envp)
{
	int	err;

	close(pipefd[1]);
	open_outfile(input, pipefd);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	if (input->cmd2)
	{
		err = execve(input->cmd2, input->args2, envp);
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
	else
		command_error(input, 2);
}
