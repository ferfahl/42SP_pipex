/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:14:54 by feralves          #+#    #+#             */
/*   Updated: 2022/11/29 22:28:56 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//Libraries
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"

//Structs
typedef struct s_data
{
	int		index;
	int		status;
	int		fd[]; //isso existe? funciona?
	char	**cmd[];
	char	**temp;
	char	**path[];
}				t_data;

//Functions

#endif
