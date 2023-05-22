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

void init_image(t_img *img, int mlx_inst)
{
	img->width = WIDTH;
	img->height = HEIGHT;
	img->img = mlx_new_image(mlx_inst, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,\
		 &img->line_length, &img->endian);
}

t_v_map	*create_v_map(char *file, t_persp *persp, t_img *img)
{
	t_v_map	*ret;
	char	***str_map;

	ret = malloc(sizeof(t_v_map));
	get_str_map_rows(file, ret);
	str_map = get_str_map(file, ret);
	get_str_map_cols(ret, &str_map);
	get_heights_colors(ret, &str_map);
	to_new_perspective(ret, persp);
	get_span_v(ret);
	get_span_h(ret, persp);
	get_max_pps(ret, img->width, img->height);
	scale_v_map(ret);
	get_offset(ret, img->width, img->height);
	center_v_map(ret);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_bundle	bundle;
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_persp		persp;
	t_v_map		*v_map;

	(void)argc;
	init_persp(&bundle);
	mlx = mlx_init();
	init_image(&img);
	mlx_win = mlx_new_window(mlx, img.width, img.height, WIN_TITLE);
	v_map = create_v_map(argv[1], &persp, &img);
	write_v_map_to_image(&img, v_map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 2, 0, exit_on_esc, &img);
	mlx_hook(mlx_win, 17, quit, &img);
	mlx_loop(mlx);
}
