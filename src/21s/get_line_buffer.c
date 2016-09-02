#include "21sh.h"

static int		is_special_key(unsigned int key)
{
	if (key == K_UP || key == K_DOWN || key == K_LEFT || key == K_RIGHT ||
		key == K_ESC || key == K_ENT || key == K_DEL || key == K_BKSPC || key == K_TAB)
		return 1;
	return 0;
}

// if potential leaks probably here
static int		getline2(char **line, int fd, t_dict *env)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	int				is_running;
	t_line			l;

	is_running = 1;
	ret = BUFF_SIZE;
	init_line(&l, env);
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
			else if (l.key == K_LEFT && l.end > l.start)
			{
				--l.end;
				--l.position;
				ft_putstr(tgetstr("le", NULL));
			}
			else if (l.key == K_RIGHT)
			{
				++l.end;
				++l.position;
				ft_putstr(tgetstr("nd", NULL));
			}
		}
		else
		{
			buf[ret] = '\0';
			ft_putstr(buf);
			l.buffer = ft_strjoinfree(l.buffer, buf);
			++l.size;
			++l.position;
			++l.end;
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

int				get_line_buffer(int const fd, char **line, t_dict *env)
{
	int				res;
	struct termios old_term;

	if (fd < 0 || !line)
		return (-1);
	else
	{
		init_term_data(fd);
		init_raw_mode(&old_term);
		res = getline2(line, fd, env);
		reset_default_mode(&old_term);
		return (res);
	}
}
