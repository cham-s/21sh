/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 17:19:09 by cattouma          #+#    #+#             */
/*   Updated: 2016/05/30 18:32:13 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_entry_color(t_entlist *l, t_entry *e)
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
			ft_putstr_fd("\e[31m", l->fd);
			ft_putstr_fd(e->line, l->fd);
			ft_putstr_fd("\e[0m", l->fd);
		}
		else if (S_ISDIR(file.st_mode))
		{
			e->t = D;
			ft_putstr_fd("\e[34m", l->fd);
			ft_putstr_fd(e->line, l->fd);
			ft_putstr_fd("\e[0m", l->fd);
		}
		else
		{
			e->t = R;
			ft_putstr_fd(e->line, l->fd);
		}
	}
}

void	set_draw(t_entlist *l)
{
	if (l->head)
		l->head->us = 1;
}
