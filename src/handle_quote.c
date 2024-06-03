/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:23:32 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/03 18:12:39 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quote_helper(char *str, int start, int end)
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
		if (same(temp->args[0], "\"\"") || same(temp->args[0], "\'\'"))
			temp->empty_cmd = 1;
		if (handle_quote_args(&temp->args))
			return (1);
		temp = temp->next;
	}
	return (0);
}
