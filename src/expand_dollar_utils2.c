/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:13:23 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/19 11:32:46 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	it_is_var(char *find, int len_var)
{
	if (find[len_var] && find[len_var] != ' '
		&& find[len_var] != '\"' && find[len_var] != '\''
		&& find[len_var] != '?' && find[len_var] != '='
		&& find[len_var] != '$')
		return (1);
	return (0);
}

static int	count_len_var(char *find)
{
	int	len_var;

	len_var = 0;
	while (it_is_var(find, len_var))
		len_var++;
	if (find[0] == '?' && len_var == 0)
		len_var = 1;
	return (len_var);
}

char	*find_var(char *find)
{
	char	*variable;
	int		len_var;

	len_var = count_len_var(find);
	variable = malloc(len_var + 1);
	if (!variable)
		return (NULL);
	ft_memcpy(variable, find, len_var);
	variable[len_var] = '\0';
	return (variable);
}

char	*find_expanded(t_cmd *cmd, char *variable)
{
	char	*expanded;

	if (same(variable, "?"))
		expanded = ft_strdup(cmd->original_env->value);
	else
	{
		expanded = ft_strdup(value_finder(cmd->env, variable));
		if (!expanded)
			expanded = ft_strdup("");
		if (!expanded)
		{
			free(variable);
			master_clean(NULL, cmd, EXIT_FAILURE);
		}
	}
	if (!expanded)
	{
		free(variable);
		master_clean(NULL, cmd, EXIT_FAILURE);
	}
	return (expanded);
}

char	*str_after_expansion(char *str, char *find,
	char *variable, char *expanded)
{
	char	*new_str;
	char	*part2;
	int		len1;

	len1 = find - str -1;
	part2 = find + ft_strlen(variable);
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
	ft_memcpy(new_str + len1
		+ ft_strlen(expanded), part2, ft_strlen(part2));
	return (new_str);
}
