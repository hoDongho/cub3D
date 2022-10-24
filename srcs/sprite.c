/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:29:35 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/24 17:02:28 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"

void	sort_sprite(t_info *info, t_sprite *sprite)
{
	int			i;
	int			j;
	int			k;
	t_sprite	tmp;

	i = -1;
	while (++i < info->sprite_cnt)
		sprite[i].distance = pow((info->p_x - sprite[i].x), 2) \
							+ pow((info->p_y - sprite[i].y), 2);
	k = -1;
	while (++k < info->sprite_cnt)
	{
		j = -1;
		while (++j < info->sprite_cnt - 1)
		{
			if (sprite[j].distance < sprite[j + 1].distance)
			{
				tmp = sprite[j];
				sprite[j] = sprite[j + 1];
				sprite[j + 1] = tmp;
			}
		}
	}
}

void	select_color(t_info *info, t_sprite *sprite, t_sprite_tool *tool)
{
	const int	texture_index = P_WIDTH * tool->tex_y + tool->tex_x;
	const int	frame = info->frame_cnt / 10 % 4;
	int			texture_id;

	if (sprite->id == 2 && info->access_cnt + 1 == info->sprite_cnt)
		texture_id = 9 + frame;
	else
		texture_id = 5 + frame;
	tool->color = info->texture[texture_id][texture_index];
}

void	draw_sprite(t_info *info, t_sprite *sprite, t_sprite_tool *tool)
{
	int	i;
	int	j;
	int	d;

	i = tool->draw_start_x - 1;
	while (++i < tool->draw_end_x)
	{
		tool->tex_x = (i - (-tool->s_width / 2 + tool->s_screen_x)) \
						* P_WIDTH / tool->s_width;
		if (tool->t_y > 0 && i > 0 && i < W_WIDTH && \
			tool->t_y < info->z_buffer[i])
		{
			j = tool->draw_start_y - 1;
			while (++j < tool->draw_end_y)
			{
				d = (j - tool->v_move_screen) * 2 - W_HEIGHT + tool->s_height;
				tool->tex_y = ((d * P_HEIGHT) / tool->s_height) / 2;
				select_color(info, sprite, tool);
				if ((tool->color & 0x00FFFFFF) != 0)
					info->main.addr[j * W_WIDTH + i] = tool->color;
			}
		}
	}
}

void	init_tool(t_info *info, t_sprite *sprite, t_sprite_tool *tool)
{
	tool->s_x = sprite->x - info->p_x;
	tool->s_y = sprite->y - info->p_y;
	tool->t_x = tool->inv_det * \
				(info->dir_y * tool->s_x - info->dir_x * tool->s_y);
	tool->t_y = tool->inv_det * \
				(-info->plane_y * tool->s_x + info->plane_x * tool->s_y);
	tool->s_screen_x = (int)((W_WIDTH / 2) * (1 + tool->t_x / tool->t_y));
	tool->v_move_screen = (int)(VMOVE / tool->t_y) * (2 - sprite->id);
	tool->s_height = (int)fabs((W_HEIGHT / tool->t_y) / VDIV * sprite->id);
	tool->draw_start_y = -tool->s_height / 2 \
				+ W_HEIGHT / 2 + tool->v_move_screen;
	if (tool->draw_start_y < 0)
		tool->draw_start_y = 0;
	tool->draw_end_y = tool->s_height / 2 + W_HEIGHT / 2 + tool->v_move_screen;
	if (tool->draw_end_y >= W_HEIGHT)
		tool->draw_end_y = W_HEIGHT - 1;
	tool->s_width = (int)fabs((W_HEIGHT / tool->t_y) / UDIV * sprite->id);
	tool->draw_start_x = -tool->s_width / 2 + tool->s_screen_x;
	if (tool->draw_start_x < 0)
		tool->draw_start_x = 0;
	tool->draw_end_x = tool->s_width / 2 + tool->s_screen_x;
	if (tool->draw_end_x >= W_WIDTH)
		tool->draw_end_x = W_WIDTH - 1;
}

int	sprite(t_info *info)
{
	t_sprite_tool	tool;
	int				i;

	ft_memset(&tool, 0, sizeof(t_sprite_tool));
	sort_sprite(info, info->sprite);
	tool.inv_det = 1.0 / (info->plane_x * info->dir_y \
							- info->dir_x * info->plane_y);
	i = -1;
	while (++i < info->sprite_cnt)
	{
		if (info->sprite[i].id == 2 \
			&& info->access_cnt + 1 != info->sprite_cnt)
			continue ;
		init_tool(info, &info->sprite[i], &tool);
		draw_sprite(info, &info->sprite[i], &tool);
	}
	return (0);
}
