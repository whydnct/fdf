/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:26:58 by aperez-m          #+#    #+#             */
/*   Updated: 2023/04/11 20:18:15 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*param;
	t_data	img;
	int		size_x;
	int		size_y;	

	(void)argc;
	param = &size_x;
	size_x = atoi(argv[1]);
	size_y = atoi(argv[2]);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, "prueba");
	img.img = mlx_new_image(mlx_ptr, size_x, size_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_key_hook(win_ptr, &exit_on_esc, param);
	mlx_loop(mlx_ptr);
}
