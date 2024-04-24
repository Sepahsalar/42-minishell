/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:10:06 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/24 09:12:38 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//ft_handle_quote is based on the assumption that read_line doesn't trim or process anything. just give us the exact input.
int	ft_handle_quote(char ***input)
{
	char	**args;
	char	*temp;
	int		index;

	args = *input;
	index = 0;
	while (args[index])
	{
		if (args[index][0] == '\"')
		{
			temp = args[index];
			args[index] = ft_strtrim(args[index], "\"");
			//handle $
			free(temp);
		}
		else if (args[index][0] == '\'')
		{
			temp = args[index];
			args[index] = ft_strtrim(args[index], "\'");
			free(temp);
		}
		//if not a quote
		if (!args[index])
			return (1);
		index++;
	}
	return (0);
}

char	*ft_handle_quote_str(char *input)
{
	char	*temp;

	if (!input)
		return (NULL);
	if (input[0] == '\"')
		temp = ft_strtrim(input, "\"");
	if (input[0] == '\'')
		temp = ft_strtrim(input, "\'");
	else
		temp = ft_strdup(input);
	if (!temp)
		return (0);
	return (temp);
}

char	**ft_create_args(char *str)
{
	char	**args;

	args = ft_split_pipex(str);
	if (ft_handle_quote(&args))
	    return (NULL);
	return (args);
}
