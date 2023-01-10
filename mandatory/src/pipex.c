/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/10 09:45:18 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_pipe(int *pipefd, t_input *input)
{
	int	err;
	int	pid;

	err = pipe(pipefd);
	if (err == -1)
		error_function(input, "Pipe");
	pid = fork();
	if (pid == -1)
		error_function(input, "Fork");
	return (pid);
}

void	parent_process(int *pipefd, t_input *input, char *const *envp, int *pid)
{
	int	status;

	pid[1] = fork();
	if (pid[1] == -1)
		error_function(input, "Fork");
	if (pid[1] == 0)
		second_cmd(input, pipefd, envp);
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_struct(input);
		waitpid(pid[1], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		exit(status);
	}
}

int	main(int ac, char **av, char *const *envp)
{
	t_input	*input;
	int		pid[2];
	int		pipefd[2];

	if (ac != 5)
	{
		write(2, "pipex: incorrect number of arguments\n", 37);
		return (EXIT_FAILURE);
	}
	input = parsing(av + 1, envp);
	if (!input || !input->args1 || !input->args2)
	{
		free_struct(input);
		exit(EXIT_FAILURE);
	}
	pid[0] = init_pipe(pipefd, input);
	if (pid[0] == -1)
		error_function(input, NULL);
	if (pid[0] == 0)
		first_cmd(input, pipefd, envp);
	else
		parent_process(pipefd, input, envp, pid);
}
