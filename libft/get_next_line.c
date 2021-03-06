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
#include <sys/types.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>
#include "21sh.h"

# define MAX_KEY_LENGTH 5

# define K_UP		4283163
# define K_DOWN		4348699
# define K_LEFT		4479771
# define K_RIGHT	4414235
# define K_ESC		27
# define K_ENT		10
# define K_TAB		9
# define K_DEL		2117294875
# define K_BKSPC	127
# define K_SPACE	32

static t_file	*fpnodenew(int fd)
{
	t_file			*new;

	new = (t_file *)ft_memalloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buffer = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

static t_file	*fpintree(t_file **btree, int fd)
{
	t_file			*tmp;

	tmp = *btree;
	while (tmp)
	{
		if (fd == tmp->fd)
			return (tmp);
		if (fd > tmp->fd)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	return (NULL);
}

static void		addnode(t_file **btree, t_file *new)
{
	t_file			*tmptree;
	t_file			*tmpnode;

	tmptree = *btree;
	if (!*btree)
		*btree = new;
	else
	{
		while (tmptree)
		{
			tmpnode = tmptree;
			if (new->fd > tmptree->fd)
			{
				tmptree = tmptree->right;
				if (!tmptree)
					tmpnode->right = new;
			}
			else
			{
				tmptree = tmptree->left;
				if (!tmptree)
					tmpnode->left = new;
			}
		}
	}
}

static int		is_special_key(unsigned int key)
{
	if (key == K_UP || key == K_DOWN || key == K_LEFT || key == K_RIGHT ||
		key == K_ESC || key == K_ENT || key == K_DEL || key == K_BKSPC)
		return 1;
	return 0;
}

static int		getline2(t_file *fpnode, char **line, int fd)
{
	int				ret;
	int				len;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	unsigned int	key;
	int				is_running;
	struct termios old_term;

	init_term_data(fd);
	init_raw_mode(&old_term);
	is_running = 1;
	len = 0;
	ret = BUFF_SIZE;
	while (is_running && ret)
	{
		ft_bzero(buf, MAX_KEY_LENGTH);
		if ((ret = read(fd, buf, MAX_KEY_LENGTH)) < 0)
			return (-1);
		key = *(unsigned int *)buf;
			ft_putnbr(key);
			ft_putendl("");
		if (is_special_key(key))
		{
			ft_putnbr(key);
			ft_putendl("");
		}
		else
		{
			buf[1] = '\0';
			fpnode->buffer = ft_strjoinfree(fpnode->buffer, buf);
		}
	}
	*line = ft_strsub(fpnode->buffer, 0, 1);
	tmp = fpnode->buffer;
	fpnode->buffer = ft_strdup(fpnode->buffer + len);
	ft_strdel(&tmp);
	reset_default_mode(&l->old_term);
	if (ret == 0 && *line[0] == '\0')
		return (0);
	return (1);
}

/* static int		getline(t_file *fpnode, char **line, int fd) */
/* { */
/* 	int				ret; */
/* 	int				len; */
/* 	char			buf[BUFF_SIZE + 1]; */
/* 	char			*tmp; */
/*  */
/* 	len = 0; */
/* 	ret = BUFF_SIZE; */
/* 	while (!(ft_strchr(fpnode->buffer, '\n')) && ret) */
/* 	{ */
/* 		if ((ret = read(fd, buf, BUFF_SIZE)) < 0) */
/* 			return (ret); */
/* 		buf[ret] = '\0'; */
/* 		fpnode->buffer = ft_strjoinfree(fpnode->buffer, buf); */
/* 	} */
/* 	while (fpnode->buffer[len] && fpnode->buffer[len] != '\n') */
/* 		len++; */
/* 	*line = ft_strsub(fpnode->buffer, 0, len); */
/* 	if (fpnode->buffer[len] == '\n') */
/* 		len++; */
/* 	tmp = fpnode->buffer; */
/* 	fpnode->buffer = ft_strdup(fpnode->buffer + len); */
/* 	ft_strdel(&tmp); */
/* 	if (ret == 0 && *line[0] == '\0') */
/* 		return (0); */
/* 	return (1); */
/* } */

int				get_next_line(int const fd, char **line)
{
	static t_file	*btree = NULL;
	t_file			*fpnode;
	int				res;

	if (fd < 0 || !line)
		return (-1);
	else
	{
		if (!(fpnode = fpintree(&btree, fd)))
		{
			fpnode = fpnodenew(fd);
			addnode(&btree, fpnode);
		}
		if (!(fpnode->buffer))
		{
			fpnode->buffer = ft_strdup("");
		}
		res = getline2(fpnode, line, fd);
		return (res);
	}
}
