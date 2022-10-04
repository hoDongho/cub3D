/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:31:18 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/13 15:49:32 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_int_to_char(int nb, int fd)
{
	char	str[10];
	int		i;

	i = 0;
	while (nb > 0)
	{
		str[i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	while (i > 0)
	{
		write(fd, &str[i - 1], 1);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n > 0)
		ft_int_to_char(n, fd);
	else
	{
		n = -n;
		write(fd, "-", 1);
		ft_int_to_char(n, fd);
	}		
}
