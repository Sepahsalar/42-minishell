/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:23:32 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/22 11:59:28 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	end_finder(char *str, int index)
{
	if (str[index] != '\'' && str[index] != '\"')
	{
		index++;
		while (str[index] != '\'' && str[index] != '\"' && str[index] != '\0')
			index++;
		index--;
	}
	else if (str[index] == '\"')
	{
		index++;
		while (str[index] != '\"' && str[index] != '\0')
			index++;
	}
	else
	{
		index++;
		while (str[index] != '\'' && str[index] != '\0')
			index++;
	}
	return (index);
}

void	clean_quote_node(t_quote *node)
{
	if (node)
		free (node);
}

t_quote	*clean_quote_list(t_quote *first)
{
	t_quote	*node;
	t_quote	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		clean_quote_node(node);
		node = temp;
	}
	return (0);
}

t_quote	*create_and_fill_quote_node(int start, int end)
{
	t_quote	*quote;

	quote = malloc(sizeof(t_quote));
	ft_memset(quote, 0, sizeof(t_quote));
	quote->start = start;
	quote->end = end;
	return (quote);
}

t_quote	*create_and_fill_quote_list(char *str)
{
	int		index;
	int		end;
	t_quote	*head;
	t_quote	*new;
	t_quote	*old;

	index = 0;
	head = NULL;
	while (index < (int)ft_strlen(str) - 1 || index == 0)
	{
		// printf("index:%d\n", index);
		end = end_finder(str, index);
		new = create_and_fill_quote_node(index, end);
		if (head == NULL)
			head = new;
		else
			old->next = new;
		if (!new)
			clean_quote_list(head);
		old = new;
		index = end + 1;
	}
	// printf("end of quote list\n");
	return (head);
}

char *sliced_str(char *str, int start, int end)
{
	int		len;
	char	*result;

	len = end - start + 1;
	result = malloc(len + 1);
	result[len] = '\0';
	// printf("in sliced str; start: %d, end: %d\n", start, end);
	ft_memcpy(result, str + start, len);
	return (result);
}

char *quote_helper(char *str, int start, int end)
{
	if (str[start] != '\"' && str[start] != '\'')
		return (sliced_str(str, start, end));
	else
		return (sliced_str(str, start + 1, end - 1));
}

char	*handling_quote(char *str)
{
	char	*result;
	char	*temp_str;
	t_quote	*temp;
	t_quote	*head;

	head = create_and_fill_quote_list(str);
	result = ft_strdup("");
	temp = head;
	while (temp)
	{
		temp_str = result;
		// printf("in handling quote; start: %d, end: %d\n", temp->start, temp->end);
		result = ft_strjoin(result, quote_helper(str, temp->start, temp->end));
		free(temp_str);
		temp = temp->next;
	}
	clean_quote_list(head);
	return (result);
}

int	handle_quote_args(char ***input)
{
	char	**args;
	char	*temp;
	int		index;

	args = *input;
	index = 0;
	while (args[index])
	{
		// printf("in handle_quote_args: %s\n", args[index]);
		temp = args[index];
		args[index] = handling_quote(temp);
		free(temp);
		index++;
	}
	return (0);
}

int	handle_quote_cmd(t_cmd *start)
{
	t_cmd	*temp;

	temp = start;
	while (temp)
	{
		if (handle_quote_args(&temp->args))
			return (1);
		temp = temp->next;
	}
	return (0);
}
