/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:09:24 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 20:13:17 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_pid(char *str, char *start, char *temp, int count)
{
	char	*new;
	int		len;
	char	*dst;
	int		temp_count;

	if (!count)
		return (str);
	len = ft_strlen(str) + (count *(ft_strlen(temp) - 2));
	new = malloc(len + 1);
	if (!new)
		return (NULL);
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

char	*get_current_pid(t_env *original_env)
{
	char		*raw_line;
	int			fd;
	char		*pid_str;
	t_env_pack	env_pack;
	t_env		*cpy;	

	raw_line = "ps|awk '$4==\"minishell\"'|tail -n 1|awk '{print $1}' >.pid";
	cpy = cpy_env(original_env);
	if (!cpy)
		pid_str = ft_strdup("$$");
	cpy = export_original(cpy, 0);
	if (!cpy)
		pid_str = ft_strdup("$$");
	env_pack.env = cpy;
	env_pack.original_env = cpy;
	execute_all(raw_line, env_pack);
	fd = open(".pid", O_RDONLY);
	pid_str = get_next_line(fd);
	if (!pid_str)
		pid_str = ft_strdup("$$");
	else if (pid_str && ft_strlen(pid_str) > 1)
		pid_str[ft_strlen(pid_str) - 1] = '\0';
	clean_env_list(cpy);
	if (close(fd) == -1)
		exit(1);
	if (unlink(".pid") == -1)
		exit(1);
	return (pid_str);
}

void	expand_two_dollars(t_cmd *cmd, char **str,
	char **find, int *remained_dollar)
{
	int		index;
	char	*temp;
	int		count;
	int		reletive_index;

	count = 0;
	index = 0;
	temp = cmd->original_env->next->value;
	while ((*find)[index] && (*find)[index] == '$')
	{
		count++;
		index++;
	}
	(*remained_dollar) = count % 2;
	count = count / 2;
	reletive_index = (*find) - (*str);
	if (count)
	{
		(*str) = expand_pid((*str), (*find), temp, count);
		if (!*str)
			master_clean(NULL, cmd, EXIT_FAILURE);
		(*find) = (*str) + reletive_index + (ft_strlen(temp) * count);
	}
	else
	{
	    *str = ft_strdup(*str);
		if (!*str)
			master_clean(NULL, cmd, EXIT_FAILURE);
		(*find) = (*str) + reletive_index;
	}
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
