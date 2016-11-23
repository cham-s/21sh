#include "21sh.h"

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

void			foreward_history(t_line *l, t_hcontrol *c)
{
	if (c->list->prev)
	{
		l->end = ft_strlen(l->buffer);
		while (l->end--)
		{
			ft_putstr(tgetstr("le", NULL));
			ft_putstr(tgetstr("dc", NULL));
		}
		c->list = c->list->prev;
		l->buffer = ft_strdup(c->list->line);
		ft_putstr(l->buffer);
		l->position = ft_strlen(l->buffer);
	}
}

void			backward_history(t_line *l, t_hcontrol *c)
{
	if (c->passage == 0)
	{
		l->end = ft_strlen(l->buffer);
		while (l->end--)
		{
			ft_putstr(tgetstr("le", NULL));
			ft_putstr(tgetstr("dc", NULL));
		}
		++c->passage;
		l->buffer = ft_strdup(c->list->line);
		ft_putstr(l->buffer);
		l->position = ft_strlen(l->buffer);
	}
	else if (c->list->next)
	{
		l->end = ft_strlen(l->buffer);
		while (l->end--)
		{
			ft_putstr(tgetstr("le", NULL));
			ft_putstr(tgetstr("dc", NULL));
		}
		c->list = c->list->next;
		l->buffer = ft_strdup(c->list->line);
		ft_putstr(l->buffer);
		l->position = ft_strlen(l->buffer);
	}
}
