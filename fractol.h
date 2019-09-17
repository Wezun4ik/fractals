/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:49:39 by sbrella           #+#    #+#             */
/*   Updated: 2019/06/26 18:00:25 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# include "./libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# define WIN_X 1200
# define WIN_Y 1200

typedef struct			s_cl_str
{
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel;
	cl_command_queue	queue;
	cl_int				i;
	cl_int				err;
	size_t				local_size;
	size_t				global_size;
	cl_program			mandel;
	cl_program			julia;
	cl_program			newton;
	cl_program			wreck;
}						t_cl_str;

typedef struct			s_image
{
	int					bpp;
	int					size_line;
	int					endian;
}						t_image;

typedef struct			s_point
{
	double				x;
	double				y;
	double				z;
	int					color;
}						t_point;

typedef struct			s_screen
{
	double				min_r;
	double				max_r;
	double				min_i;
	double				max_i;
	int					iter;
	int					fr_col;
	int					rgb_col;
	int					fract;
	double				jul_im;
	double				jul_re;
	int					space;
	int					colors;
}						t_screen;

void					put_mandel(t_image img, char *image, t_screen *scr);
void					put_burning(t_image img, char *image, t_screen *scr);
void					put_julia(t_image img, char *image, t_screen *scr);
void					put_img_pixel(char *image, t_image img, t_point x);
int						get_color(int iter, t_screen *scr, double rng);
void					put_xernya(t_image img, char *image, t_screen *scr);
void					put_antimandel(t_image img, char *image, t_screen *scr);
int						red_button(void *param);
void					rezoom(int button, int x, int y, t_screen *screen);
int						manage_mouse(int button, int x, int y, void *param);
int						manage_key(int keycode, void *param);
int						manage_move(int x, int y, void *param);
void					draw_fractal(void **mas, t_cl_str *cl_params);
void					init_fract(void **mas, t_screen *screen);
int						prepare_cl(t_cl_str *params);
void					paint_fractal(t_cl_str *cl_params,
						char *image, void **mas);
void					another_fractal(int keycode, void **mas);
#endif
