/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:31:11 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/13 15:49:32 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_size(size_t len, size_t str_size)
{
	if (len >= str_size)
		return (str_size);
	else
		return (len);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = (char *)malloc(sizeof(char));
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	size = count_size(len, ft_strlen(s));
	substr = (char *)malloc(sizeof(char) * (size + 1));
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < (int)size)
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}
