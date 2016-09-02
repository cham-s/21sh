/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 13:59:25 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/28 12:28:02 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include "21sh.h"
#include "dict.h"
#include "get_next_line.h"

static int		is_special_key(unsigned int key)
{
	if (key == K_UP || key == K_DOWN || key == K_LEFT || key == K_RIGHT ||
		key == K_ESC || key == K_ENT || key == K_DEL || key == K_BKSPC || key == K_TAB)
		return 1;
	return 0;
}

/* void	go_right(t_entlist *l) */
/* { */
/* 	int i; */
/*  */
/* 	i = 0; */
/* 	l->list->us = 0; */
/* 	while (i < l->row - 1) */
/* 	{ */
/* 		l->list = l->list->next; */
/* 		i++; */
/* 	} */
/* 	l->list->us = 1; */
/* } */
/*  */
/* void	go_right(t_entlist *l) */
/* { */
/* 	int i; */
/*  */
/* 	i = 0; */
/* 	l->list->us = 0; */
/* 	while (i < l->row - 1) */
/* 	{ */
/* 		l->list = l->list->next; */
/* 		i++; */
/* 	} */
/* 	l->list->us = 1; */
/* } */


// if potential leaks probably here
static int		getline2(char **line, int fd)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	int				is_running;
	t_line			l;

	is_running = 1;
	ret = BUFF_SIZE;
	init_line(&l);
	while (is_running && ret)
	{
		ft_bzero(buf, MAX_KEY_LENGTH);
		if ((ret = read(fd, buf, MAX_KEY_LENGTH)) < 0)
			return (-1);
		l.key = *(unsigned int *)buf;
		if (is_special_key(l.key))
		{
			// handle special key with termcap
			if (l.key == K_ENT)
				is_running = 0;
			else if (l.key == K_LEFT)
				ft_putstr(tgetstr("le", NULL));
			else if (l.key == K_RIGHT)
				ft_putstr(tgetstr("nd", NULL));
		}
		else
		{
			buf[ret] = '\0';
			ft_putstr(buf);
			l.buffer = ft_strjoinfree(l.buffer, buf);
		}
	}
	ft_putendl("");
	*line = ft_strdup(l.buffer);
	l.tmp = l.buffer;
	ft_strdel(&l.tmp);
	if (ret == 0 && *line[0] == '\0')
		return (0);
	return (1);
}

int				get_next_line(int const fd, char **line, t_dict *env)
{
	int				res;
	struct termios old_term;

	if (fd < 0 || !line)
		return (-1);
	else
	{
		init_term_data(fd);
		init_raw_mode(&old_term);
		res = getline2(line, fd);
		reset_default_mode(&old_term);
		return (res);
	}
}
