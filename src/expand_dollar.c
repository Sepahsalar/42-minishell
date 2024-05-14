/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:23:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/14 17:48:04 by asohrabi         ###   ########.fr       */
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
	ft_memcpy(dst, start + (2 * temp_count), ft_strlen(start + (2 * temp_count)));
	// free(str);
	return (new);
}

static char	*get_current_pid(char **envp)
{
	char	*raw_line;
	int		fd;
	char	*pid_str;

	raw_line = "ps|awk '$4==\"./minishell\"'|tail -n 1|awk '{print $1}' >.pid";
	execute_all(raw_line, envp);
	fd = open(".pid", O_RDONLY);
	pid_str = get_next_line(fd);
	pid_str[ft_strlen(pid_str) - 1] = '\0';
	close(fd);
	unlink(".pid");
	return (pid_str);
}

char	*expand_dollar(t_cmd *cmd, char *str, char **envp)
{
	t_env	*env;
	char	*new_str;
	char	*find;
	char	*expanded;
	int		len_var;
	int		len1;
	char	*part2;
	char	*variable;
	int		sq_triger;
	int		index;
	char	*temp;
	int		count;
	int		j;
	int		initial_length;

	env = cmd->env;
	index = 0;
	sq_triger = 0;
	new_str = NULL;
	while (index < (int)ft_strlen(str) && str[index] != '$')
	{
		if (str[index] == '\'')
		{
			if (sq_triger)
				sq_triger = 0;
			else
				sq_triger = 1;
		}
		index++;
	}
	if (sq_triger)
	{
		new_str = ft_strdup(str);
		return (new_str);
	}
	temp = str;
	count = 0;
	index = 0;
	find = ft_strchr(str, '$');
	if (find)
		count = 1;
	temp = get_current_pid(envp);
	j = 0;
	initial_length = ft_strlen(str);
	while (count && find[index] && j < initial_length)
	{
		if (find[index + 1] && find[index + 1] == '$')
		{
			count++;
			index++;
		}
		else
		{
			count = count / 2;
			str = expand_pid(str, find, temp, count);
			index = 0;
			count = 0;
			find = ft_strchr(str + index, '$');
			if (find)
				count = 1;
		}
		j++;
	}
	if (ft_strchr(str, '$') && (*(ft_strchr(str, '$') + 1) == '\0'
			|| *(ft_strchr(str, '$') + 1) == '\"'))
	{
		new_str = ft_strdup(str);
		return (new_str);
	}
	find = ft_strchr(str, '$');
	if (find)
	{
		len1 = find - str;
		if (find[len1 + 1])
			find++;
		len_var = 0;
		while (find[len_var] && find[len_var] != ' '
			&& find[len_var] != '\"' && find[len_var] != '\'')
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
		ft_memcpy(new_str + len1
			+ ft_strlen(expanded), part2, ft_strlen(part2));
		free(variable);
		free(expanded);
	}
	else
		new_str = ft_strdup(str);
	return (new_str);
}

int	expand_all_dollar(t_cmd *start, char **envp)
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
				args[index] = expand_dollar(temp_cmd, args[index], envp);
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
