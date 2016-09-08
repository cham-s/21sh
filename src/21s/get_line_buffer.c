#include "21sh.h"

static int		is_special_key(unsigned int key)
{
	if (key == K_UP || key == K_DOWN || key == K_LEFT || key == K_RIGHT ||
		key == K_ESC || key == K_ENT || key == K_DEL || key == K_BKSPC || key == K_TAB)
		return 1;
	return 0;
}

// if potential leaks probably here
static int		getline2(char **line, int fd, t_dict *env, t_hcontrol *c)
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
			else if (l.key == K_UP)
			{
				if (c->list)
				{
					// free here
					l.end = ft_strlen(l.buffer);
					while (l.end--)
					{
						ft_putstr(tgetstr("le", NULL));
						ft_putstr(tgetstr("dc", NULL));
					}
					add_history(c, new_history(l.buffer));
					l.buffer = ft_strdup(c->list->line);
					c->list = c->list->next;
					ft_putstr(l.buffer);
					l.position = ft_strlen(l.buffer);
				}
			}
			else if (l.key == K_LEFT && l.position > 0)
			{
				--l.end;
				--l.position;
				ft_putstr(tgetstr("le", NULL));
			}
			else if (l.key == K_BKSPC && l.position > 0)
			{
				char *tmpos = l.buffer + (l.position);
				--l.end;
				--l.position;
				ft_putstr(tgetstr("le", NULL));
				ft_putstr(tgetstr("dc", NULL));
				if (ft_strlen(l.buffer) == l.position + 1)
				{
					char *tmp = l.buffer;
					l.buffer = ft_strsub(l.buffer, 0, l.position);
					free(tmp);
				}
				else
				{
					char *end = ft_strdup(tmpos);
					char *start  = ft_strsub(l.buffer, 0, l.position);
					l.buffer = ft_strjoinfree(start, end);
				}
			}
			else if (l.key == K_RIGHT && l.buffer[l.position])
			{
				++l.end;
				++l.position;
				ft_putstr(tgetstr("nd", NULL));
			}
		}
		else
		{
			buf[ret] = '\0';
			if (l.buffer[l.position])
			{
				size_t i = l.position;
				/* size_t tmp = l.position; */
				while (i--)
				{
					ft_putstr(tgetstr("le", NULL));
					ft_putstr(tgetstr("dc", NULL));
				}
				char *end = ft_strdup(l.buffer + l.position);
				char *start = ft_strsub(l.buffer, 0, l.position);
				char *start_new = ft_strjoinfree(start, buf);
				l.buffer = ft_strjoinfree(start_new, end);
				l.end = ft_strlen(l.buffer);
				ft_putstr(l.buffer);
				i = ft_strlen(l.buffer) - (l.position + 1);
				++l.position;
				while (i--)
					ft_putstr(tgetstr("le", NULL));
			}
			else
			{
				l.buffer = ft_strjoinfree(l.buffer, buf);
				++l.size;
				++l.position;
				++l.end;
				ft_putstr(buf);
			}
		}
	}
	ft_putendl("");
	*line = ft_strdup(l.buffer);
	add_history(c, new_history(l.buffer));
	l.tmp = l.buffer;
	ft_strdel(&l.tmp);
	if (ret == 0 && *line[0] == '\0')
		return (0);
	return (1);
}

int				get_line_buffer(int const fd, char **line, t_dict *env, t_hcontrol *c)
{
	int				res;
	struct termios old_term;

	if (fd < 0 || !line)
		return (-1);
	else
	{
		init_term_data(fd);
		init_raw_mode(&old_term);
		res = getline2(line, fd, env, c);
		reset_default_mode(&old_term);
		return (res);
	}
}
