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
/**
 * NEXT: v_map is created but not displayed. 
*/
void	init_image(t_bundle *bundle)
{
	bundle->img = malloc(sizeof(t_img));
	bundle->img->width = WIDTH;
	bundle->img->height = HEIGHT;
	bundle->mlx_inst = mlx_init();
	bundle->img->img = mlx_new_image(bundle->mlx_inst, \
		bundle->img->width, bundle->img->height);
	bundle->img->addr = mlx_get_data_addr(bundle->img->img, \
		&bundle->img->bits_per_pixel, &bundle->img->line_length, \
		&bundle->img->endian);
	bundle->mlx_win = mlx_new_window(bundle->mlx_inst, \
		bundle->img->width, bundle->img->height, WIN_TITLE);
}

t_v_map	*create_v_map(char *file, t_persp *persp, t_img *img)
{
	t_v_map	*ret;
	char	***str_map;

	ret = malloc(sizeof(t_v_map));
	printf("ret allocated\n");
	get_str_map_rows(file, ret);
	printf("got v_map rows\n");
	str_map = get_str_map(file, ret);
	printf("got str_map\n");
	get_str_map_cols(ret, str_map);
	printf("got str_map cols\n");
	get_heights_colors(ret, str_map);
	printf("got height and colors\n");
	to_new_perspective(ret, persp);
	printf("transformed to new perspective\n");
	get_span_v(ret);
	get_span_h(ret, persp);
	get_max_pps(ret, img->width, img->height);
	scale_v_map(ret);
	get_offset(ret, img->width, img->height);
	center_v_map(ret);
	printf("v_map centered\n");
	return (ret);
}

int	main(int argc, char **argv)
{
	t_bundle	bundle;
	t_v_map		*v_map;

	(void)argc;
	init_persp(&bundle);
	printf("perspective initiated\n");
	init_image(&bundle);
	printf("image initiated\n");
	v_map = create_v_map(argv[1], bundle.persp, bundle.img);
	printf("v_map created\n");
	write_v_map_to_image(bundle.img, v_map);
	printf("v_map written to img\n");
	mlx_put_image_to_window(bundle.mlx_inst, bundle.mlx_win, \
	bundle.img->img, 0, 0);
	mlx_hook(bundle.mlx_win, 2, 0, exit_on_esc, &bundle);
	mlx_hook(bundle.mlx_win, 17, 0, quit, &bundle);
	mlx_loop(bundle.mlx_inst);
}
