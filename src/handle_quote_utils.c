/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:07:19 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/03 18:11:09 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	end_finder(char *str, int index)
{
	if (str[index] && str[index] != '\'' && str[index] != '\"')
	{
		index++;
		while (str[index] && str[index] != '\'' && str[index] != '\"')
			index++;
		index--;
	}
	else if (str[index] && str[index] == '\"')
	{
		index++;
		while (str[index] && str[index] != '\"')
			index++;
	}
	else if (str[index])
	{
		index++;
		while (str[index] && str[index] != '\'')
			index++;
	}
	return (index);
}

t_quote	*clean_quote_list(t_quote *first)
{
	t_quote	*node;
	t_quote	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		if (node)
			free(node);
		node = temp;
	}
	return (0);
}

static t_quote	*create_and_fill_quote_node(int start, int end)
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
	return (head);
}

char	*sliced_str(char *str, int start, int end)
{
	int		len;
	char	*result;

	len = end - start + 1;
	result = malloc(len + 1);
	result[len] = '\0';
	ft_memcpy(result, str + start, len);
	return (result);
}
