/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:43:38 by arpenel           #+#    #+#             */
/*   Updated: 2025/09/26 15:55:30 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>

typedef struct s_list
{
    void    *content;
    struct s_list *next;
}   t_list;

// libc functions //
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
void		ft_bzero(void *s, size_t n);
char	*ft_strjoin_nofree(char const *s1, char const *s2);

// additional functions //
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(const char *s, char sep);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

// lst functions // 
t_list  *ft_lstlast(t_list *lst);
void    ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void    ft_lstadd_front(t_list **lst, t_list *new);
void    ft_lstclear(t_list **lst, void (*del)(void *));
void    ft_lstdelone(t_list *lst, void (*del)(void *));
void    ft_lstiter(t_list *lst, void (*f)(void *));
int ft_lstsize(t_list *lst);

#endif 
