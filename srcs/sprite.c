/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:29:35 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 16:39:37 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite.h"

void	init_data(t_info *info, t_sprite *sprite, t_sprite_data *data)
{
	int	i;

	i = -1;
	while (++i < info->key_cnt)
	{
		data->order[i] = i;
		data->distance[i] = pow((info->p_x - sprite[i].x), 2) \
							+ pow((info->p_y - sprite[i].y), 2);
	}
	sort_sprites(data->order, data->distance, info->key_cnt);
	data->inv_det = 1.0 / (info->plane_x * info->dir_y \
							- info->dir_x * info->plane_y);
}

void	draw_sprite(t_info *info, t_sprite *sprite, t_sprite_tool *tool)
{
	int				i;
	int				j;
	int				d;

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
				d = (j - tool->v_move_screen) * 256 - W_HEIGHT * \
					128 + tool->s_height * 128;
				tool->tex_y = ((d * P_HEIGHT) / tool->s_height) / 256;
				if (find_target(info->map, sprite->x, sprite->y) == -2 && info->access_cnt + 1 != info->key_cnt)
					tool->color = info->texture[9][P_WIDTH * tool->tex_y + tool->tex_x];
				else if (find_target(info->map, sprite->x, sprite->y) == -2 && info->access_cnt + 1 == info->key_cnt)
					tool->color = info->texture[9 + info->frame_cnt / 10 % 4][P_WIDTH * tool->tex_y + tool->tex_x];
				else
					tool->color = info->texture[5 + info->frame_cnt / 10 % 4] \
						[P_WIDTH * tool->tex_y + tool->tex_x];
				if ((tool->color & 0x00FFFFFF) != 0)
					info->buff[j][i] = tool->color;
			}
		}
	}
}

void	init_tool(t_info *info, t_sprite *sprite,
	t_sprite_tool *tool, t_sprite_data *data)
{
	tool->s_x = sprite->x - info->p_x;
	tool->s_y = sprite->y - info->p_y;
	tool->t_x = data->inv_det * \
				(info->dir_y * tool->s_x - info->dir_x * tool->s_y);
	tool->t_y = data->inv_det * \
				(-info->plane_y * tool->s_x + info->plane_x * tool->s_y);
	tool->s_screen_x = (int)((W_WIDTH / 2) * (1 + tool->t_x / tool->t_y));
	tool->v_move_screen = (int)(VMOVE / tool->t_y);
	tool->s_height = (int)fabs((W_HEIGHT / tool->t_y) / VDIV);
	tool->draw_start_y = -tool->s_height \
						/ 2 + W_HEIGHT / 2 + tool->v_move_screen;
	if (tool->draw_start_y < 0)
		tool->draw_start_y = 0;
	tool->draw_end_y = tool->s_height / 2 + W_HEIGHT / 2 + tool->v_move_screen;
	if (tool->draw_end_y >= W_HEIGHT)
		tool->draw_end_y = W_HEIGHT - 1;
	tool->s_width = (int)fabs((W_HEIGHT / tool->t_y) / UDIV);
	tool->draw_start_x = -tool->s_width / 2 + tool->s_screen_x;
	if (tool->draw_start_x < 0)
		tool->draw_start_x = 0;
	tool->draw_end_x = tool->s_width / 2 + tool->s_screen_x;
	if (tool->draw_end_x >= W_WIDTH)
		tool->draw_end_x = W_WIDTH - 1;
}

int	sprite(t_info *info)
{
	t_sprite_data	data;
	t_sprite_tool	tool;
	int				i;

	ft_memset(&data, 0, sizeof(t_sprite_data));
	ft_memset(&tool, 0, sizeof(t_sprite_tool));
	data.order = ft_calloc(info->key_cnt, sizeof(int *));
	if (!data.order)
		puterr_msg("sprite malloc error");
	data.distance = ft_calloc(info->key_cnt, sizeof(double *));
	if (!data.distance)
		puterr_msg("sprite malloc error");
	init_data(info, info->sprite, &data);
	i = -1;
	while (++i < info->key_cnt)
	{
		init_tool(info, &info->sprite[data.order[i]], &tool, &data);
		draw_sprite(info, &info->sprite[data.order[i]], &tool);
	}
	free(data.order);
	free(data.distance);
	return (0);
}
