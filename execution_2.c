/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 14:07:54 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/13 16:01:06 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(char	*cmd)
{

	if (!ft_strcmp(cmd, "cd"))
		return (2);
	if (!ft_strcmp(cmd, "pwd"))
		return (3);
	return (0);
}

void	exec_builtins(char	**str, t_env_list **env_list, int code)
{
	if (code == 2)
    {
		ft_cd(str[1], env_list);
        exit(0);
    }
	else if (code == 3)
    {
		ft_pwd();
        exit(0);
    }
	
}

int main_builtins(t_cmd_line **cmd_line)
{
    if ((*cmd_line) && (*cmd_line)->str[0])
    {
        if (!ft_strcmp((*cmd_line)->str[0], "cd"))
            return (1);
    
    }
    return (0);
}

void    execute_builtins(t_cmd_line **cmd_line, t_env_list **env_list)
{
    if (!ft_strcmp((*cmd_line)->str[0], "cd"))
        ft_cd((*cmd_line)->str[1], env_list);
    if (!ft_strcmp((*cmd_line)->str[0], "pwd"))
        ft_pwd();
    
}