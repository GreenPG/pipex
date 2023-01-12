/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:58:48 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/12 14:49:46 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "../../libft/include/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
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
int		main(int ac, char **av, char *const *envp);

//	parsing.c
t_input	*parsing(char **av, char *const *envp);

//	utils.c
size_t	strtab_len(char **tab_str);
void	infile_error(t_input *input, int pipefd[2]);

//	error_functions.c
void	open_error(t_input *input, int cmd_nb);
void	error_function(t_input *input, char *message);
void	no_file_function(t_input *input, int cmd_nb);
void	no_permission_function(t_input *input, int cmd_nb);
void	command_error(t_input *input, int cmd_nb);

//	free_functions.c
void	free_struct(t_input *input);
void	free_tab(char **str_tab);
void	free_cmds(char **str_tab, int cmd_nb);
void	free_tab_tab(char ***tab_tab);

//	strcut_utils.c
t_input	*init_struct(void);

//	child_functions.c
void	first_cmd(t_input *input, int *pipefd, char *const *envp);
void	second_cmd(t_input *input, int *pipefd, char *const *envp);

#endif
