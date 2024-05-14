/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:10:06 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/14 11:25:56 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//Probably it is realted to fill_files file. Should be tested via becomming as comment 
char	*handle_quote_str(char *input)
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

char	**create_args(char *str)
{
	char	**args;

	args = split_pipex(str);
	return (args);
}
