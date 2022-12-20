/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/20 16:58:07 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_pipe(int *pipefd, t_input *input)
{
	int	err;
	int	pid;

	err = access(input->file1, R_OK);
	if (err == -1)
	{
		free_struct(input);
		ft_printf("Cannot read this file");
		return (-1);
	}
	err = pipe(pipefd);
	if (err == -1)
	{
		free_struct(input);
		perror("Pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		free_struct(input);
		perror("Error");
		return (-1);
	}
	return (pid);
}

int	main(int ac, char **av)
{
	t_input	*input;	
	int		pid;
	int		pipefd[2];

	if (ac < 2)
		return (0);
	input = parsing(av + 1);
	if (!input)
		return (0);
	pid = init_pipe(pipefd, input);
	if (pid == -1)
	{
		free_struct(input);
		perror(NULL);
		return (0);
	}
	if (pid == 0)
		first_cmd(input, pipefd);
	else
	{
		wait(NULL);
		pid = fork();
		if (pid == -1)
		{
			free_struct(input);
			perror("Fork :");
			return (0);
		}
		if (pid == 0)
			second_cmd(input, pipefd);
		else
		{
			close(pipefd[0]);
			close(pipefd[1]);
			free_struct(input);
		}
	}
	return (0);
}
