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

void			move_left(t_line *l)
{
	--l->end;
	--l->position;
	ft_putstr(tgetstr("le", NULL));
}

void			move_right(t_line *l)
{
	++l->end;
	++l->position;
	ft_putstr(tgetstr("nd", NULL));
}

void			move_word_left(t_line *l)
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

void			move_word_right(t_line *l)
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

void			erase_back(t_line *l)
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

void			go_home_of_line(t_line *l)
{
	while (l->position > 0)
	{
		--l->position;
		ft_putstr(tgetstr("le", NULL));
	}
}

void			go_end_of_line(t_line *l)
{
	while (l->buffer[l->position])
	{
		++l->position;
		ft_putstr(tgetstr("nd", NULL));
	}
}

/* void			backward_history(t_line *l, t_hcontrol *c) */
/* { */
/* 	if (c->list) */
/* 	{ */
/* 		// free here */
/* 		l->end = ft_strlen(l->buffer); */
/* 		while (l->end--) */
/* 		{ */
/* 			ft_putstr(tgetstr("le", NULL)); */
/* 			ft_putstr(tgetstr("dc", NULL)); */
/* 		} */
/* 		l->buffer = ft_strdup(c->list->line); */
/* 		if (c->list->next) */
/* 			c->list = c->list->next; */
/* 		ft_putstr(l->buffer); */
/* 		l->position = ft_strlen(l->buffer); */
/* 	} */
/* } */

void			foreward_history(t_line *l, t_hcontrol *c)
{
	t_history	*tmp;

	(void)l;
	tmp = NULL;
	if (c->list)
	{
		tmp = c->list;
		ft_putendl(c->list->line);
		c->list = c->list->prev;
	}
	if (c->list == NULL)
		c->list = tmp;
}
void			backward_history(t_line *l, t_hcontrol *c)
{
	t_history	*tmp;

	(void)l;
	tmp = NULL;
	if (c->list)
	{
		tmp = c->list;
		ft_putendl(c->list->line);
		c->list = c->list->next;
	}
	if (c->list == NULL)
		c->list = tmp;
}

/* void			foreward_history(t_line *l, t_hcontrol *c) */
/* { */
/* 	if (c->list) */
/* 	{ */
/* 		// free here */
/* 		l->end = ft_strlen(l->buffer); */
/* 		while (l->end--) */
/* 		{ */
/* 			ft_putstr(tgetstr("le", NULL)); */
/* 			ft_putstr(tgetstr("dc", NULL)); */
/* 		} */
/* 		l->buffer = ft_strdup(c->list->line); */
/* 		if (c->list->prev) */
/* 			c->list = c->list->prev; */
/* 		ft_putstr(l->buffer); */
/* 		l->position = ft_strlen(l->buffer); */
/* 	} */
/* } */

void			edit_buffer(t_line *l, char	buf[BUFF_SIZE + 1])
{
	size_t i = l->position;
	char *end;
	char *start;
	char *start_new;
	/* size_t tmp = l->position; */
	while (i--)
	{
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
	}
	end = ft_strdup(l->buffer + l->position);
	start = ft_strsub(l->buffer, 0, l->position);
	start_new = ft_strjoinfree(start, buf);
	l->buffer = ft_strjoinfree(start_new, end);
	l->end = ft_strlen(l->buffer);
	ft_putstr(l->buffer);
	i = ft_strlen(l->buffer) - (l->position + 1);
	++l->position;
	while (i--)
		ft_putstr(tgetstr("le", NULL));
}

void			display_buffer(t_line *l, char	buf[BUFF_SIZE + 1])
{
	l->buffer = ft_strjoinfree(l->buffer, buf);
	++l->size;
	++l->position;
	++l->end;
	ft_putstr(buf);
}

void			handle_special_keys(t_line *l, t_hcontrol *c)
{
	if (l->key == K_UP)
		backward_history(l, c);
	else if (l->key == K_DOWN)
		foreward_history(l, c);
	else if (l->key == K_LEFT && l->position > 0)
		move_left(l);
	else if (l->key == K_RIGHT && l->buffer[l->position])
		move_right(l);
	else if (l->key == K_ALT_L && l->position > 0)
		move_word_left(l);
	else if (l->key == K_ALT_R && l->buffer[l->position])
		move_word_right(l);
	else if (l->key == K_BKSPC && l->position > 0)
		erase_back(l);
	else if (l->key == K_HOME)
		go_home_of_line(l);
	else if (l->key == K_END)
		go_end_of_line(l);
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
			else
				handle_special_keys(l, c);
		}
		else
		{
			buf[ret] = '\0';
			if (l->buffer[l->position])
				edit_buffer(l, buf);
			else
				display_buffer(l, buf);
		}
	}
	ft_putendl("");
	*line = ft_strdup(l->buffer);
	if (l->buffer[0])
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
