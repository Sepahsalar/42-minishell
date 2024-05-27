/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:03:14 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/27 17:55:33 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// long	atoi_file(char **input, int def)
// {
// 	long	a;
// 	char	*find;
// 	int		temp;
// 	int		len1;
// 	int		len2;
// 	char	*part2;
// 	char	*new;
// 	char	*str;
// 	char	*temp_str;

// 	a = 0;
// 	str = *input;
// 	if (def == 0)
// 		find = ft_strchr(str, '<');
// 	else
// 		find = ft_strchr(str, '>');
// 	temp = find - str;
// 	temp--;
// 	if ((temp >= 0 && str[temp] == '>' && def == 1)
// 		|| (str[temp] == '<' && def == 0))
// 		temp--;
// 	part2 = str + temp + 1;
// 	len2 = ft_strlen(part2);
// 	if (str[temp] == ' ')
// 		return (def);
// 	while (temp >= 0 && str[temp] >= '0' && str[temp] <= '9')
// 		temp--;
// 	if (temp != -1 && str[temp] != ' ')
// 		return (def);
// 	len1 = temp + 1;
// 	temp++;
// 	while (str[temp] >= '0' && str[temp] <= '9')
// 	{
// 		a = a * 10 + (str[temp] - '0');
// 		// if (a < 0)
// 		// 	perror("bash");
// 		temp++;
// 	}
// 	new = malloc(len1 + len2 + 1);
// 	new[len1 + len2] = '\0';
// 	ft_memcpy(new, str, len1);
// 	ft_memcpy(new + len1, part2, len2);
// 	temp_str = *input;
// 	*input = new;
// 	free(temp_str);
// 	return (a);
// }

long	atoi_file(char **input, int place, int def)
{
	long	a;
	char	*find;
	int		temp;
	int		len1;
	int		len2;
	char	*part2;
	char	*new;
	char	*str;
	char	*temp_str;

	a = 0;
	str = *input;
	// if (def == 0)
	// 	find = ft_strchr(str, '<');
	// else
	// 	find = ft_strchr(str, '>');
	find = str + place;
	temp = find - str;
	if (temp)
		temp--;
	else
	{
		if (def == 0)
			return (0);
		if (def == 1)
			return (1);
	}
	if ((temp >= 0 && str[temp] == '>' && def == 1)
		|| (str[temp] == '<' && def == 0))
		temp--;
	part2 = str + temp + 1;
	len2 = ft_strlen(part2);
	if (str[temp] == ' ')
		return (def);
	while (temp >= 0 && str[temp] >= '0' && str[temp] <= '9')
		temp--;
	if (temp != -1 && str[temp] != ' ')
		return (def);
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
