/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:38:01 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/10 18:03:48 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_command_in_path(char **path, char *cmd)
{
	int i;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		if (!access(ft_strjoin(path[i], cmd), F_OK))
		{
			return (ft_strjoin(path[i], cmd));
			break;
		}
		i++;
	}
	return (NULL);
}

int count_envlist(t_env_list **env_list)
{
	t_env_list *envlist;
	int i;

	envlist = *env_list;
	i = 0;
	while (envlist)
	{
		i++;
		envlist = envlist->next;
	}
	return (i);
}

char **create_envp(t_env_list **env_list)
{
	t_env_list *envlist;
	char **envp;
	int i;
	char *tmp;

	envlist = *env_list;
	envp = malloc(sizeof(char *) * count_envlist(env_list) + 1);
	i = 0;
	while (envlist)
	{
		tmp = ft_strjoin(envlist->name, "=");
		envp[i] = ft_strjoin(tmp, envlist->value);
		envlist = envlist->next;
		i++;
	}
	return (envp);
}

void execve_func(char **cmd, t_env_list **env_list)
{
	char **path;
	char *cmd_;
	char **envp;

	path = get_path(env_list);
	cmd_ = check_command_in_path(path, cmd[0]);
	envp = create_envp(env_list);
	if (!cmd_)
	{
		perror("Command not found");
		exit(0);
	}
	execve(cmd_, cmd, envp);
}

void execute_command_2(t_cmd_line **cmd_line, t_env_list **env_list)
{
	int built_code;

	built_code = builtins((*cmd_line)->str[0]);
	if (built_code)
	{
		exec_builtins((*cmd_line)->str, env_list, built_code);
	}
	else
	{

		execve_func((*cmd_line)->str, env_list);
	}
}

void dup_pipe(int **fd, int i, int cmds)
{
	if (i == 0)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		
	}
	if (i > 0)
	{
		if (i + 1 == cmds)
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
		
		}
		else
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
			dup2(fd[i][1], STDOUT_FILENO);
		}			
	}
}


void execute_command(t_cmd_line **cmd_line, t_env_list **env_list)
{
	t_cmd_line 		*cmd_tmp;
	int 		cmds;
	int 		**fd;
	int 		i;
	int 		j;

	cmd_tmp = *cmd_line;
	cmds = count_list(cmd_line);
	fd = malloc(sizeof(int *) * (cmds - 1));
	i = 0;
	int flg = 0;
	while (cmd_tmp)
	{
		if (cmd_tmp->separator == e_pipe)
		{
			fd[i] = malloc(sizeof(int) * 2);
			pipe(fd[i]);
			flg = 1;
		}
		if (fork() == 0)
		{
			if (flg)
			{
				dup_pipe(fd[i], i, cmds);
				j = i;
				while (j >= 0)
				{
					close(fd[j][0]);
					close(fd[j][1]);
					j--;
				}
			}
			execute_command_2(&cmd_tmp, env_list);
		}
		cmd_tmp = cmd_tmp->next;
		i++;
	}
	i = i - 2;
	while (i>=0)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i--;
	}
	while (wait(0) != -1);
}

void execution(t_cmd_line **cmd_line, t_env_list **env_list)
{
	// if ((*cmd_line) && main_builtins(cmd_line) && (*cmd_line)->separator == e_nline)
	//     execute_builtins(cmd_line, env_list);
	if ((*cmd_line))
	{

		execute_command(cmd_line, env_list);
	}
}