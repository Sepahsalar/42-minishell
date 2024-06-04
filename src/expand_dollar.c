/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:23:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/04 13:11:18 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_pid(char *str, char *start, char *temp, int count)
{
	char	*new;
	int		len;
	char	*dst;
	int		temp_count;

	if (!count)
		return (str);
	len = ft_strlen(str) + (count *(ft_strlen(temp) - 2));
	new = malloc(len + 1);
	new[len] = '\0';
	dst = new;
	ft_memcpy(dst, str, (start - str));
	dst = dst + (start - str);
	temp_count = count;
	while (count)
	{
		ft_memcpy(dst, temp, ft_strlen(temp));
		dst += ft_strlen(temp);
		count--;
	}
	ft_memcpy(dst, start + (2 * temp_count),
		ft_strlen(start + (2 * temp_count)));
	// free(str);
	return (new);
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
		ft_memset(new, 0, sizeof(t_env));
		new->key = ft_strdup(env->key);
		new->value = ft_strdup(env->value);
		if (!start)
			start = new;
		else
			old->next = new;
		old = new;
		env = env->next;
	}
	return (start);
}

char	*get_current_pid(t_env *original_env)
{
	char		*raw_line;
	int			fd;
	char		*pid_str;
	t_env_pack	env_pack;
	t_env		*cpy;	

	raw_line = "ps|awk '$4==\"./minishell\"'|tail -n 1|awk '{print $1}' >.pid";
	cpy = cpy_env(original_env);
	env_pack.env = cpy;
	env_pack.original_env = cpy;
	execute_all(raw_line, env_pack);
	fd = open(".pid", O_RDONLY);
	pid_str = get_next_line(fd);
	pid_str[ft_strlen(pid_str) - 1] = '\0';
	close(fd);
	unlink(".pid");
	clean_env_list(cpy);
	return (pid_str);
}

void expand_two_dollars(t_cmd *cmd, char **str, char **find, int *remained_dollar)
{
	t_env	*env;
	int		index;
	char	*temp;
	int		count;
	int		initial_length;
	int		reletive_index;

	env = cmd->env;
	count = 0;
	index = 0;
	initial_length = ft_strlen((*str));
	temp = cmd->original_env->next->value;
	while ((*find)[index] && (*find)[index] == '$')
	{
		count++;
		index++;
	}
	(*remained_dollar) = count % 2;
	count = count / 2;
	reletive_index = (*find) - (*str);
	(*str) = expand_pid((*str), (*find), temp, count);
	if (count)
		(*find) = (*str) + reletive_index + (ft_strlen(temp) * count);
}

int	no_need_more_expand(int remain_dollar, char *find, int type)
{
	if (!remain_dollar)
		return (1);
	return ((!*find) || (find && (*(find + 1) == '\0'
				|| *(find + 1) == ' ' || *(find + 1) == '='
				|| (type == 2 && (*(find + 1) == '\''
						|| *(find + 1) == '\"')))));
}

int	it_is_var(char *find, int len_var)
{
	if (find[len_var] && find[len_var] != ' '
		&& find[len_var] != '\"' && find[len_var] != '\''
		&& find[len_var] != '?' && find[len_var] != '=')
		return (1);
	return (0);
}

int	count_len_var(char *find)
{
	int	len_var;

	len_var = 0;
	while (it_is_var(find, len_var))
		len_var++;
	
	if (find[0] == '?' && len_var == 0)
		len_var = 1;
	return (len_var);
}

char *find_var(char *find)
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

char *find_expanded(t_cmd *cmd, char *variable)
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
			return (NULL);
		}
	}
	return (expanded);
}

char *str_after_expansion(char *str, char *find, char *variable, char *expanded)
{
	char	*new_str;
	char	*part2;
	int     len1;

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


char *expand_one_dollar(t_cmd *cmd, char *str , char *find)
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

char	*expand_dollar_helper(t_cmd *cmd, char *str , char *find, int type)
{
	int		remained_dollar;

	expand_two_dollars(cmd, &str, &find, &remained_dollar);
	if (no_need_more_expand(remained_dollar, find, type))
		return (ft_strdup(str));
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

char *replace_inside_helper(char *str, char *inside, char *handled)
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
