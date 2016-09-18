/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:53:36 by cattouma          #+#    #+#             */
/*   Updated: 2016/09/18 13:21:22 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h" 

/* static void		sig_stp(t_entlist *l) */
/* { */
/* 	char	buff[2]; */
/*  */
/* 	buff[0] = 032; */
/* 	buff[1] = '\0'; */
/* 	if (isatty(1)) */
/* 	{ */
/* 		signal(SIGTSTP, SIG_DFL); */
/* 		ft_putstr_fd(tgetstr("ve", NULL), l->fd); */
/* 		ft_putstr_fd(tgetstr("te", NULL), l->fd); */
/* 		ioctl(0, TIOCSTI, buff); */
/* 		reset_default_mode(&l->old_term); */
/* 	} */
/* 	else */
/* 	{ */
/* 		ft_putendl_fd("Not a terminal device", 2); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* } */

/* static void		sig_cont(t_line *l) */
/* { */
/* 	ft_putstr(tgetstr("vi", NULL)); */
/* 	ft_putstr(tgetstr("ti", NULL)); */
/* 	signal(SIGTSTP, sig_handler); */
/* 	init_raw_mode(&l->old_term); */
/* 	draw(l); */
/* } */

void			sig_handler(int sig)
{
	t_line	*l;
	struct winsize	w;

	l = ret_line();
	if (sig == SIGWINCH)
	{
		if(ioctl(1, TIOCGWINSZ, &w) < 0)
		{
			ft_putendl_fd("Error using ioctl()", 2);
			exit(EXIT_FAILURE);
		}
		l->term_height = w.ws_row;
		l->term_width = w.ws_col;
	}
	else if (sig == SIGINT)
	{
		ft_putchar('\n');
		ft_putstr("21sh - Ctrl-c -> ");
	}
	/* else if (sig == SIGTSTP) */
	/* 	sig_stp(l); */
	/* else if (sig == SIGCONT) */
	/* 	sig_cont(l); */
	/* else */
	/* 	quit(l); */
}

void			signals(void)
{
	int i;

	i = 1;
	while (i < MAX_SIGNAL)
	{
		signal(i, sig_handler);
		i++;
	}
}
