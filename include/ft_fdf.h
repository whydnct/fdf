/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:30:39 by aperez-m          #+#    #+#             */
/*   Updated: 2023/07/09 10:07:41 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

/**
 * free helpers
*/
# define IMG_ALLOCD 1
# define V_MAP_ALLOCD 2
# define STR_MAP_ALLOCD 3
# define PERSP_ALLOCD 4
# define VTX_ALLOCD 5

/**
 * parametres for isometric perspective
 * col_2_x = cos^2(30)
 * x = col'*Sen(a) - row'*Sen(b)
 * y = row'*Sen(180 - b) col'*Cos(180-a) - height'
 * row_2_x = -sen(30)cos(30)
 * col_2_y = sen(30)cos(30)
 * row_2_y = sen^2(30)
 * height_2_y = -cos(30)
*/
# define COL_2_X 0.7084087
# define ROW_2_X 0.7084087
# define COL_2_Y -0.48
# define ROW_2_Y 0.48
# define HEIGHT_2_Y -0.8616

/**
 * image properties
*/
# define WIDTH 1000
# define HEIGHT 1000
/**
 * window title
*/
# define WIN_TITLE "FdF"
/**
 * event keys
*/
# define XK_ESCAPE_L 0xff1b
# define Q_KEY_L 0x0071
# define ESC_KEY_M 53
# define Q_KEY_M 12

# include "mlx.h"
# include "ft.h"
# include <math.h>
# include <fcntl.h>
# include <limits.h>

/**
 * @brief actual image that is shown on screen
*/
typedef struct s_img{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

/**
 * @brief holds the factors for the chosen perpective
 * col_x = factor that translates colum to x coordinate
 * ...
*/
typedef struct s_persp{
	double	col_x;
	double	row_x;
	double	col_y;
	double	row_y;
	double	height_y;
}				t_persp;

/**
 * @brief each of the vtx o the vertex map
 */
typedef struct s_vertex{
	int				col;
	int				row;
	int				height;
	double			x;
	double			y;
	unsigned int	color;
}				t_vertex;

/**
 * @brief holds all the vtx
 */
typedef struct s_v_map{
	t_vertex	**vtx;
	int			rows;
	int			cols;
	double		span_h;
	double		span_v;
	int			offset_h;
	int			offset_v;
	double		pps;
}				t_v_map;

/**
 * @brief all structs bundled
*/
typedef struct s_bundle{
	void	*mlx_inst;
	void	*mlx_win;
	t_persp	*persp;
	t_img	*img;
	t_v_map	*v_map;
	char	***str_map;
	int		allocs;
}			t_bundle;

// INIT
void	init_image(t_bundle *bundle);

//READ FILE INTO VERTEX MAP

void	read_map(char *file, t_bundle *bundle);

//gets the number of rows and colums in the file
void	get_str_map_rows(char *file, t_bundle *bundle);

/**
 * @brief reads the file into a char ***. Every row is a char **
 * @param file path for the file
 * @return char *** that stores all strings in the map
 * @note 
 */
void	get_str_map(char *file, t_bundle *bundle);

//builds a t_vertex ** and gets height and color for each vertex
void	get_heights_colors(t_bundle *bundle);

//transforms the hexa coded color to int
int		hex_to_color(char *str);
char	*sanitize_line(char *line);

// PROJECT V_MAP

/**
 * @brief fills x and y values of the v_map
 */
void	project_v_map(t_bundle *bundle);

/**
 * @brief sets the values for all the factors of the
 * perspective
*/
void	init_persp(t_bundle *bundle);

/**
 * @brief gets x and y of each vertex in the new perspective
 * @note doesn't scale or move the vtx map
*/
void	to_new_perspective(t_v_map *v_map, t_persp *persp);

double	get_y_max(t_v_map *v_map);
double	get_y_min(t_v_map *v_map);

//get the vertical span of the vtx map, unscaled
void	get_span_v(t_v_map *v_map);

//get the horizontal span of the vtx map, unscaled
void	get_span_h(t_v_map *v_map);

/**
 * @brief gets the maximum Pixels Per grid Side (zoom) for the vtx 
 * map to be shown completely in the window
 * @note pps = pixels per grid side
*/
void	get_max_pps(t_v_map *v_map, t_img *img);

//scale v_map_around 0,0
void	scale_v_map(t_v_map *v_map);

//get vector from scaled v_map to image center
void	get_offset(t_bundle *bundle);

//move the v_map to the center of the window
void	center_v_map(t_v_map *v_map);

// IMAGE TO WINDOW

void	write_v_map_to_image(t_bundle *bundle);
//choses what lines to draw from each vertex
void	choose_lines(t_bundle *bundle, int i, int j);

/**
 * @param dir 1 draws line to vertex to the right, 0 draws line to vertex below
*/
void	draw_line(t_bundle *bundle, int i, int j, int dir);
void	plot_line_h(t_bundle *bundle, t_vertex **nodes, int *deltas, int sense);
void	plot_line_v(t_bundle *bundle, t_vertex **nodes, int *deltas, int sense);
int		xy_within_limits(t_img *img, double x, double y);
void	my_mlx_pixel_put(t_img *img, double x, double y, int color);
// COLORS

int		get_color(t_vertex **nodes, int *deltas, int *pixel);
double	percent(int start, int end, int current);

// EXIT
void	free_str_map(t_bundle *bundle);
void	free_v_map(t_bundle *bundle);
void	free_all(t_bundle *bundle);
int		exit_on_esc(int keycode, t_bundle *bundle);
int		quit(t_bundle *bundle, int status);

// PARAM VALIDATORS

int		get_line_cols(char *line, char c);
char	*purge_gnl(int fd, char **line);

#endif
/**
// DEBUGGERS
void	debug(t_bundle *bundle);
void	print_heights_colors(t_bundle *bundle);
void	print_x_y(t_bundle *bundle);
void	write_vtx_to_image(t_bundle *bundle);
void	print_str_map(t_bundle *bundle, char ***str_map);
void	print_x_y_file(t_bundle *bundle);
void	print_height_file(t_bundle *bundle);
void	print_color_file(t_bundle *bundle);
*/