/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:03:14 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/30 12:17:30 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long	ft_atoi_output(char **input)
{
	long	a;
	char	*find;
	int		temp;
	int len1;
	int len2;
	char *part2;
	char *new;
	char *str;
	char *temp_str;

	a = 0;
	str = *input;
	find = ft_strchr(str, '>');
	
	temp = find - str;
	temp--;
	if (str[temp] == '>')
		temp--;
	part2 = str + temp + 1;
	len2 = ft_strlen(part2);
	if (str[temp] == ' ')
		return (1);
	while (temp >= 0 && str[temp] >= '0' && str[temp] <= '9')
		temp--;
	if (temp != -1 && str[temp] != ' ')
		return (1);
	len1 = temp + 1;
	temp++;
	while (str[temp] >= '0' && str[temp] <= '9')
	{
		a = a * 10 + (str[temp] - '0');
		// if (a < 0)
		// 	perror("bash");
		temp++;
	}
	new = malloc(len1 + len2 + 1);
	new[len1 + len2] = '\0';
	ft_memcpy(new, str, len1);
	ft_memcpy(new + len1, part2, len2);
	temp_str = *input;
	*input = new;
	free(temp_str);
	return (a);
}
