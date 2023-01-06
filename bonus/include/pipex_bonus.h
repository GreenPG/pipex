/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:58:48 by gpasquet          #+#    #+#             */
/*   Updated: 2023/01/06 14:55:49 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include "../../libft/include/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_input {
	char	*file1;
	char	*file2;
	char	**cmd;
	char	***args;
}	t_input;

//	pipex_bonus.c
int		main(int ac, char **av, char *const *envp);
void	init_pipe(t_input *input, int cmd_nb, char *const *envp);
void	parent_process(int *pipefd, t_input *input, char *const *envp);

//	parsing_bonus.c
t_input	*parsing(char **av, char *const *envp);
char	*get_cmds(char *av, char *const *envp);
char	**get_paths(char *const *envp);
char	**get_splitted_envp(char *const *envp);

//	utils_bonus.c
size_t	strtab_len(char **tab_str);
void	error_function(t_input *input, char *message);
void	no_file_function(t_input *input);
void	no_permission_function(t_input *input);

//	free_functions_bonus.c
void	free_tab(char **str_tab);
void	free_struct(t_input *input);
void	free_tab_tab(char ***tab_tab);

//	strcut_utils_bonus.c
t_input	*init_struct(void);

//	child_functions_bonus.c
void	first_cmd(t_input *input, int *pipefd, char *const *envp);
void	last_cmd(t_input *input, int *pipefd, char *const *envp);
void	child_cmd(t_input *input, int *pipefd_in, int *pipefd_out, char *const *envp, int cmd_nb);

#endif
