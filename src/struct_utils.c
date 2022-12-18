/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:30:33 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/18 13:32:53 by gpasquet         ###   ########.fr       */
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
	input->cmd1 = NULL;
	input->cmd2 = NULL;
	input->args1 = NULL;
	input->args2 = NULL;
	return (input);
}
