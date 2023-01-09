/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/09 15:24:51 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	init_pipe(t_input *input, int cmd_nb, char *const *envp)
{
	int	pipesfd[2][2];
	int	err;
	int	pid;

	err = pipe(pipesfd[1]);
	if (err == -1)
		error_function(input, "Pipe");
	pid = fork();
	if (pid == -1)
		error_function(input, "Fork");
	if (pid == 0)
		first_cmd(input, pipesfd[1], envp);
	pipesfd[0][0] = pipesfd[1][0];
	pipesfd[0][1] = pipesfd[1][1];
	cmds_loop(input, pipesfd, envp, cmd_nb);
	parent_process(pipesfd[0], input, envp);
}

void	cmds_loop(t_input *input, int pipesfd[2][2], char	*const	*envp,
		int cmd_nb)
{
	int	i;
	int	err;
	int	pid;

	i = 1;
	while (i < cmd_nb -1)
	{
		err = pipe(pipesfd[1]);
		if (err == -1)
			error_function(input, "Pipe");
		pid = fork();
		if (pid == -1)
			error_function(input, "Fork");
		if (pid == 0)
			child_cmd(input, pipesfd, envp, i);
		else
		{
			close(pipesfd[0][0]);
			close(pipesfd[0][1]);
			pipesfd[0][0] = pipesfd[1][0];
			pipesfd[0][1] = pipesfd[1][1];
			i++;
		}
	}
}

void	parent_process(int *pipefd, t_input *input, char *const *envp)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == -1)
		error_function(input, "Fork");
	if (pid == 0)
		last_cmd(input, pipefd, envp);
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		free_struct(input);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		exit(status);
	}
}

int	main(int ac, char **av, char *const *envp)
{
	t_input	*input;

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
	init_pipe(input, ac - 3, envp);
}
