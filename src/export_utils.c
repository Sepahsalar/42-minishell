/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:43:06 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 11:15:35 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*custom_export(t_env *env, char *key, char *value)
{
	t_env	*temp;
	char	*temp_key;
	char	*temp_value;

	temp = env;
	while (temp)
	{
		if (same(temp->key, key))
			break ;
		temp = temp->next;
	}
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(value);
		if (!temp->value)
			clean_all(env, NULL, NULL, NULL);
	}
	else
	{
		temp_key = ft_strdup(key);
		temp_value = ft_strdup(value);
		if (!temp_key || !temp_value)
			clean_all(env, NULL, temp_key, temp_value);
		add_node_front(&env, temp_key, temp_value);
		if (!env)
			clean_all(env, NULL, temp_key, temp_value);
	}
	return (env);
}

int	is_higher(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 < *s2)
			return (*s2 - *s1);
		if (*s1 > *s2)
			return (*s2 - *s1);
		else
		{
			s1++;
			s2++;
		}
	}
	return (*s2 - *s1);
}

int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

t_env	*sort_env(t_env *env)
{
	int		index;
	t_env	*temp_index;
	t_env	*temp;

	index = 1;
	while (index <= env_count(env))
	{
		temp = env;
		while (temp && temp->index)
			temp = temp->next;
		temp_index = temp;
		temp = env;
		while (temp)
		{
			if (temp && temp_index && is_higher(temp_index->key, temp->key) < 0
				&& !temp->index)
				temp_index = temp;
			temp = temp->next;
		}
		if (temp_index)
			temp_index->index = index;
		index++;
	}
	return (env);
}

t_env	*handle_oldpwd(t_env *env)
{
	t_env	*temp;
	int		has_oldpwd;

	has_oldpwd = 0;
	temp = env;
	while (temp)
	{
		if (same(temp->key, "OLDPWD"))
			has_oldpwd = 1;
		temp = temp->next;
	}
	if (!has_oldpwd)
		add_node_front(&env, ft_strdup("OLDPWD"), NULL);
	return (env);
}
