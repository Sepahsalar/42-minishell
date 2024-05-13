/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:23:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/13 17:38:38 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_dollar(t_cmd *cmd, char *str)
{
	t_env	*env;
	char	*new_str;
	char	*find;
	char	*expanded;
	int		len_var;
	int		len1;
	char	*part2;
	char	*variable;

	env = cmd->env;
	find = ft_strchr(str, '$');
	len1 = find - str;
	if (find[len1 + 1])
		find++;
	len_var = 0;
	while (find[len_var + 1] && find[len_var + 1] != ' ')
		len_var++;
	len_var++;
	variable = malloc(len_var + 1);
	if (!variable)
		return (NULL);
	ft_memcpy(variable, find, len_var);
	variable[len_var] = '\0';
	part2 = find + len_var;
	while (env && ((int)ft_strlen(env->key) != len_var
			|| ft_strncmp((env->key), variable, len_var)))
		env = env->next;
	if (env)
		expanded = ft_strdup(env->value);
	else
		expanded = ft_strdup("");
	if (!expanded)
	{
		free(variable);
		return (NULL);
	}
	new_str = malloc(len1 + ft_strlen(expanded) + ft_strlen(part2) + 1);
	if (!new_str)
	{
		free(variable);
		free(expanded);
		return (NULL);
	}
	new_str[len1 + ft_strlen(expanded) + ft_strlen(part2)] = '\0';
	ft_memcpy(new_str, str, len1);
	ft_memcpy(new_str + len1, expanded, ft_strlen(expanded));
	ft_memcpy(new_str + len1 + ft_strlen(expanded), part2, ft_strlen(part2));
	free(variable);
	free(expanded);
	return (new_str);
}

int	expand_all_dollar(t_cmd *start)
{
	t_cmd	*temp_cmd;
	char	**args;
	int		index;
	char	*temp;

	temp_cmd = start;
	while (temp_cmd)
	{
		index = 0;
		args = temp_cmd->args;
		while (args[index])
		{
			if (ft_strchr(args[index], '$'))
			{
				temp = args[index];
				args[index] = expand_dollar(temp_cmd, args[index]);
				free(temp);
				if (!args[index])
					return (1);
			}
			index++;
		}
		temp_cmd = temp_cmd->next;
	}
	return (0);
}
