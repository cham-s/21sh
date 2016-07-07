/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:32:54 by cattouma          #+#    #+#             */
/*   Updated: 2016/03/02 12:37:34 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

t_dict			*init_dict(int size)
{
	t_dict	*d;
	int		i;

	i = 0;
	d = (t_dict *)ft_memalloc(sizeof(t_dict));
	if (!d)
		return (NULL);
	d->size = size;
	d->n = 0;
	d->table = (t_elt **)ft_memalloc(sizeof(t_elt *) * d->size);
	while (i < size)
	{
		d->table[i] = NULL;
		i++;
	}
	return (d);
}

t_dict			*dict_create(void)
{
	return (init_dict(INIT_SIZE));
}

void			dict_destroy(t_dict *d)
{
	int		i;
	t_elt	*e;
	t_elt	*tmp;

	i = 0;
	while (i < d->size)
	{
		e = d->table[i];
		while (e)
		{
			tmp = e;
			e = e->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		i++;
	}
	free(d->table);
	free(d);
}

unsigned long	hash_function(const char *s)
{
	unsigned const char	*ts;
	unsigned long		h;

	printf("%s\n", s);
	exit(3);
	h = 0;
	ts = (unsigned const char *)s;
	while (*ts)
	{
		h = h * MULTIPLAYER + *ts;
		ts++;
	}
	return (h);
}

void			grow(t_dict *d)
{
	t_dict	*d2;
	t_dict	swap;
	int		i;
	t_elt	*e;

	i = 0;
	d2 = init_dict(d->size * GROWTH_FACTOR);
	while (i < d->size)
	{
		e = d->table[i];
		while (e)
		{
			dict_insert(d2, e->key, e->value);
			e = e->next;
		}
		i++;
	}
	swap = *d;
	*d = *d2;
	*d2 = swap;
	dict_destroy(d2);
}
