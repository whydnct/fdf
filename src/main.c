/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:26:58 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/13 05:51:25 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	//
	*(unsigned int *)dst = color;
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
	mlx = mlx_init(); //connects to the graphical system. Returns a mlx instance
	mlx_win = mlx_new_window(mlx, size_x, size_y, "prueba"); //creates a window, with size and title, tied to the mlx instance
	img.img = mlx_new_image(mlx, size_x, size_y); //creates an image, with size in pixels, tied to the mlx instance
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian); //allocates and returns address of the image. All variables but the address are set by mlx.
	my_mlx_pixel_put(&img, 195, 195, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0); //pushes the img (t_data) to the window
	mlx_key_hook(mlx_win, &exit_on_esc, param);
	mlx_loop(mlx); //renders the window
}
