/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 17:19:42 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/01 16:11:18 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	init_entlist(t_entlist *l, char **av, int ac)
{
	t_entry			*tmp;
	t_entry			*slow;
	struct winsize	w;

	ioctl(l->fd, TIOCGWINSZ, &w);
	l->height = w.ws_row;
	l->width = w.ws_col;
	l->row = l->height - START - PAD;
	l->col = l->width - SPACE * 2;
	l->head = NULL;
	l->list = NULL;
	l->ac = ac - 1;
	l->max_len = 0;
	getargs(ac, av, l);
	l->head = l->list;
	tmp = l->list;
	slow = l->list;
	while (tmp->next)
	{
		tmp = tmp->next;
		tmp->prev = slow;
		slow = slow->next;
	}
	tmp->next = l->head;
	l->list->prev = tmp;
}

void	addentry(t_entlist *l, t_entry *new)
{
	t_entry *tmp;

	l->sel_v = 0;
	tmp = l->list;
	if (!tmp)
		l->list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	getargs(int ac, char **av, t_entlist *l)
{
	int i;
	int	max_len;

	i = 1;
	while (ac-- > 1)
	{
		max_len = ft_strlen(av[i]);
		l->max_len = max_len > l->max_len ? max_len : l->max_len;
		addentry(l, newentry(av[i]));
		i++;
	}
}

void	entry_destroy(t_entlist *l)
{
	t_entry *tmp;
	int		i;

	i = 0;
	if (l->head)
	{
		while (i < l->ac)
		{
			tmp = l->head;
			l->head = l->head->next;
			free(tmp->line);
			free(tmp);
			i++;
		}
	}
	close(l->fd);
}
