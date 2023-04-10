/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:25:03 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/10 16:54:13 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_last(t_redirections **redirections_)
{
    t_redirections  *redirections;

    redirections = *redirections_;
    while (redirections)
    {
        if (redirections->type == LEFTRED || redirections->type == HEREDOC)
            return (0);
        redirections = redirections->next;
    }
    return (1);
}

t_redirections  *last_in(t_redirections **redirections_)
{
    t_redirections  *redirections;

    redirections = *redirections_;
    while (redirections)
    {
        if (redirections && (redirections->type == LEFTRED || redirections->type == HEREDOC))
        {
            if (redirections->next && is_last(&redirections->next))
                return (redirections);
        }
        redirections = redirections->next;
    }
    return (NULL);
}