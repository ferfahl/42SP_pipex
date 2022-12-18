/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:37:24 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 19:36:12 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_data *p_data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		ft_free_array(p_data->cmd[i]);
		free(p_data->path[i]);
		i++;
	}
	free(p_data->cmd);
	free(p_data->path);
	free (p_data);
}

void	if_error(char *message, t_data *p_data, int n)
{
	ft_putendl_fd(message, 2);
	if (n == 0)
		return ;
	ft_free_all(p_data);
	exit (n);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*p_data;

	p_data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (p_data == NULL)
		if_error("Calloc error", p_data, 1);
	if (check_error_args(argc, argv, p_data))
		return (1);
	if (check_cmd(argc, argv, envp, p_data))
		return (1);
	pipex_start(p_data, envp);
}
