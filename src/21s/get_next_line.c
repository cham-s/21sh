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
#include "get_next_line.h"

static int		is_special_key(unsigned int key)
{
	if (key == K_UP || key == K_DOWN || key == K_LEFT || key == K_RIGHT ||
		key == K_ESC || key == K_ENT || key == K_DEL || key == K_BKSPC || key == K_TAB)
		return 1;
	return 0;
}

static int		getline2(char *buffer, char **line, int fd)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	unsigned int	key;
	int				is_running;
	struct termios old_term;

	init_term_data(fd);
	init_raw_mode(&old_term);
	is_running = 1;
	ret = BUFF_SIZE;
	while (is_running && ret)
	{
		ft_bzero(buf, MAX_KEY_LENGTH);
		if ((ret = read(fd, buf, MAX_KEY_LENGTH)) < 0)
			return (-1);
		key = *(unsigned int *)buf;
		if (is_special_key(key))
		{
			if (key == K_ENT)
				is_running = 0;
			ft_putnbr(key);
			ft_putendl("");
		}
		else
		{
			buf[ret] = '\0';
			ft_putstr(buf);
			buffer = ft_strjoinfree(buffer, buf);
		}
	}
	ft_putendl(buffer);
	*line = ft_strdup(buffer);
	tmp = buffer;
	buffer = ft_strdup(buffer);
	ft_strdel(&tmp);
	reset_default_mode(&old_term);
	if (ret == 0 && *line[0] == '\0')
		return (0);
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	static char		*buf = NULL;
	int				res;

	if (fd < 0 || !line)
		return (-1);
	else
	{
		buf = ft_strdup("");
		res = getline2(buf, line, fd);
		return (res);
	}
}
