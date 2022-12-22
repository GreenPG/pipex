/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:32:52 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/22 16:06:05 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_cmd(t_input *input, int *pipefd, char *const *envp)
{
	int	infile;
	int	err;

	close(pipefd[0]);
	infile = open(input->file1, O_RDONLY);
	if (infile == -1)
	{
		write(2, "pipex: no such file or directory: ", 34);
		ft_putstr_fd(input->file1, 2);
		write(2, "\n", 1);
		free_struct(input);
		exit(EXIT_FAILURE);
	}
	dup2(infile, 0);
	close(infile);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	err = execve(input->cmd1, input->args1, envp);
	if (err == -1)
	{
		free_struct(input);
		exit(EXIT_FAILURE);
	}
}

void	second_cmd(t_input *input, int *pipefd, char *const *envp)
{
	int	outfile;
	int	err;

	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	outfile = open(input->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		write(2, "pipex: no such file or directory: ", 34);
		ft_putstr_fd(input->file2, 2);
		write(2, "\n", 1);
		free_struct(input);
		exit(EXIT_FAILURE);
	}
	dup2(outfile, 1);
	close(outfile);
	err = execve(input->cmd2, input->args2, envp);
	if (err == -1)
	{
		free_struct(input);
		exit(EXIT_FAILURE);
	}
}
