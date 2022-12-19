/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:37:24 by feralves          #+#    #+#             */
/*   Updated: 2022/12/19 15:37:41 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_all(t_data *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->n_cmd)
	{
		ft_free_array(p_data->cmd[i]);
		free(p_data->path[i]);
		free(p_data->pipes[i]);
		i++;
	}
	free(p_data->check);
	free(p_data->pipes);
	free(p_data->cmd);
	free(p_data->path);
	free (p_data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*p_data;

	p_data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (p_data == NULL)
		if_error("Calloc error", p_data, 1);
	if (check_error_args(argc, argv, p_data))
		return (1);
	if (p_data->here_doc)
	 	here_doc(p_data);
	check_cmd(argc, argv, envp, p_data);
	pipex_start(p_data, envp);
}
