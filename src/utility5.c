/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:06:03 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 12:03:48 by asohrabi         ###   ########.fr       */
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

int	same(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) && !ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}
