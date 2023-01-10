/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:56:12 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/10 17:07:38 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*here_doc(char **av)
{
	char	*tmp;
	int		fd;

	fd = open(".here_doc.tmp", O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
		return (NULL);
	tmp = "";
	while (ft_strncmp(tmp, av[1], ft_strlen(av[1])) != 0)
	{
		if (tmp[0] != '\0')
			free(tmp);
		tmp = get_next_line(0);
		if (ft_strncmp(tmp, av[1], ft_strlen(av[1])) != 0)
			ft_putstr_fd(tmp, fd);
	}
	free(tmp);
	close(fd);
	return (".here_doc.tmp");
}
