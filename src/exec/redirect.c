/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/08/07 10:34:51 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    dispatch_redirect(t_commande *cmd_list)
{
    t_redirection *current;
    int    res;

    res = -1;
    current = cmd_list->redirection;
    while(current != NULL)
    {
        if(current->type == TOK_REDIR_IN)
            res = handle_input_redirect(current);
        else if(current->type == TOK_REDIR_OUT)
            res = handle_output_redirect(current);
        else if(current->type == TOK_REDIR_APPEND)
            res = handle_append_redirect(current);
        else if(current->type == TOK_HEREDOC)
            res = handle_heredoc_redirect(current);
        if (res != 0)
            return (res);
        current = current->next;
    }
    return (0);
}

int    handle_input_redirect(t_redirection *redir)
{
    int    fd;

    fd = open(redir->file, O_RDONLY);
    if (fd == -1)
    {
        perror(redir->file);
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int    handle_output_redirect(t_redirection *redir)
{
    int    fd;

    fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror(redir->file);
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int    handle_append_redirect(t_redirection *redir)
{
    int    fd;

    fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror(redir->file);
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int    handle_pipe_redirect(t_redirection *redir,t_commande cmd_list, int **pipes, int i)
{
    int    count_cmd;

    count_cmd = count_command(cmd_list);
    if (i == 0)
        dup2(pipes[0][1], STDOUT_FILENO);
    else if (i > 0 && i < count_cmd - 1)
    {
        dup2(pipes[i - 1][0], STDIN_FILENO);
        dup2(pipes[i][1], STDOUT_FILENO);
    }
    else if (i == count_cmd - 1 && nb > 1)
        dup2(pipes[i - 1][0], STDIN_FILENO);
    close_all_pipes(pipes, i);
    return (0);
}