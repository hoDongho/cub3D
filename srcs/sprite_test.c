/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:29:35 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 14:15:22 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ray_casting.h"
#include "cub3d.h"

#define NUM_SPRITES 3

typedef struct s_sprite
{
	double	x;
	double	y;
}	t_sprite; //맵상에서의 x y 좌표

typedef struct	s_pair
{
	double	first;
	int		second;
}	t_pair;

int		sprite_order[NUM_SPRITES];
double	sprite_distance[NUM_SPRITES];

void	sort_sprite(int *order, double *dist, int amount)
{
	
}

int	count_elem(t_dlist *map, int c)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (map)
	{
		while (map->line[++i])
			if (map->line[i] == c)
				cnt++;
		map = map->next;
	}
	return (cnt);
}

int	set_sprite(t_dlist *map, t_sprite *sprite)
{
	int	i;
	int	j;

	j = -1;
	while (map)
	{
		i = -1;
		while (map->line[++i])
		{
			if (map->line[i] == 'K')
			{
				sprite[++j].x = 0.5 + i;
				sprite[j].y = 0.5 + map->height;
			}
		}
		map = map->next;
	}	
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*pair;

	pair = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		pair[i].first = dist[i];
		pair[i].second = order[i];
	}
	sort_order(pair, amount);
	for (int i = 0; i < amount; i++)
	{
		dist[i] = pair[amount - i - 1].first;
		order[i] = pair[amount - i - 1].second;
	}
	free(pair);
}

int	draw_sprite(t_info *info)
{
	t_sprite	*sprite;
	int			s_size;
	double	sprite_x, sprite_y, inv_det, transform_x, transform_y;
	int		sprite_screen_x;

	s_size = count_elem(info->map, 'C');
	sprite = ft_calloc(s_size, sizeof(sprite));
	if (!sprite)
		puterr_msg("sprite malloc error");
	set_sprite(info->map, sprite);
	for (int i = 0; i < s_size; i++)
	{
		sprite_order[i] = i;
		sprite_distance[i] = pow((info->p_x - sprite[i].x), 2) + pow((info->p_y - sprite[i].y), 2);
	}
	sort_sprites(sprite_order, sprite_distance, s_size);
}
