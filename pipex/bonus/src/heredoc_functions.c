/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:56:12 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/11 15:43:50 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include <stdlib.h>

void	here_doc(char **av, int pipefd[2])
{
	char	*tmp;
	char	*limiter;

	tmp = ft_strdup(av[2]);
	limiter = ft_strjoin(tmp, "\n");
	if (!limiter)
		exit(EXIT_FAILURE);
	free(tmp);
	tmp = "";
	while (tmp[0] == '\0' || ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(">", 1);
		if (tmp[0] != '\0')
			free(tmp);
		tmp = get_next_line(0);
		if (ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
			ft_putstr_fd(tmp, pipefd[1]);
	}
	free(limiter);
	free(tmp);
}
