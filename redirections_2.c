/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:38:42 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/11 00:39:05 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

dup_outfile(t_redirections *redirection)
{
	int	fd;
	
	if (redirection->type == RIGHTRED)
		fd = open(redirection->file, O_WRONLY | O_TRUNC, 0664);
	if (redirection->type == APPEND)
		fd = open(redirection->file, O_WRONLY | O_APPEND, 0664);
	dup2(fd, 1);
	close(fd);
}