/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:47:41 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 17:29:49 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_malloc_pipes(t_data *pipes)
{
	int	i;

	i = 0;
	pipes->cmd = (char ***)malloc(sizeof (char **) * (pipes->n_cmd));
	if (!pipes->cmd)
		if_error("Malloc error", pipes, 1);
	pipes->path = (char **)malloc(sizeof (char *) * (pipes->n_cmd));
	if (!pipes->path)
		if_error("Malloc error", pipes, 1);
	pipes->check = (int *)malloc(sizeof (int) * (pipes->n_cmd));
	if (!pipes->check)
		if_error("Malloc error", pipes, 1);
	pipes->pippin = (int **)malloc(sizeof (int *) * (pipes->n_cmd));
	if (!pipes->pippin)
		if_error("Malloc error", pipes, 1);
	while (i < pipes->n_cmd)
	{
		pipes->pippin[i] = (int *)malloc(sizeof (int) * 2);
		if (!pipes->pippin[i])
			if_error("Malloc error", pipes, 1);
		i++;
	}
}
