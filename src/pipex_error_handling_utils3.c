/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_handling_utils3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:48:05 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/19 16:48:06 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_error_helper	init_error_helper(void)
{
	t_error_helper	helper;

	helper.token = NULL;
	helper.index = 0;
	helper.sq = 0;
	helper.dq = 0;
	helper.error = init_error();
	return (helper);
}

void init_token_part1(char ***token)
{
    (*token)[0] = "||";
    (*token)[1] = "<>";
    (*token)[2] = "<<<";
    (*token)[3] = "<<";
    (*token)[4] = "<";
    (*token)[5] = ">>";
    (*token)[6] = ">";
    (*token)[7] = "|";
    (*token)[8] = "&&";
    (*token)[9] = "&";
    (*token)[10] = "*";
}

void init_token_part2(char ***token)
{
	(*token)[11] = "\\";
    (*token)[12] = ";";
    (*token)[13] = "(";
    (*token)[14] = ")";
    (*token)[15] = "{";
    (*token)[16] = "}";
    (*token)[17] = "[";
    (*token)[18] = "]";
    (*token)[19] = ":";
    (*token)[20] = NULL;
}

char	**init_token(t_env_pack env_pack)
{
	char	**token;

	token = (char **)malloc(21 * sizeof(char *));
	if (!token)
		clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	init_token_part1(&token);
	init_token_part2(&token);
	return (token);
}
