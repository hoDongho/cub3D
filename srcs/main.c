/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:16:28 by yehyun            #+#    #+#             */
/*   Updated: 2022/09/27 10:07:29 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		return (puterr_msg("arguments error!") + 2);
	ft_memset(&info, 0, sizeof(t_info));
	if (parsing_map(&info, av[1]) == ERROR)
	{
		free_info(&info);
		return (1);
	}
	free_info(&info);
	return (0);
}
