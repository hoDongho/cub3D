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
	load_image(info, info->texture[0], info->cub.ea);
	load_image(info, info->texture[1], info->cub.we);
	load_image(info, info->texture[2], info->cub.so);
	load_image(info, info->texture[3], info->cub.no);
	load_image(info, info->texture[4], "imgs/DOOR_2A.xpm");
	load_image(info, info->texture[5], "imgs/CARD_1.xpm");
	load_image(info, info->texture[6], "imgs/CARD_2.xpm");
	load_image(info, info->texture[7], "imgs/CARD_3.xpm");
	load_image(info, info->texture[8], "imgs/CARD_4.xpm");
	load_image(info, info->texture[9], "imgs/EXIT_1.xpm");
	load_image(info, info->texture[10], "imgs/EXIT_2.xpm");
	load_image(info, info->texture[11], "imgs/EXIT_3.xpm");
	load_image(info, info->texture[12], "imgs/EXIT_4.xpm");
}

void	set_info(t_info *info, int i, int j)
{
	(void)i;
	info->texture = ft_calloc(13, sizeof(int *));
	if (!info->texture)
		puterr_msg("texture malloc error");
	while (++j < 13)
	{
		info->texture[j] = ft_calloc(P_HEIGHT * P_WIDTH, sizeof(int));
		if (!info->texture[j])
			puterr_msg("texture malloc error");
	}
	info->sprite_cnt = count_elem(info->map, 'K') + count_elem(info->map, 'X');
	info->sprite = ft_calloc(info->sprite_cnt + 1, sizeof(t_sprite));
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
		rotate_view(info, ROTATE_SPEED / 500 * abs(std_x - x));
	else if (x < std_x - W_WIDTH / 4)
		rotate_view(info, -ROTATE_SPEED / 500 * abs(std_x - x));
	return (0);
}

int	main_loop(t_info *info)
{
	draw_cell_floor(info, &info->main);
	ray_casting(info);
	sprite(info);
	mlx_put_image_to_window(info->mlx, info->win, info->main.img, 0, 0);
	mouse_move(info);
	key_move(info);
	if (find_target(info->map, (int)info->p_x, (int)info->p_y) == -1)
		take_card(info);
	if (find_target(info->map, (int)info->p_x, (int)info->p_y) == -2 \
		&& info->access_cnt + 1 == info->sprite_cnt)
		exit_hook(info);
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
	set_info(info, -1, -1);
	set_info_dir(info);
	info->win = mlx_new_window(info->mlx,
			W_WIDTH, W_HEIGHT, "cub3d");
	info->main.img = mlx_new_image(info->mlx,
			W_WIDTH, W_HEIGHT);
	info->main.addr = (int *)mlx_get_data_addr(info->main.img, &info->main.bpp,
			&info->main.line_length, &info->main.endian);
	mlx_hook(info->win, PRESS, 0, &key_press, info);
	mlx_hook(info->win, RELEASE, 0, &key_release, info);
	mlx_hook(info->win, RED_BUTTON, 0, &exit_hook, info);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_loop(info->mlx);
	return (0);
}
