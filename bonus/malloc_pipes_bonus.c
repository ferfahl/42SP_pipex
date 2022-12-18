/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_p_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:47:41 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 17:29:49 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_malloc_p_data(t_data *p_data)
{
	int	i;

	i = 0;
	p_data->cmd = (char ***)malloc(sizeof (char **) * (p_data->n_cmd));
	if (!p_data->cmd)
		if_error("Malloc error", p_data, 1);
	p_data->path = (char **)malloc(sizeof (char *) * (p_data->n_cmd));
	if (!p_data->path)
		if_error("Malloc error", p_data, 1);
	p_data->check = (int *)malloc(sizeof (int) * (p_data->n_cmd));
	if (!p_data->check)
		if_error("Malloc error", p_data, 1);
	p_data->pipes = (int **)malloc(sizeof (int *) * (p_data->n_cmd));
	if (!p_data->pipes)
		if_error("Malloc error", p_data, 1);
	while (i < p_data->n_cmd)
	{
		p_data->pipes[i] = (int *)malloc(sizeof (int) * 2);
		if (!p_data->pipes[i])
			if_error("Malloc error", p_data, 1);
		i++;
	}
}
