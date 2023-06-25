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
 * NEXT: fix perspective. 
*/
void	init_image(t_bundle *bundle)
{
	bundle->mlx_inst = mlx_init();
	bundle->img = malloc(sizeof(t_img));
	bundle->img->width = WIDTH;
	bundle->img->height = HEIGHT;
	bundle->img->img = mlx_new_image(bundle->mlx_inst, \
		bundle->img->width, bundle->img->height);
	bundle->img->addr = mlx_get_data_addr(bundle->img->img, \
		&bundle->img->bits_per_pixel, &bundle->img->line_length, \
		&bundle->img->endian);
	bundle->mlx_win = mlx_new_window(bundle->mlx_inst, \
		bundle->img->width, bundle->img->height, WIN_TITLE);
}

void	read_map(char *file, t_bundle *bundle)
{
	bundle->v_map = malloc(sizeof(t_v_map));
	get_str_map_rows(file, bundle);
	get_str_map(file, bundle);
	get_heights_colors(bundle);
}

void	project_v_map(t_bundle *bundle)
{
	init_persp(bundle);
	to_new_perspective(bundle->v_map, bundle->persp);
	get_span_v(bundle->v_map);
	get_span_h(bundle->v_map);
	get_max_pps(bundle->v_map, bundle->img);
	scale_v_map(bundle->v_map);
	get_offset(bundle);
	center_v_map(bundle->v_map);
}

int	main(int argc, char **argv)
{
	t_bundle	bundle;

	(void)argc;
	ft_bzero(&bundle, sizeof(bundle));
	init_image(&bundle);
	read_map(argv[1], &bundle);
	project_v_map(&bundle);
	write_v_map_to_image(&bundle);
	//debug(&bundle);
	mlx_put_image_to_window(bundle.mlx_inst, bundle.mlx_win, \
	bundle.img->img, 0, 0);
	printf("pushed to window\n");
	mlx_hook(bundle.mlx_win, 2, 1L << 0, exit_on_esc, &bundle);
	mlx_hook(bundle.mlx_win, 17, 0, quit, &bundle);
	mlx_loop(bundle.mlx_inst);
}
