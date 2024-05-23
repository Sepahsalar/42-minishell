/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:01:19 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/23 11:28:01 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	ft_putnum_exit(const char *str, int sign, int i)
// {
// 	long	a;

// 	a = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = sign * -1;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		a = a * 10 + (str[i] - '0');
// 		if (a < 0 && sign == 1)
// 			return (-1);
// 		else if (a < 0 && sign == -1)
// 			return (0);
// 		i++;
// 	}
// 	return (sign * (int)a);
// }

t_atol	atol_exit(char *str)
{
	int		sign;
	int		i;
	long	a;
	t_atol  res;

	i = 0;
	sign = 1;
	a = 0;
	res.num = 0;
	res.is_error = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || str[0] == '-' || str[0] == '+'))
		{
			res.is_error = 1;
			return (res);
		}
		i++;
	}
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - '0');
		if (a < 0)
		{
			res.is_error = 1;
			return (res);
		}
		// if (a < 0 && sign == 1)
		// 	return (-1);
		// else if (a < 0 && sign == -1)
		// 	return (0);
		i++;
	}
	res.num = sign * a;
	// res.is_error = res.num;
	return (res);
}
