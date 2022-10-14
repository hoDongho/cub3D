/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:12:02 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 16:24:38 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"

int	count_elem(t_dlist *map, int c)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (map)
	{
		i = -1;
		while (map->line[++i])
			if (map->line[i] == c)
				cnt++;
		map = map->next;
	}
	return (cnt);
}

void	set_sprite(t_dlist *map, t_sprite *sprite)
{
	int	i;
	int	j;

	j = -1;
	while (map)
	{
		i = -1;
		while (map->line[++i])
		{
			if (map->line[i] == 'K' || map->line[i] == 'X')
			{
				sprite[++j].x = i + 0.5;
				sprite[j].y = map->height + 0.5;
				if (map->line[i] == 'K')
					sprite[j].id = 1;
				else
					sprite[j].id = 2;
			}
		}
		map = map->next;
	}
}

void	take_card(t_info *info)
{
	t_dlist	*tmp;
	int		i;

	tmp = info->map;
	while (tmp->height != (int)info->p_y)
		tmp = tmp->next;
	tmp->line[(int)info->p_x] = '0';
	info->access_cnt++;
	i = -1;
	while (++i < info->sprite_cnt)
	{
		if ((int)info->sprite[i].x == (int)info->p_x
			&& (int)info->sprite[i].y == (int)info->p_y)
			ft_memmove(&info->sprite[i], &info->sprite[i + 1], \
			sizeof(t_sprite) * (info->sprite_cnt - i));
	}
}
