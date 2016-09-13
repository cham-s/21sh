/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entry2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:39:06 by cattouma          #+#    #+#             */
/*   Updated: 2016/09/13 15:32:33 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_entlist	*ret_entlist(void)
{
	static t_entlist l;

	return (&l);
}

t_entry		*newentry(char *str)
{
	t_entry *new;

	new = (t_entry *)ft_memalloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->line = ft_strdup(str);
	new->hl = 0;
	new->us = 0;
	new->t = 0;
	return (new);
}

int			nbr_col(t_entlist *l)
{
	double	cols_float;
	int		cols_int;

	cols_float = (double)l->ac / (double)l->row;
	if (cols_float == (int)cols_float)
		cols_int = (int)cols_float;
	else
		cols_int = (int)cols_float + 1;
	cols_int = (l->max_len + SPACE) * cols_int;
	return (cols_int);
}
