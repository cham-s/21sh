#include "21sh.h"

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
	ft_putnbr(l->level_count);
	if ((int)l->position + PROMPT_SIZE == l->term_width + 1)
		ft_putstr(tgetstr("do", NULL));
	else
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
	if ((int)l->position + PROMPT_SIZE == l->term_width + 1)
	{
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
	}
	else
	{
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
	}
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
	update_line_level(l, TRUE);
}