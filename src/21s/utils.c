/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 11:08:58 by cattouma          #+#    #+#             */
/*   Updated: 2016/09/18 13:12:53 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	*join_with_chr(char *var, char *value, char c)
{
	char	*new;
	size_t	varlen;
	size_t	valuelen;

	varlen = ft_strlen(var);
	valuelen = ft_strlen(value);
	new = ft_strnew(varlen + valuelen + 1);
	if (!new)
		return (NULL);
	ft_strncpy(new, var, varlen);
	new[varlen] = c;
	ft_strncpy(new + varlen + 1, value, valuelen);
	return (new);
}

char	**dict_to_tab(t_dict *env)
{
	char	**new;
	t_elt	*e;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char **)ft_memalloc(env->n + 1);
	if (!new)
		return (NULL);
	while (i < env->size)
	{
		e = env->table[i];
		while (e)
		{
			new[j] = join_with_chr(e->key, e->value, '=');
			e = e->next;
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

void	ft_delsplit(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	clean_malloc(char *line, char **big_line, char **env)
{
	free(line);
	ft_delsplit(big_line);
	ft_delsplit(env);
}
