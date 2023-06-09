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

void	create_v_map(char *file, t_bundle *bundle)
{
	char	***str_map;

	bundle->v_map = malloc(sizeof(t_v_map));
	get_str_map_rows(file, bundle->v_map);
	str_map = get_str_map(file, bundle->v_map);
	get_str_map_cols(bundle->v_map, str_map);
	get_heights_colors(bundle->v_map, str_map);
	printf("got height and colors\n");
	to_new_perspective(bundle->v_map, bundle->persp);
	printf("transformed to new perspective\n");
	get_span_v(bundle->v_map);
	get_span_h(bundle->v_map, bundle->persp);
	get_max_pps(bundle->v_map, bundle->img->width, bundle->img->height);
	scale_v_map(bundle->v_map);
	get_offset(bundle);
	center_v_map(bundle->v_map);
	printf("v_map centered\n");
}

int	main(int argc, char **argv)
{
	t_bundle	bundle;

	(void)argc;
	init_persp(&bundle);
	init_image(&bundle);
	create_v_map(argv[1], &bundle);
	//write_v_map_to_image(bundle.img, v_map);
	print_heights_colors(&bundle);
	print_x_y(&bundle);
	write_vertices_to_image(&bundle);
	mlx_put_image_to_window(bundle.mlx_inst, bundle.mlx_win, \
	bundle.img->img, 0, 0);
	printf("pushed to window\n");
	mlx_hook(bundle.mlx_win, 2, 1L << 0, exit_on_esc, &bundle);
	mlx_hook(bundle.mlx_win, 17, 0, quit, &bundle);
	mlx_loop(bundle.mlx_inst);
}
