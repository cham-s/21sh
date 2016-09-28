#include "21sh.h"

static int		is_special_key(unsigned int key)
{
	if (key == K_UP || key == K_DOWN || key == K_LEFT || key == K_RIGHT ||
		key == K_ESC || key == K_ENT || key == K_DEL || key == K_BKSPC ||
		key == K_TAB || key == K_ALT_L || key == K_ALT_R || key == K_HOME ||
	   	key == K_END || key == K_ALT_DOWN || key == K_ALT_UP)
		return 1;
	return 0;
}

// if potential leaks probably here
static int		getline2(char **line, int fd, t_dict *env, t_hcontrol *c)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	int				is_running;
	t_line			*l;

	is_running = 1;
	ret = BUFF_SIZE;
	l = ret_line();
	init_line(l, env);
	while (is_running && ret)
	{
		ft_bzero(buf, MAX_KEY_LENGTH);
		if ((ret = read(fd, buf, MAX_KEY_LENGTH)) < 0)
			return (-1);
		l->key = *(unsigned int *)buf;
		if (is_special_key(l->key))
		{
			// handle special key with termcap
			if (l->key == K_ENT)
				is_running = 0;
			else if (l->key == K_UP)
			{
				if (c->list)
				{
					// free here
					l->end = ft_strlen(l->buffer);
					while (l->end--)
					{
						ft_putstr(tgetstr("le", NULL));
						ft_putstr(tgetstr("dc", NULL));
					}
					l->buffer = ft_strdup(c->list->line);
					if (c->list->next)
						c->list = c->list->next;
					ft_putstr(l->buffer);
					l->position = ft_strlen(l->buffer);
				}
			}
			else if (l->key == K_DOWN)
			{
				if (c->list)
				{
					// free here
					l->end = ft_strlen(l->buffer);
					while (l->end--)
					{
						ft_putstr(tgetstr("le", NULL));
						ft_putstr(tgetstr("dc", NULL));
					}
					l->buffer = ft_strdup(c->list->line);
					if (c->list->prev)
						c->list = c->list->prev;
					ft_putstr(l->buffer);
					l->position = ft_strlen(l->buffer);
				}
			}
			else if (l->key == K_LEFT && l->position > 0)
			{
				--l->end;
				--l->position;
				ft_putstr(tgetstr("le", NULL));
			}
			else if (l->key == K_ALT_L && l->position > 0)
			{
				ft_putstr(tgetstr("le", NULL));
				--l->position;
				while (l->buffer[l->position] == ' ' && l->position > 0)
				{
					ft_putstr(tgetstr("le", NULL));
					--l->position;
				}
				while(l->buffer[l->position] != ' ' && l->position > 0)
				{
					ft_putstr(tgetstr("le", NULL));
					--l->position;
				}
				if (l->position > 1)
				{
					ft_putstr(tgetstr("nd", NULL));
					++l->position;
				}
			}
			else if (l->key == K_ALT_R && l->buffer[l->position])
			{
				if (l->buffer[l->position] == ' ')
				{
					while (l->buffer[l->position] == ' ' && l->buffer[l->position])
					{
						++l->position;
						ft_putstr(tgetstr("nd", NULL));
					}
				}
				else
				{
					while (l->buffer[l->position] != ' ' && l->buffer[l->position] != '\0')
					{
						++l->position;
						ft_putstr(tgetstr("nd", NULL));
					}
					if (l->buffer[l->position] == ' ')
					{
						while (l->buffer[l->position] == ' ' && l->buffer[l->position])
						{
							++l->position;
							ft_putstr(tgetstr("nd", NULL));
						}
					}
				}
			}
			else if (l->key == K_BKSPC && l->position > 0)
			{
				// remove end?
				char *tmpos = l->buffer + (l->position);
				--l->end;
				--l->position;
				ft_putstr(tgetstr("le", NULL));
				ft_putstr(tgetstr("dc", NULL));
				if (ft_strlen(l->buffer) == l->position + 1)
				{
					char *tmp = l->buffer;
					l->buffer = ft_strsub(l->buffer, 0, l->position);
					free(tmp);
				}
				else
				{
					char *end = ft_strdup(tmpos);
					char *start  = ft_strsub(l->buffer, 0, l->position);
					l->buffer = ft_strjoinfree(start, end);
				}
			}
			else if (l->key == K_RIGHT && l->buffer[l->position])
			{
				++l->end;
				++l->position;
				ft_putstr(tgetstr("nd", NULL));
			}
			else if (l->key == K_HOME)
			{
				while (l->position > 0)
				{
					--l->position;
					ft_putstr(tgetstr("le", NULL));
				}
			}
			else if (l->key == K_END)
			{
				while (l->buffer[l->position])
				{
					++l->position;
					ft_putstr(tgetstr("nd", NULL));
				}
			}
		}
		else
		{
			buf[ret] = '\0';
			if (l->buffer[l->position])
			{
				size_t i = l->position;
				/* size_t tmp = l->position; */
				while (i--)
				{
					ft_putstr(tgetstr("le", NULL));
					ft_putstr(tgetstr("dc", NULL));
				}
				char *end = ft_strdup(l->buffer + l->position);
				char *start = ft_strsub(l->buffer, 0, l->position);
				char *start_new = ft_strjoinfree(start, buf);
				l->buffer = ft_strjoinfree(start_new, end);
				l->end = ft_strlen(l->buffer);
				ft_putstr(l->buffer);
				i = ft_strlen(l->buffer) - (l->position + 1);
				++l->position;
				while (i--)
					ft_putstr(tgetstr("le", NULL));
			}
			else
			{
				l->buffer = ft_strjoinfree(l->buffer, buf);
				++l->size;
				++l->position;
				++l->end;
				ft_putstr(buf);
			}
		}
		// ===> line level
		/* int buf_len = (int)ft_strlen(l->buffer); */
		/* // int width = l->term_width = l->term_width * l->level_count; */
		/* if (l->level_count == 1) */
		/* 	buf_len += 6; */
		/* if (buf_len == l->term_width * l->level_count) */
		/* { */
		/* 	++l->level_count; */
		/* 	ft_putnbr(l->level_count); */
		/* } */
	}
	ft_putendl("");
	*line = ft_strdup(l->buffer);
	add_history(c, new_history(l->buffer));
	// reset history
	c->list = c->head;
	l->tmp = l->buffer;
	ft_strdel(&l->tmp);
	if (ret == 0 && *line[0] == '\0')
		return (0);
	return (1);
}

int				get_line_buffer(int const fd, char **line, t_dict *env, t_hcontrol *c)
{
	int				res;

	if (fd < 0 || !line)
		return (-1);
	else
	{
		init_term_data(fd);
		init_raw_mode(&c->old_term);
		res = getline2(line, fd, env, c);
		reset_default_mode(&c->old_term);
		return (res);
	}
}
