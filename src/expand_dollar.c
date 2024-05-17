/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:23:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/17 20:13:53 by nnourine         ###   ########.fr       */
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

static char	*get_current_pid(t_env *original_env)
{
	char	*raw_line;
	int		fd;
	char	*pid_str;

	raw_line = "ps|awk '$4==\"./minishell\"'|tail -n 1|awk '{print $1}' >.pid";
	execute_all(raw_line, original_env, original_env);
	fd = open(".pid", O_RDONLY);
	pid_str = get_next_line(fd);
	pid_str[ft_strlen(pid_str) - 1] = '\0';
	close(fd);
	unlink(".pid");
	return (pid_str);
}

char	*expand_dollar_helper(t_cmd *cmd, char *str , char *find, int type)
{
	t_env	*env;
	char	*new_str;
	char	*expanded;
	int		len_var;
	int		len1;
	char	*part2;
	char	*variable;
	int		index;
	char	*temp;
	int		count;
	int		initial_length;
	int		remained_dollar;
	int		reletive_index;

	env = cmd->env;
	temp = str;
	count = 0;
	index = 0;
	initial_length = ft_strlen(str);
	temp = get_current_pid(cmd->original_env);
	while (find[index] && find[index] == '$')
	{
		count++;
		index++;
	}
	remained_dollar = count % 2;
	count = count / 2;
	reletive_index = find - str;
	str = expand_pid(str, find, temp, count);
	if (count)
		find = str + reletive_index + (ft_strlen(temp) * count);
	if ((!*find) || (find && (*(find + 1) == '\0'
				|| *(find + 1) == ' ' || (type == 2 && (*(find + 1) == '\''
						|| *(find + 1) == '\"')))))
	{
		new_str = ft_strdup(str);
		return (new_str);
	}
	if (remained_dollar)
	{
		len1 = find - str;
		find++;
		len_var = 0;
		while (find[len_var] && find[len_var] != ' '
			&& find[len_var] != '\"' && find[len_var] != '\''
			&& find[len_var] != '?')
			len_var++;
		if (find[0] == '?' && len_var == 0)
			len_var = 1;
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
		ft_memcpy(new_str + len1
			+ ft_strlen(expanded), part2, ft_strlen(part2));
		free(variable);
		free(expanded);
	}
	else
		new_str = ft_strdup(str);
	return (new_str);
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

char	*replace_inside(char *str, char *location, char *inside, char *handled_inside)
{
	char	*new_str;
	char	*dst;
	char	*src;
	int		l;
	int		new_len;

	new_len = ft_strlen(str) - ft_strlen(inside) + ft_strlen(handled_inside);
	new_str = malloc(new_len + 1);
	new_str[new_len] = '\0';
	dst = new_str;
	src = str;
	l = location - str + 1;
	ft_memcpy(dst, src, l);
	dst = dst + l;
	src = handled_inside;
	l = ft_strlen(handled_inside);
	ft_memcpy(dst, src, l);
	dst = dst + l;
	src = location + ft_strlen(inside) + 1;
	l = ft_strlen(src);
	ft_memcpy(dst, src, l);
	//free(str);
	return (new_str);
}
