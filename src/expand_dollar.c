/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:23:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/17 18:52:21 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_one_dollar(t_cmd *cmd, char *str, char *find)
{
	char	*new_str;
	char	*expanded;
	char	*variable;

	find++;
	variable = find_var(find);
	expanded = find_expanded(cmd, variable);
	new_str = str_after_expansion(str, find, variable, expanded);
	free(variable);
	free(expanded);
	return (new_str);
}

char	*expand_dollar_helper(t_cmd *cmd, char *str, char *find, int type)
{
	int		remained_dollar;

	expand_two_dollars(cmd, &str, &find, &remained_dollar);
	if (no_need_more_expand(remained_dollar, find, type))
		return (str);
		// return (ft_strdup(str));
	return (expand_one_dollar(cmd, str, find));
}

char	*inside_double_quote(char *location)
{
	char	*pair_location;
	char	c;
	int		len;
	char	*inside;

	c = *location;
	pair_location = location + 1;
	while (*pair_location != c)
		pair_location++;
	len = (pair_location - location) - 1;
	inside = malloc(len + 1);
	inside[len] = '\0';
	ft_memcpy(inside, location + 1, len);
	return (inside);
}

char	*replace_inside_helper(char *str, char *inside, char *handled)
{
	char	*new_str;
	int		new_len;

	new_len = ft_strlen(str) - ft_strlen(inside) + ft_strlen(handled);
	new_str = malloc(new_len + 1);
	new_str[new_len] = '\0';
	return (new_str);
}

char	*replace_inside(char *str, char *location, char *inside, char *handled)
{
	char	*new_str;
	char	*dst;
	char	*src;
	int		l;

	new_str = replace_inside_helper(str, inside, handled);
	dst = new_str;
	src = str;
	l = location - str + 1;
	ft_memcpy(dst, src, l);
	ft_memcpy(new_str, str, (location - str + 1));
	dst = dst + l;
	src = handled;
	l = ft_strlen(handled);
	ft_memcpy(dst, src, l);
	dst = dst + l;
	src = location + ft_strlen(inside) + 1;
	l = ft_strlen(src);
	ft_memcpy(dst, src, l);
	//free(str);
	return (new_str);
}
