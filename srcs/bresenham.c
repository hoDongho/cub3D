#include "cub3d.h"

void	bresenham_main(t_info *info, int end_pos_x, int end_pos_y)
{
	int	width;
	int	height;
	int	det;

	width = abs(end_pos_x - info->p_x);
	height = abs(end_pos_y - info->p_y);

	if (width > height)
	{
		det = (2 * height) - width;
		if (det < 0)
		{
			det += 2 * height;
		}
		else
		{
			// y값 초기화
			det += (2 * height - 2 * width);
		}
	}
	else
	{
		det = (2 * width) - height;
		if (det < 0)
		{
			det += 2 * width;
		}
		else
		{
			// x값 초기화
			det += (2 * width - 2 * height);
		}
	}
}