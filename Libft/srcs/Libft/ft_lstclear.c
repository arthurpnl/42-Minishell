/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:09:48 by arpenel           #+#    #+#             */
/*   Updated: 2025/03/06 14:09:51 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list  *current; 
    t_list  *next;

    if (!lst || !del)
        return ;
    
    current = *lst;
    while (current)
    {
        next = current->next;
        del(current->content);
        free(current);
        current = next;
    }
    *lst = NULL;
}