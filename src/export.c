/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:44:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 13:25:46 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_node_front(t_env **env, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = *env;
	*env = new;
}

int	is_higher(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 < *s2)
			return (*s2 - *s1);
		if (*s1 > *s2)
			return (*s2 - *s1);
		else
		{
			s1++;
			s2++;
		}
	}
	return (*s2 - *s1);
}

int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}


t_env	*sort_env(t_env *env)
{
	int		index;
	int		count;
	t_env	*temp_index;
	t_env	*temp;

	index = 1;
	count = env_count(env);
	while (index <= count)
	{
		temp = env;
		while (temp && temp->index)
			temp = temp->next;
		temp_index = temp;
		temp = env;
		while (temp)
		{
			if (temp && temp_index && is_higher(temp_index->key, temp->key) < 0
				&& !temp->index)
				temp_index = temp;
			temp = temp->next;
		}
		if (temp_index)
			temp_index->index = index;
		index++;
	}
	return (env);
}

t_env	*handle_oldpwd(t_env *env)
{
	t_env	*temp;
	int		has_oldpwd;

	has_oldpwd = 0;
	temp = env;
	while (temp)
	{
		if (same(temp->key, "OLDPWD"))
			has_oldpwd = 1;
		temp = temp->next;
	}
	if (!has_oldpwd)
		add_node_front(&env, ft_strdup("OLDPWD"), NULL);
	return (env);
}

void export_no_arg(t_cmd *cmd)
{
	int		index;
	t_env	*sorted;
	t_env	*cpy;
	int		count;
	t_env	*temp_env;
	int		i;


	cpy = handle_oldpwd(cpy_env(cmd->env));
	sorted = sort_env(cpy);
	index = 1;
	count = env_count(cpy);
	while (index <= count)
	{
		temp_env = sorted;
		while (temp_env && temp_env->index != index)
			temp_env = temp_env->next;
		if (temp_env && !same(temp_env->key, "_"))
		{
			i = 0;
			printf("declare -x %s", temp_env->key);
			if (temp_env->value)
			{
				printf("=\"");
				while (temp_env->value[i])
				{
					if (temp_env->value[i] == '\"')
						printf("\\\"");
					else
						printf("%c", temp_env->value[i]);
					i++;
				}
				printf("\"\n");
			}
			else
				printf("\n");
		}
		index++;
	}
	clean_env_list(cpy);
}

static void print_export_error(char *arg, int *status)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	*status = 1;
}

static void export_with_plus(t_cmd *cmd, char *arg, int *status)
{
	char 	*new_env;
	char 	*temp_str_1;
	char 	*temp_str_2;
	char 	*find1;
	char 	**split;
	t_env 	*temp_env;
	char 	*temp;
	
	new_env = ft_strdup(arg);
	// if (new_env == NULL)
	// 	return (1);
	find1 = ft_strchr(new_env, '=');
	temp_str_1 = ft_substr(new_env, 0, (find1 - new_env - 1));
	if (!export_check_key(temp_str_1))
		print_export_error(arg, status);
	else
	{
		temp_str_2 = ft_substr(new_env, (find1 - new_env) + 1, ft_strlen(find1 + 1));
		split = ft_split(new_env, '=');
		temp_env = cmd->env;
		while (temp_env != NULL)
		{
			if (ft_strlen(temp_str_1) == ft_strlen(temp_env->key)
				&& !ft_strncmp(temp_env->key, temp_str_1,
					ft_strlen(temp_str_1)))
				break ;
			temp_env = temp_env->next;
		}
		if (!temp_env)
			add_node_front(&cmd->env, temp_str_1, temp_str_2);
		else
		{
			temp = temp_env->value;
			temp_env->value = ft_strjoin(temp, temp_str_2);
			free(temp);
		}
		free(new_env);
	}
}

static void export_normal(t_cmd *cmd, char *arg, int *status)
{
	char 	*new_env;
	char 	*temp_str_1;
	char 	*temp_str_2;
	char 	*find1;
	char 	**split;
	t_env 	*temp_env;
	char 	*temp;

	new_env = ft_strdup(arg);
	// if (new_env == NULL)
	// 	return (1);
	find1 = ft_strchr(new_env, '=');
	temp_str_1 = ft_substr(new_env, 0, find1 - new_env);
	if (!export_check_key(temp_str_1))
		print_export_error(arg, status);
	else
	{
		temp_str_2 = ft_substr(new_env, find1 - new_env + 1, ft_strlen(find1 + 1));
		split = ft_split(new_env, '=');
		temp_env = cmd->env;
		while (temp_env != NULL)
		{
			if (ft_strlen(temp_str_1) == ft_strlen(temp_env->key)
				&& !ft_strncmp(temp_env->key, temp_str_1,
					ft_strlen(temp_str_1)))
				break ;
			temp_env = temp_env->next;
		}
		if (!temp_env)
			add_node_front(&cmd->env, temp_str_1, temp_str_2);
		else
		{
			temp = temp_env->value;
			temp_env->value = ft_strdup(temp_str_2);
			free(temp);
		}
		free(new_env);
		//clean_2d_char(split);
	}
}

static void export_helper(t_cmd *cmd, char *arg, int *status)
{
	if (!export_check(arg))
		print_export_error(arg, status);
	else if (ft_strchr(arg, '='))
	{
		if (ft_strchr(arg, '=') - (arg) > 0
			&& *(ft_strchr(arg, '=') - 1) == '+')
			export_with_plus(cmd, arg, status);
		else
			export_normal(cmd, arg, status);
	}
}


t_env_pack	run_export(t_cmd *cmd)
{
	t_env_pack	env_pack;
	char		**args;
	int			index;
	int			status;

	status = 0;
	args = cmd->args;
	if (!args[1])
		export_no_arg(cmd);
	else
	{
		index = 1;
		while (args[index])
		{
			export_helper(cmd, args[index], &status);
			index++;
		}
	}
	env_pack.env = cmd->env;
	env_pack.original_env = export_original(cmd->original_env, status);
	return (env_pack);
}

t_env	*export_original(t_env *env, int status)
{
	t_env	*temp_env;
	char	*temp;
	char	*status_str;

	temp_env = env;
	while (temp_env)
	{
		if (ft_strlen("exit_code") == ft_strlen(temp_env->key)
			&& !ft_strncmp(temp_env->key, "exit_code",
				ft_strlen("exit_code")))
			break ;
		temp_env = temp_env->next;
	}
	status_str = ft_itoa(status);
	if (!temp_env)
		add_node_front(&env, "exit_code", status_str);
	else
	{
		temp = temp_env->value;
		temp_env->value = status_str;
		free(temp);
	}
	return (env);
}
