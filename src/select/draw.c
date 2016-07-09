/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:33:43 by cattouma          #+#    #+#             */
/*   Updated: 2016/05/30 19:02:03 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	draw_at_location(int x , int y, char *str, int fd)
{
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), x, y), fd);
	ft_putstr_fd(str, fd);
}

void		draw_title(t_entlist *l)
{
	int i;
	int start;

	i = 0;
	start = l->width / 2 - ((int)ft_strlen("FT SELECT") / 2);
	ft_putstr_fd(tgetstr("ho", NULL), l->fd);
	ft_putstr_fd("\e[104m", l->fd);
	while (i < start)
	{
		ft_putchar_fd(' ', l->fd);
		i += 1;
	}
	ft_putstr_fd("FT_SELECT", l->fd);
	i += (int)ft_strlen("FT_SELECT");
	while (i < l->width)
	{
		ft_putchar_fd(' ', l->fd);
		i += 1;
	}
	ft_putstr_fd("\e[0m", l->fd);
}

void		draw_help(t_entlist *l)
{
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, l->height - 4), l->fd);
	ft_putstr_fd("\e[96mCommands:\e[0m\n\t\e[96mSPACE\e[0m select/unselect   ",
			l->fd);
	ft_putstr_fd("\e[96mX\e[0m exec file   \e[96mR\e[0m regular file\t",
			l->fd); 
	ft_putstr_fd("\e[96mD\e[0m directory   \e[96mA\e[0m all   ", l->fd); 
	ft_putstr_fd("\e[96mENTER\e[0m return selected   \e[96mESCAPE\e[0m Quit   ",
			l->fd);
	ft_putstr_fd("\e[96mBKSPC/DEL\e[0m delete   ", l->fd);
	ft_putstr_fd("\e[96mARROWS\e[0m move", l->fd);
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
