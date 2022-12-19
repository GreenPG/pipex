/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:30:33 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/19 09:20:44 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_input	*init_struct(void)
{
	t_input	*input;

	input = malloc(sizeof(*input));
	if (!input)
		return (0);
	input->file1 = NULL;
	input->file2 = NULL;
	input->cmd1 = malloc (sizeof(char) * 6);
	input->cmd2 = malloc (sizeof(char) * 6);
	input->cmd1 = "/bin/";
	input->cmd2 = "/bin/";
	input->args1 = NULL;
	input->args2 = NULL;
	return (input);
}
