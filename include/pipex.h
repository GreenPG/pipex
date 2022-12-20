/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:58:48 by gpasquet          #+#    #+#             */
/*   Updated: 2022/12/20 16:54:09 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "../libft/include/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_input {
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
	char	**args1;
	char	**args2;
}	t_input;

//	pipex.c
int		main(int ac, char **av);
int		init_pipe(int *pipefd, t_input *input);

//	parsing.c
t_input	*parsing(char **av);
void	get_cmds(char **av, t_input *input);
char	**get_args(char **splitted_input);
char	***get_splitted_input(char **av);

//	utils.c
size_t	strtab_len(char **tab_str);

//	free_functions.c
void	free_tab(char **str_tab);
void	free_struct(t_input *input);
void	free_tab_tab(char ***tab_tab);

//	strcut_utils.c
t_input	*init_struct(void);

//	first_cmd.c
void	first_cmd(t_input *input, int *pipefd);
void	second_cmd(t_input *input, int *pipefd);

#endif
