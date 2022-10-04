/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:28:32 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/13 15:49:32 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*pos_num(long n)
{
	int		cnt;
	int		i;
	long	nbr;
	char	*temp;

	cnt = 0;
	nbr = n;
	while (n)
	{
		n /= 10;
		cnt++;
	}
	temp = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!temp)
		return (NULL);
	temp[cnt] = '\0';
	i = 0;
	while (nbr)
	{
		temp[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	ft_strrev(temp);
	return (temp);
}

static char	*neg_num(long n)
{
	int		cnt;
	int		i;
	long	nbr;
	char	*temp;

	cnt = 1;
	nbr = n * -1;
	while (n)
	{
		n /= 10;
		cnt++;
	}
	temp = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!temp)
		return (NULL);
	temp[cnt] = '\0';
	i = 0;
	while (nbr)
	{
		temp[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	temp[i] = '-';
	ft_strrev(temp);
	return (temp);
}

char	*ft_itoa(long n)
{
	char	*str;

	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	else if (n < 0)
		str = neg_num(n);
	else
		str = pos_num(n);
	return (str);
}
