/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:26:58 by aperez-m          #+#    #+#             */
/*   Updated: 2023/04/29 11:04:43 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*- Read map
/*	 

#include "ft_fdf.h"

int	exit_on_esc(int keycode, void *param)
{
	(void)param;
	if (keycode == 0xff1b)
		exit(1);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	//write(1, ".", 1);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	void	*param;
	t_data	img;
	int		size_x;
	int		size_y;	

	(void)argc;
	param = &size_x;
	size_x = atoi(argv[1]);
	size_y = atoi(argv[2]);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, size_x, size_y, "prueba");
	img.img = mlx_new_image(mlx, size_x, size_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 195, 195, 0x00FF0000);
	mlx_pixel_put(mlx, mlx_win, 200, 200, 0x00FF0000);
	mlx_pixel_put(mlx, mlx_win, 200, 201, 0x00FF0000);
	mlx_pixel_put(mlx, mlx_win, 201, 201, 0x00FF0000);
	mlx_pixel_put(mlx, mlx_win, 201, 200, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_key_hook(mlx_win, &exit_on_esc, param);
	mlx_loop(mlx);
}
