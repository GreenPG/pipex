/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/06 17:19:48 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	init_pipe(t_input *input, int *pid, int cmd_nb, char *const *envp)
{
	int	pipefd_in[2];
	int	pipefd_out[2];
	int	err;
	int	i;

	err = pipe(pipefd_out);
	if (err == -1)
		error_function(input, "Pipe");
	first_cmd(input, pipefd_out, envp);
	i = 0;
	while (i < cmd_nb -1)
	{
		err = pipe(pipefd_in);
		if (err == -1)
			error_function(input, "Pipe");
		pid[i] = fork();
		if (pid[i] == -1)
			error_function(input, "Fork");
		if (pid == 0)
			child_function(input, pipefd, envp);
		else
		{
			pipefd_out[0] = pipefd_in[0];
			pipefd_out[1] = pipefd_in[1];
			i++;
		}
	}
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
	int		*pid;

	if (ac < 5)
	{
		write(2, "pipex: incorrect number of arguments\n", 37);
		return (EXIT_FAILURE);
	}
	input = parsing(av + 1, envp);
	if (!input || !input->args || !input->args)
	{
		free_struct(input);
		exit(EXIT_FAILURE);
	}
	pid = malloc(sizeof(int) * (ac -3));
	if (!pid)
	{
		free_struct(input);
		exit(EXIT_FAILURE);
	}
	init_pipe(input, pid, ac - 3, envp);
}
