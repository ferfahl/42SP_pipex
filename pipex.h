/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:14:54 by feralves          #+#    #+#             */
/*   Updated: 2022/12/10 21:05:37 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	int		fd[2];
	int		check[2];
	char	**temp;
	char	**path;
	char	***cmd;
}				t_data;

//Define
# define TEMP_SPACE 1

//Functions
void	if_error(char *message, t_data *pipes, int n);
int		check_cmd(int argc, char *argv[], char *envp[], t_data *pipes);
int		check_error_args(int argc, char *argv[], t_data *pipes);
void	pipex_start(t_data *pipes, char *envp[]);
char	**ft_split_pipex(char *argument);

#endif
