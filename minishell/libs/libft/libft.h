/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:21:06 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:24:57 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_var
{
	char			*name;
	char			*value;
	char			c;
	struct s_var	*next;
}	t_var;

int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_is_strdigit(const char *nptr);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strncmp_uc(const char *s1, const char *s2, size_t n);
int			ft_is_strequal(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strbef_chr(const char *s, int c);
char		*ft_strchrind(const char *s, int c, int *ind);
char		*ft_strbef_chridx(const char *s, int c, int *i);
int			ft_chrindex(const char *s, int c);
char		*ft_strslice_btwchr(char *str, char c);
char		*ft_strslice_btwidx(char *str, int start, int end);
char		*ft_substr_idx(const char *s, int c, int *ind);
int			ft_toupper(int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_strjoin3(char *s1, char *s2);

char		**ft_split(char const *s, char c);
long		ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);

t_var		*ft_lstnew(char *name, char *val);
t_var		*ft_lstnew2(char *name, char *val, char c);
void		ft_lstadd_back(t_var **lst, t_var *new);
void		ft_lstadd_front(t_var **lst, t_var *new);
t_var		*ft_lstlast(t_var *lst);
t_var		*ft_lstbeforelast(t_var *lst);
t_var		*ft_lst_extlast(t_var *lst);
int			ft_lstsize(t_var *lst);

void		ft_putstr_fd(char *s, int fd);
char		*ft_itoa(int n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strrchr(const char *str, int ch);

#endif
