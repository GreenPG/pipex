/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:19:38 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/22 10:49:49 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

size_t	strtab_len(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
		i++;
	return (i);
}

void	error_function(t_input *input, char *message)
{
	free_struct(input);
	perror(message);
	exit(1);
}
