/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:41:07 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/01 16:12:30 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	select_specific(t_entlist *l, int value, int v)
{
	t_entry *tmp;
	int		i;

	i = 0;
	tmp = l->head;
	while (i < l->ac)
	{
		if (tmp->t == value && v)
			tmp->hl = 1;
		else
			tmp->hl = 0;
		tmp = tmp->next;
		i++;
	}
}

void	delete_key(t_entlist *l)
{
	if (delete_entry(l) < 0)
	{
		clean_screen(l);
		reset_default_mode(&l->old_term);
		exit(0);
	}
	l->list->us = 1;
}

void	go_right(t_entlist *l)
{
	int i;

	i = 0;
	l->list->us = 0;
	while (i < l->row - 1)
	{
		l->list = l->list->next;
		i++;
	}
	l->list->us = 1;
}

void	go_left(t_entlist *l)
{
	int i;

	i = 0;
	l->list->us = 0;
	while (i < l->row - 1)
	{
		l->list = l->list->prev;
		i++;
	}
	l->list->us = 1;
}

int		launcher(t_entlist *l)
{
	char			buf[MAX_KEY_LENGTH];
	int				is_running;
	unsigned int	key;

	set_draw(l);
	is_running = 1;
	while (is_running)
	{
		draw(l);
		ft_bzero(buf, MAX_KEY_LENGTH);
		read(0, buf, MAX_KEY_LENGTH);
		key = *(unsigned int *)buf;
		key_handler(key, l, &is_running);
	}
	return (0);
}
