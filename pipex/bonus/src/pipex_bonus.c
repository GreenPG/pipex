/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/11 16:02:04 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	init_pipe(char **av, t_input *input, int cmd_nb, char *const *envp)
{
	int	pipesfd[2][2];
	int	err;
	int	pid;

	err = pipe(pipesfd[1]);
	if (err == -1)
		error_function(input, "Pipe");
	if (!input->file1)
	{
		err = pipe(pipesfd[0]);
		if (err == -1)
			error_function(input, "Pipe");
		here_doc(av, pipesfd[0]);
	}
	pid = fork();
	if (pid == -1)
		error_function(input, "Fork");
	if (pid == 0)
		first_cmd(input, pipesfd, envp);
	pipesfd[0][0] = pipesfd[1][0];
	pipesfd[0][1] = pipesfd[1][1];
	cmds_loop(input, pipesfd, envp, cmd_nb);
	parent_process(pipesfd[0], input, envp, cmd_nb);
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

void	parent_process(int *pipefd, t_input *input, char *const *envp,
		int cmd_nb)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == -1)
		error_function(input, "Fork");
	if (pid == 0)
		last_cmd(input, pipefd, envp, cmd_nb);
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

	if (check_param_nb(ac, av) < 0)
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
	init_pipe(av, input, strtab_len(input->cmd) - 1, envp);
}
