/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 19:34:08 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/02 19:37:05 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cd.h"

t_dict	*envcpy(char **env)
{
	t_dict		*envdict;
	int			start;
	t_keyval	kv;
	int			i;

	envdict = dict_create();
	if (!envdict)
		return (NULL);
	i = 0;
	while (env[i])
	{
		start = ft_strlenchr(env[i], '=');
		kv.key = ft_strndup(env[i], start);
		kv.value = ft_strdup(env[i] + start + 1);
		dict_insert(envdict, kv.key, kv.value);
		i++;
		free(kv.key);
		free(kv.value);
	}
	return (envdict);
}

int		ft_unsetenv(const char *key, t_dict *env)
{
	if (!key || ft_strchr(key, '=') || key[0] == '\0')
		return (-1);
	dict_delete(env, key);
	return (0);
}

int		ft_setenv(const char *key, const char *value, t_dict *env, int overw)
{
	if (!is_alphanumeric(key))
	{
		ft_putendl_fd("setenv: name must contains alphanumeric characters", 2);
		return (-1);
	}
	if (!key || key[0] == '\0' || (overw != 0 && overw != 1))
		return (-1);
	if (overw)
	{
		dict_delete(env, key);
		dict_insert(env, key, value);
	}
	else if (!dict_search(env, key))
		dict_insert(env, key, value);
	return (0);
}

void	ft_putenv(t_dict *env)
{
	int		i;
	t_elt	*e;

	i = 0;
	while (i < env->size)
	{
		e = env->table[i];
		while (e)
		{
			ft_putstr(e->key);
			ft_putchar('=');
			ft_putendl(e->value);
			e = e->next;
		}
		i++;
	}
}
