/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:44:56 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/21 12:21:58by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	write_v_map_to_image(t_bundle *bundle)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
			choose_lines(bundle, i, j);
		j = -1;
	}
}

void	my_mlx_pixel_put(t_img *img, double x, double y, int color)
{
	char	*dst;
	int		offset;

	if (xy_within_limits(img, x, y))
	{
		offset = (int)(y * img->line_length \
			+ x * (img->bits_per_pixel / 8));
		dst = img->addr + offset;
		*(unsigned int *)dst = color;
	}
	else
		printf("out of bounds\n");
}

int	xy_within_limits(t_img *img, double x, double y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > img->width || y > img->height)
		return (0);
	return (1);
}
int	interpolate(int x, int span_x, int span_value)
{
	int	ret;

	ret = (span_value / span_x) * x;
	return (ret);
}
