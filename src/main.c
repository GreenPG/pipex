/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/19 17:07:11 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av)
{
	t_input	*input;	
	int		pid;
	int		pipe_fd[2];
	int		err;
	int		file;

	if (ac < 2)
		return (0);
	input = parsing(av + 1);
	if (!input)
		return (0);
	if (pipe(pipe_fd) == -1)
	{
		free_struct(input);
		perror("Pipe :");
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		free_struct(input);
		perror("Error :");
		return (0);
	}
	if (pid == 0)
	{
		file = open(input->file1, O_WRONLY | O_CREAT, 0777);
		dup2(file, 1);
		close(file);
		err = execve(input->cmd1, input->args1, NULL);
		if (err == -1)
		{
			free_struct(input);
			perror(NULL);
			return (0);
		}
	}
	else
	{
		free_struct(input);
	}
	return (0);
}
