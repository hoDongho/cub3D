/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:26:18 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/13 15:49:32 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp;
	unsigned const char	*str;

	temp = (unsigned char *)dest;
	str = (unsigned const char *)src;
	if (dest <= src)
	{
		if (dest == 0 && src == 0)
			return (dest);
		while (n--)
			*(temp++) = *(str++);
	}
	else
	{
		temp += n;
		str += n;
		while (n--)
			*(--temp) = *(--str);
	}
	return (dest);
}
