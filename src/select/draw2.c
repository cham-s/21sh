/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 17:19:09 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/01 16:01:23 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	put_color(t_entlist *l, t_entry *e, char *color)
{
	ft_putstr_fd(color, l->fd);
	ft_putstr_fd(e->line, l->fd);
	ft_putstr_fd("\e[0m", l->fd);
}

void		print_entry_color(t_entlist *l, t_entry *e)
{
	struct stat	file;

	if (stat(e->line, &file) < 0)
	{
		e->t = R;
		ft_putstr_fd(e->line, l->fd);
	}
	else
	{
		if (file.st_mode & S_IXUSR && !S_ISDIR(file.st_mode))
		{
			e->t = X;
			put_color(l, e, "\e[31m");
		}
		else if (S_ISDIR(file.st_mode))
		{
			e->t = D;
			put_color(l, e, "\e[34m");
		}
		else
		{
			e->t = R;
			ft_putstr_fd(e->line, l->fd);
		}
	}
}

void		set_draw(t_entlist *l)
{
	if (l->head)
		l->head->us = 1;
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
