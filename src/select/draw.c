/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:33:43 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/01 16:03:26 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	draw_at_location(int x, int y, char *str, int fd)
{
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), x, y), fd);
	ft_putstr_fd(str, fd);
}

static int	init_draw(t_entlist *l)
{
	l->i = START;
	l->j = SPACE;
	l->times = 0;
	ft_putstr_fd(tgetstr("ho", NULL), l->fd);
	ft_putstr_fd(tgetstr("cd", NULL), l->fd);
	l->col_max = nbr_col(l);
	if (check_window_size(l) < 0)
	{
		draw_at_location(l->col / 2 - SPACE, l->row / 2, "window too small",
				l->fd);
		return (-1);
	}
	return (0);
}

void		draw(t_entlist *l)
{
	t_entry *tmp;

	tmp = l->head;
	if (init_draw(l) < 0)
		return ;
	draw_title(l);
	while (l->times < l->ac)
	{
		if (l->i == l->row + SPACE - START)
		{
			l->i = START;
			l->j += l->max_len + SPACE;
		}
		if (tmp->us)
			ft_putstr_fd(tgetstr("us", NULL), l->fd);
		if (tmp->hl)
			ft_putstr_fd(tgetstr("mr", NULL), l->fd);
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), l->j, l->i), l->fd);
		print_entry_color(l, tmp);
		ft_putstr_fd(tgetstr("me", NULL), l->fd);
		tmp = tmp->next;
		l->i++;
		l->times++;
	}
	draw_help(l);
}

void		print_selected(t_entlist *l)
{
	t_entry		*tmp;
	static int	i = 0;
	int			j;

	j = 0;
	tmp = l->head;
	if (l->head != NULL)
	{
		while (j < l->ac)
		{
			if (tmp->hl)
			{
				if (i++ != 0)
					ft_putchar(' ');
				ft_putstr(tmp->line);
			}
			tmp = tmp->next;
			j++;
		}
		if (i != 0)
			ft_putchar('\n');
	}
}

void		check_args(int ac)
{
	if (!(ac > 1))
	{
		ft_putendl_fd("usage: ./ft_select args[...]", 2);
		exit(EXIT_FAILURE);
	}
}
