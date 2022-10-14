/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:29:35 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 15:46:55 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H
# define UDIV 2.5
# define VDIV 2.5
# define VMOVE 200.0

typedef struct s_sprite_tool
{
	double			inv_det;
	double			s_x;
	double			s_y;
	double			t_x;
	double			t_y;
	int				s_screen_x;
	int				s_height;
	int				s_width;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				tex_x;
	int				tex_y;
	int				v_move_screen;
	unsigned int	color;
}	t_sprite_tool;

#endif
