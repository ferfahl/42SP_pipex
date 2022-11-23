/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:55:40 by feralves          #+#    #+#             */
/*   Updated: 2022/11/23 17:13:27 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command(char **possible_paths)
{
	int	i;
	char	*temp;

	i = 0;
	while (possible_paths[i])
	{
		temp = ft_strjoin(possible_paths[i], "/grep");
		if (access(temp, F_OK) == 0)
			return (temp);
		i++;
	}
	return (NULL); //command not found
}

char	*get_path(char *envp[])
{
	int	i;
	char	**possible_paths;
	char	*right_path;
	
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	possible_paths = ft_split(&envp[i][5], ':');
//	ft_printf_array(possible_paths);
	right_path = find_command(possible_paths);
//	ft_printf("Right path: %s\n", right_path);
	if (!right_path)
		return (NULL);
	return (right_path);
}

int main(int argc, char *argv[], char *envp[])
{
//	char	*file1;
	int		fd;
	int		index;
	char *path;
	char *cmd[3] = {"grep", "a", NULL};
	char *cmd2[4] = {"tr", "a", "b", NULL};

	index = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror(argv[1]);
	ft_printf("#%d argv: %s\n", index, argv[1]);
	path = get_path(envp);
	(void)argc;
/* 	if (find_command(cmd[0]))
	{	
		ft_printf("Command not found\n");
		exit(0);
	} */
	int	cavalinho[2];
	int mario = pipe(cavalinho);
	if (mario)
		return (-1);
	int	child1 = fork();
	if (child1 == 0)
	{
		dup2(fd, 0);
		dup2(cavalinho[1], 1);
		int exe = execve(path, cmd, envp);
		ft_printf("Error?\n");
		return (exe);
	}
	close(fd);
	int	child2 = fork();
	if (child2 == 0)
	{
		close(cavalinho[1]);
		dup2(cavalinho[0], 0);
		int exe2 = execve("/usr/bin/tr", cmd2, envp);
		ft_printf("Error?\n");
		return (exe2);
	}
	close(cavalinho[1]); //fechando um lado do pipe
	close(cavalinho[0]); //fechando o outro lado do pipe
	int status;
	waitpid(child2, &status, 0);
	wait(NULL);
	if (WIFEXITED(status)) //if terminated correctly or error
	{
		status = WEXITSTATUS(status);
		ft_printf("child's status: %d\n", status);
	}
	
	
	return (0);

}

