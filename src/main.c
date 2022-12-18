/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/18 13:34:19 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av)
{
	t_input	*input;	
	int i;

	if (ac < 2)
		return (0);
	input = parsing(av + 1);
	if (!input)
		return (0);
	ft_printf("%s\n", input->file1);
	ft_printf("%s\n", input->cmd1);
	i = 0;
	while (input->args1[i])
	{
		ft_printf("%s ", input->args1[i]);
		i++;
	}
	ft_printf("\n");
	i = 0;
	while (input->args2[i])
	{
		ft_printf("%s ", input->args2[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("%s\n", input->cmd2);
	ft_printf("%s\n", input->file2);
	free_struct(input);
}
