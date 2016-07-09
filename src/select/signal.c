/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:53:36 by cattouma          #+#    #+#             */
/*   Updated: 2016/05/30 18:51:43 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ctrl_z(int sig, t_entlist *l)
{
	char	ctrl_z[2];

	ctrl_z[0] = 032;
	ctrl_z[1] = '\0';
	if (sig == SIGTSTP && isatty(1))
	{
		signal(SIGTSTP, SIG_DFL);
		ft_putstr_fd(tgetstr("ve", NULL), l->fd);
		ft_putstr_fd(tgetstr("te", NULL), l->fd);
		ioctl(0, TIOCSTI, ctrl_z);
		reset_default_mode(&l->old_term);
	}
	else if (sig == SIGCONT)
	{
		ft_putstr_fd(tgetstr("vi", NULL), l->fd);
		ft_putstr_fd(tgetstr("ti", NULL), l->fd);
		signal(SIGTSTP, sig_handler);
		init_raw_mode(&l->old_term);
		draw(l);
	}
}

void		sig_handler(int sig)
{
	t_entlist		*l;
	struct winsize	w;

	l = ret_entlist();
	if (sig == SIGWINCH)
	{
		ioctl(l->fd, TIOCGWINSZ, &w);
		l->height = w.ws_row;
		l->width = w.ws_col;
		l->row = l->height - START - PAD;
		l->col = l->width - SPACE * 2;
		draw(l);
	}
	else if (sig == SIGTSTP || sig == SIGCONT)
		ctrl_z(sig, l);
	else
		quit(l);
}

void		signals(void)
{
	int i;

	i = 1;
	while (i < MAX_SIGNAL)
	{
		signal(i, sig_handler);
		i++;
	}
}
