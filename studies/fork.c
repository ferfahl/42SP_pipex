/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:55:40 by feralves          #+#    #+#             */
/*   Updated: 2022/11/26 19:05:54 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main()
{
	int	id_x;
	int	id_y;
	int	status;
	
	id_x = fork();
	id_y = fork();
	if (id_x == 0)
	{
		if (id_y == 0)
		{
			ft_printf("grandchild\nx value: %d\ny value: %d\n\n", id_x, id_y);
		//	ft_printf("Hello from grandchild from 1\n"); //1
		}
		else
		{
			waitpid(id_y, &status, 0);
			ft_printf("child1\nx value: %d\ny value: %d\n\n", id_x, id_y);
		//	ft_printf("Hello from child 1\n"); //2
		}
	}
	
	if (id_x != 0)
	{
		waitpid(id_x, &status, 0);	
		if (id_y == 0)
		{
			ft_printf("child2\nx value: %d\ny value: %d\n\n", id_x, id_y);
		//	ft_printf("Hello from child 2\n"); //3
		}
		else
		{
			waitpid(id_y, &status, 0);
			ft_printf("parent\nx value: %d\ny value: %d\n\n", id_x, id_y);
		//	ft_printf("Hello from parent\n"); //4
		}
	}
}

/* int	main()
{
	int	id_x;
	int	status;
	int	n;
	int i;
	
	id_x = fork();
	if (id_x == 0)
	{
		n = 1;
	}
	else
	{
		waitpid(id_x, &status, 0);
		n = 6;
	}

	i = n;
	while (i < (n + 5))
	{
		ft_printf("%d ", i);
		i++;
	}
	if (id_x != 0)
		ft_printf("\n");
} */