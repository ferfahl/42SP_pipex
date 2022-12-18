/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:14:54 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 19:36:12 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

//Libraries
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

//Structs
typedef struct s_data
{
	int		index;
	int		status;
	int		n_cmd;
	int		infile;
	int		outfile;
	int		*check;
	int		**pipes;
	char	**path;
	char	***cmd;
}				t_data;

//Define
# define TEMP_SPACE 1
# define STDIN 0
# define STDOUT 1

//Functions
void	if_error(char *message, t_data *p_data, int n);
void	error_args(char *file, t_data *p_data, int n);
void	if_error_silent(t_data *p_data, int n);
void	ft_free_all(t_data *p_data);
void	check_cmd(int argc, char *argv[], char *envp[], t_data *p_data);
int		check_error_args(int argc, char *argv[], t_data *p_data);
void	pipex_start(t_data *p_data, char *envp[]);
char	**ft_split_pipex(char *argument);
void	ft_malloc_p_data(t_data *p_data);

#endif
