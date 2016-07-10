/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:32:33 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/10 17:55:54 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_dict	*envcpy(char **env)
{
	t_dict	*envdict;
	int		start;
	char	*key;
	char	*value;
	int		i;

	envdict = dict_create();
	if (!envdict)
		return (NULL);
	i = 0;
	while (env[i])
	{
		start = ft_strlenchr(env[i], '=');
		key = ft_strndup(env[i], start);
		value = ft_strdup(env[i] + start + 1);
		dict_insert(envdict, key, value);
		i++;
		free(key);
		free(value);
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

void	print_env(char **env)
{
	int	i;

	i = 0;

	if (env == NULL)
		return ;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}
