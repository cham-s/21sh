/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:33:04 by cattouma          #+#    #+#             */
/*   Updated: 2016/03/02 10:52:20 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

void	dict_insert(t_dict *d, const char *key, const char *value)
{
	t_elt			*e;
	unsigned long	h;

	if (!key || !value || !d)
		return ;
	e = (t_elt *)ft_memalloc(sizeof(t_elt));
	if (!e)
		return ;
	e->key = ft_strdup(key);
	e->value = ft_strdup(value);
	h = hash_function(key) % d->size;
	e->next = d->table[h];
	d->table[h] = e;
	d->n++;
	if (d->n >= d->size * MAX_LOAD_FACTOR)
		grow(d);
}

char	*dict_search(t_dict *d, const char *key)
{
	t_elt *e;

	e = d->table[hash_function(key) % d->size];
	while (e)
	{
		if (!ft_strcmp(e->key, key))
			return (e->value);
		e = e->next;
	}
	return (NULL);
}

void	dict_delete(t_dict *d, const char *key)
{
	t_elt	**prev;
	t_elt	*e;

	prev = &(d->table[hash_function(key) % d->size]);
	while (*prev)
	{
		if (!ft_strcmp((*prev)->key, key))
		{
			e = *prev;
			*prev = e->next;
			free(e->key);
			free(e->value);
			free(e);
			return ;
		}
		prev = &((*prev)->next);
	}
}
