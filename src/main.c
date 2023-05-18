/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:26:58 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/16 20:01:44by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

t_v_map	*create_v_map(char *file, t_view *view, int w_width, int w_height)
{
	t_v_map	*ret;
	char	***str_map;

	ret = malloc(sizeof(ret));
	get_str_map_rows(file, ret);
	str_map = get_str_map(file, ret);
	get_str_map_cols(ret, &str_map);
	get_heights_colors(ret, &str_map);
	to_new_perspective(ret, view);
	get_span_v(ret);
	get_span_h(ret);
	get_max_pps(ret, w_width, w_height);
	scale_v_map(ret);
	get_offset(ret, w_width, w_height);
	center_v_map(ret);
	return (ret);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	void	*param;
	t_data	img;
	int		w_width;
	int		w_height;	
	char	*file;
	t_v_map	*v_map;

	(void)argc;
	param = &w_width;
	file = agrv[1];
	w_width = ft_atoi(argv[2]);
	w_height = ft_atoi(argv[3]);
	mlx = mlx_init(); //connects to the graphical system. Returns a mlx instance
	mlx_win = mlx_new_window(mlx, w_width, w_height, "prueba"); //creates a window, with size and title, tied to the mlx instance
	img.img = mlx_new_image(mlx, w_width, w_height); //creates an image, with size in pixels, tied to the mlx instance
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian); //allocates and returns address of the image. All variables but the address are set by mlx.
	v_map = create_v_map(file);
	write_v_map_to_image(&img, v_map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0); //pushes the img (t_data) to the window
	mlx_key_hook(mlx_win, &exit_on_esc, param);
	mlx_loop(mlx); //renders the window
}
