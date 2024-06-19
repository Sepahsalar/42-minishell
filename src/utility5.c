/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:06:03 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 11:18:46 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fill_address_access(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp)
	{
		if (find_cmd_address(temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_env	*cpy_env(t_env *env)
{
	t_env	*new;
	t_env	*old;
	t_env	*start;

	start = NULL;
	while (env)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			clean_all(start, NULL, NULL, NULL);
		ft_memset(new, 0, sizeof(t_env));
		new->key = ft_strdup(env->key);
		new->value = ft_strdup(env->value);
		if (!new->key || !new->value)
			clean_all(start, NULL, new->key, new->value);
		if (!start)
			start = new;
		else
			old->next = new;
		old = new;
		env = env->next;
	}
	return (start);
}

char	*value_finder(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (same(temp->key, key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	add_node_front(t_env **env, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		*env = NULL;
		return ;
	}
	new->key = key;
	new->value = value;
	new->next = *env;
	*env = new;
}

int	clean_str(char *s1)
{
	if (s1)
        free(s1);
    return (1);
}
