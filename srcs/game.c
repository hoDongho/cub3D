/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:08:00 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 16:16:58 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], info->cub.ea, &img);
	load_image(info, info->texture[1], info->cub.we, &img);
	load_image(info, info->texture[2], info->cub.so, &img);
	load_image(info, info->texture[3], info->cub.no, &img);
	load_image(info, info->texture[4], "imgs/DOOR_2A.xpm", &img);
	load_image(info, info->texture[5], "imgs/CARD_1.xpm", &img);
	load_image(info, info->texture[6], "imgs/CARD_2.xpm", &img);
	load_image(info, info->texture[7], "imgs/CARD_3.xpm", &img);
	load_image(info, info->texture[8], "imgs/CARD_4.xpm", &img);
}

void	set_info(t_info *info, int i, int j)
{
	info->buff = ft_calloc(W_HEIGHT, sizeof(int *));
	if (!info->buff)
		puterr_msg("buff malloc error");
	while (++i < W_HEIGHT)
	{
		info->buff[i] = ft_calloc(W_WIDTH, sizeof(int));
		if (!info->buff[i])
			puterr_msg("buff malloc error");
	}
	info->texture = ft_calloc(9, sizeof(int *));
	if (!info->texture)
		puterr_msg("texture malloc error");
	while (++j < 9)
	{
		info->texture[j] = ft_calloc(P_HEIGHT * P_WIDTH, sizeof(int));
		if (!info->texture[j])
			puterr_msg("texture malloc error");
	}
	info->key_cnt = count_elem(info->map, 'K');
	info->sprite = ft_calloc(info->key_cnt + 1, sizeof(t_sprite));
	if (!info->sprite)
		puterr_msg("sprite malloc error");
	set_sprite(info->map, info->sprite);
	load_texture(info);
}

int	mouse_move(t_info *info)
{
	const int	std_x = W_WIDTH / 2;
	int			x;
	int			y;

	mlx_mouse_get_pos(info->win, &x, &y);
	if (y < 0 || y > W_HEIGHT)
		return (0);
	if (x > std_x + W_WIDTH / 4)
		rotate_view(KEY_RIGHT, info, ROTATE_SPEED / 500 * abs(std_x - x));
	else if (x < std_x - W_WIDTH / 4)
		rotate_view(KEY_LEFT, info, ROTATE_SPEED / 500 * abs(std_x - x));
	return (0);
}

int	main_loop(t_info *info)
{
	draw_cell_floor(info, &info->main);
	ray_casting(info);
	sprite(info);
	draw_game(info);
	mouse_move(info);
	if (info->key_flag[0])
		move_front(info);
	if (info->key_flag[1])
		move_back(info);
	if (info->key_flag[2])
		move_right(info);
	if (info->key_flag[3])
		move_left(info);
	if (find_target(info->map, (int)info->p_x, (int)info->p_y) == -1)
		take_card(info);
	if (info->key_flag[4])
		rotate_view(KEY_LEFT, info, ROTATE_SPEED);
	if (info->key_flag[5])
		rotate_view(KEY_RIGHT, info, ROTATE_SPEED);
	if (info->map_sw)
		minimap(info);
	info->frame_cnt++;
	if (info->frame_cnt == 40)
		info->frame_cnt = 0;
	return (0);
}

int	into_game(t_info *info)
{
	info->mlx = mlx_init();
	mlx_do_key_autorepeatoff(info->mlx);
	set_info(info, -1, -1);
	set_info_dir(info);
	info->win = mlx_new_window(info->mlx,
			W_WIDTH, W_HEIGHT, "cub3d");
	info->main.img = mlx_new_image(info->mlx,
			W_WIDTH, W_HEIGHT);
	info->main.addr = (int *)mlx_get_data_addr(info->main.img, &info->main.bpp,
			&info->main.line_length, &info->main.endian);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, PRESS, 0, &key_press, info);
	mlx_hook(info->win, RELEASE, 0, &key_release, info);
	mlx_hook(info->win, RED_BUTTON, 0, &exit_hook, info);
	mlx_loop(info->mlx);
	return (0);
}
