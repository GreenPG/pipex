/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:30:33 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/20 15:58:29 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_input	*init_struct(void)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(*input));
	if (!input)
		return (0);
	return (input);
}
