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
	get_span_h(ret, view);
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
	t_data	img;
	t_view	*view;
	t_v_map	*v_map;

	(void)argc;
	view = malloc(sizeof(t_view));
	view->col_x = COL_2_X;
	view->row_x = ROW_2_X;
	view->col_y = COL_2_Y;
	view->row_y = ROW_2_Y;
	view->height_y = HEIGHT_2_Y;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, ft_atoi(argv[2]), ft_atoi(argv[3]), "prueba");
	img.img = mlx_new_image(mlx, ft_atoi(argv[2]), ft_atoi(argv[3]));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	v_map = create_v_map(argv[1], view, ft_atoi(argv[2]), ft_atoi(argv[3]));
	write_v_map_to_image(&img, v_map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_key_hook(mlx_win, &exit_on_esc, &img);
	mlx_loop(mlx);
}
