/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/21 17:14:22 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_pipe(int *pipefd, t_input *input)
{
	int	err;
	int	pid;

	err = access(input->file1, R_OK);
	if (err == -1)
		error_function(input, "Access");
	err = pipe(pipefd);
	if (err == -1)
		error_function(input, "Pipe");
	pid = fork();
	if (pid == -1)
		error_function(input, "Fork");
	return (pid);
}

void	parent_process(int *pipefd, t_input *input, char *const *envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_function(input, "Fork");
	if (pid == 0)
		second_cmd(input, pipefd, envp);
	else
	{
		wait(NULL);
		close(pipefd[0]);
		close(pipefd[1]);
		free_struct(input);
	}
}

int	main(int ac, char **av, char *const *envp)
{
	t_input	*input;
	int		pid;
	int		pipefd[2];

	if (ac < 5)
		return (0);
	input = parsing(av + 1, envp);
	if (!input)
		return (0);
	pid = init_pipe(pipefd, input);
	if (pid == -1)
		error_function(input, NULL);
	if (pid == 0)
		first_cmd(input, pipefd, envp);
	else
		parent_process(pipefd, input, envp);
	return (0);
}
