/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:33:44 by cattouma          #+#    #+#             */
/*   Updated: 2016/05/30 17:52:18 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		go_down(t_entlist *l)
{
	l->list->us = 0;
	l->list = l->list->next;
	l->list->us = 1;
}

void		go_up(t_entlist *l)
{
	l->list->us = 0;
	l->list = l->list->prev;
	l->list->us = 1;
}

void		clean_screen(t_entlist *l)
{
	ft_putstr_fd(tgetstr("ho", NULL), l->fd);
	ft_putstr_fd(tgetstr("cd", NULL), l->fd);
	ft_putstr_fd(tgetstr("ve", NULL), l->fd);
	ft_putstr_fd(tgetstr("te", NULL), l->fd);
}

static void	special_keys(unsigned int key, t_entlist *l)
{
	if (key == K_SPACE)
	{
		l->list->hl = l->list->hl == 0 ? 1 : 0;
		go_down(l);
	}
	else if (key == K_DEL || key == K_BKSPC)
		delete_key(l);
	else if (key == K_A)
	{
		l->sel_v = l->sel_v == 0 ? 1 : 0;
		select_all(l, l->sel_v);
	}
	else if (key == K_R)
	{
		l->sel_v = l->sel_v == 0 ? 1 : 0;
		select_specific(l, R, l->sel_v);
	}
	else if (key == K_D)
	{
		l->sel_v = l->sel_v == 0 ? 1 : 0;
		select_specific(l, D, l->sel_v);
	}
	else if (key == K_X)
	{
		l->sel_v = l->sel_v == 0 ? 1 : 0;
		select_specific(l, X, l->sel_v);
	}
}

void		key_handler(unsigned int key, t_entlist *l, int *running)
{
	if (key == K_ENT)
	{
		clean_screen(l);
		*running = 0;
	}
	else
	{
		if (key == K_ESC)
			quit(l);
		else if (key == K_DOWN)
			go_down(l);
		else if (key == K_UP)
			go_up(l);
		else if (key == K_RIGHT)
			go_right(l);
		else if (key == K_LEFT)
			go_left(l);
		else
			special_keys(key, l);
	}
}
