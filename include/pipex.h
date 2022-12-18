/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:58:48 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/18 13:56:43 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "../libft/include/libft.h"

typedef struct s_input {
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
	char	**args1;
	char	**args2;
}	t_input;

//	parsing.c
t_input	*parsing(char **av);
void	get_cmds(char **av, t_input *input);
char	**get_args(char **splitted_input);

//	utils.c
size_t	strtab_len(char **tab_str);

//	free_functions.c
void	free_tab(char **str_tab);
void	free_struct(t_input *input);

//	strcut_utils.c
t_input	*init_struct(void);

#endif
