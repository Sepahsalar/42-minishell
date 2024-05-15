/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:23:36 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/15 12:54:52 by nnourine         ###   ########.fr       */
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

// static char	*get_current_pid(char **envp)
// {
// 	char	*raw_line;
// 	int		fd;
// 	char	*pid_str;

// 	raw_line = "ps|awk '$4==\"./minishell\"'|tail -n 1|awk '{print $1}' >.pid";
// 	execute_all(raw_line, envp);
// 	fd = open(".pid", O_RDONLY);
// 	pid_str = get_next_line(fd);
// 	pid_str[ft_strlen(pid_str) - 1] = '\0';
// 	close(fd);
// 	unlink(".pid");
// 	return (pid_str);
// }
static char	*get_current_pid(t_cmd *cmd)
{
	char	*raw_line;
	int		fd;
	char	*pid_str;
	char 	**envp;

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
	// char 	*sq_location;
	// char 	*dq_location;
	int		index;
	char	*temp;
	int		count;
	int		j;
	int		initial_length;

	env = cmd->env;
	new_str = NULL;
	index = 0;

	//We are checking wether the $ is inside double or single quotes
	// sq_location = NULL;
	// dq_location = NULL;
	// while (index < (int)ft_strlen(str) && str[index] != '$')
	// {
	// 	if (str[index] == '\'')
	// 	{
	// 		if (sq_location)
	// 			sq_location = NULL;
	// 		else
	// 			sq_location = str + index;
	// 	}
	// 	if (str[index] == '\"')
	// 	{
	// 		if (dq_location)
	// 			dq_location = NULL;
	// 		else
	// 			dq_location = str + index;
	// 	}
	// 	index++;
	// }
	// if (sq_location && dq_location)
	// {
	// 	if (sq_location < dq_location)
	// 	{
	// 		//We have a doble quote inside a single quote
	// 		//and inside the double quote is the $ character
	// 		new_str = ft_strdup(str);
	// 		return (new_str);
	// 	}
	// 	else
	// 	{
	// 		//We have a single quote inside a double quote
	// 		//and inside the single quote is the $ character
	// 		//remove double quote
	// 		//keep the single quote
	// 		//for what is inside the single quote we should run helper and replace the result with what inside the sigle quote
	// 		//"1'2$3'" = 1'helper(2$3)'
			
			
	// 	}
	// }
	// else if (sq_location)
	// {
	// 	//$ is inside a signle quote
	// 	new_str = ft_strdup(str);
	// 	return (new_str);
	// }
	// else if (dq_location)
	// {
	// 	//$ is inside a double quote
	// 	//We have to remove dg_location and its pair and create a str for the next step
	// 	//we need a function to recive old str and dq_location and it should return a new str with strlen(str) - 2 length
	// 	//"12$3" = helper(12$3)
	// }
	temp = str;
	count = 0;
	index = 0;
	find = ft_strchr(str, '$');
	if (find)
		count = 1;
	(void)envp;
	temp = NULL;
	temp = get_current_pid(envp);
	j = 0;
	initial_length = ft_strlen(str);
	printf("before while for even removal\n");
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
	printf("after while for even removal\n");
	if (ft_strchr(str, '$') && (*(ft_strchr(str, '$') + 1) == '\0'
			|| *(ft_strchr(str, '$') + 1) == '\"'))
	{
		new_str = ft_strdup(str);
		return (new_str);
	}
	printf("Should not see here\n");
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
