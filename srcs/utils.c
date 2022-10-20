/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:28:42 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/20 14:32:35 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_color(char *str)
{
	char	**tmp;
	int		r;
	int		g;
	int		b;
	int		i;

	tmp = ft_split(str, ',');
	if (!tmp)
		puterr_msg("color split error");
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (r << 16 | g << 8 | b);
}

int	puterr_msg(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

int	free_info(t_info *info)
{
	if (info->cub.no)
		free(info->cub.no);
	if (info->cub.so)
		free(info->cub.so);
	if (info->cub.we)
		free(info->cub.we);
	if (info->cub.ea)
		free(info->cub.ea);
	if (info->map)
		delete_dlist(info->map);
	return (0);
}

char	*gnl_scan(int fd, int flag)
{
	char	*tmp;

	tmp = get_next_line(fd);
	if (!tmp || !tmp[0])
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	if (!ft_strncmp(tmp, "\n", 2))
	{
		if (!flag)
		{
			free(tmp);
			return (gnl_scan(fd, flag));
		}
		return (tmp);
	}
	if (tmp[ft_strlen(tmp) - 1] == '\n')
		tmp[ft_strlen(tmp) - 1] = '\0';
	return (tmp);
}

void	load_image(t_info *info, int *texture, char *path)
{
	t_img	img;
	int		x;
	int		y;

	img.img = mlx_xpm_file_to_image(info->mlx, path,
			&img.width, &img.height);
	if (!img.img)
		puterr_msg("failed to load image");
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp,
			&img.line_length, &img.endian);
	y = -1;
	while (++y < img.height)
	{
		x = -1;
		while (++x < img.width)
			texture[img.width * y + x] = img.addr[img.width * y + x];
	}
	mlx_destroy_image(info->mlx, img.img);
}
