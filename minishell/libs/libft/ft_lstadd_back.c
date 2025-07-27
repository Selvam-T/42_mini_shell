/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:21:02 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/21 19:02:21 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_var **lst, t_var *new)
{
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}
/*
int	main(void)
{
	t_var *l;
	t_var  *m;

	l = NULL;
	m = NULL;
	//l = ((void*)0);
	//l = ft_lstnew("one");
	m = ft_lstnew("Two");

	//ft_lstadd_back(&l,(void*)0);
	ft_lstadd_back(&l,m);
	while (l)
	{
		printf("%s \n",(char *)l->content);
		l = l->next;
	}
}*/
