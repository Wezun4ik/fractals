/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:12:38 by sbrella           #+#    #+#             */
/*   Updated: 2019/08/28 18:52:05 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				init_fract(void **mas, t_screen *screen)
{
	screen->max_r = (screen->fract == 3 || screen->fract == 4) ? 1.5 : 1;
	screen->min_r = (screen->fract == 3 || screen->fract == 4) ? -1.5 : -2;
	screen->min_i = -1.5;
	screen->max_i = 1.5;
	screen->space = 0;
	screen->iter = 40;
	screen->fr_col = 0xFFFFFF;
	screen->rgb_col = 1000;
	screen->colors = 0;
	if (screen->fract == 3 || screen->fract == 4)
	{
		screen->jul_im = 0.5;
		screen->jul_re = -0.5;
	}
	mas[4] = screen;
}

void				draw_fractal(void **mas, t_cl_str *cl_params)
{
	char			*image;
	t_image			img;

	image = mlx_get_data_addr(mas[3],
	&(img.bpp), &(img.size_line), &(img.endian));
	paint_fractal(cl_params, image, mas);
	mlx_put_image_to_window(mas[0], mas[1], mas[3], 0, 0);
}

int					get_fractal(char *fract)
{
	if (ft_strcmp("julia", fract) == 0)
		return (3);
	if (ft_strcmp("mandelbrot", fract) == 0)
		return (1);
	if (ft_strcmp("burning_ship", fract) == 0)
		return (2);
	if (ft_strcmp("biomorph", fract) == 0)
		return (4);
	if (ft_strcmp("antimandel", fract) == 0)
		return (5);
	if (ft_strcmp("graphself", fract) == 0)
		return (6);
	if (ft_strcmp("spider", fract) == 0)
		return (7);
	else
		return (0);
}

int					main(int argc, char **argv)
{
	void		*mas[6];
	t_cl_str	cl_params;
	t_screen	screen;

	if (argc != 2 || !(screen.fract = get_fractal(argv[1])))
	{
		ft_putstr("usage: fractol *fractal_name*\n*fractal_name*:\n->julia\n");
		ft_putstr("->antimandel\n->burning_ship\n->mandelbrot\n->biomorph\n");
		ft_putstr("->graphself\n");
		return (0);
	}
	mas[0] = mlx_init();
	mas[1] = mlx_new_window(mas[0], WIN_X, WIN_Y, "HELLO");
	mas[2] = &cl_params;
	mas[3] = mlx_new_image(mas[0], WIN_X, WIN_Y);
	init_fract(mas, &screen);
	prepare_cl(&cl_params);
	draw_fractal(mas, &cl_params);
	mlx_hook(mas[1], 17, 0, red_button, mas);
	mlx_hook(mas[1], 4, 0, manage_mouse, mas);
	mlx_hook(mas[1], 5, 0, manage_mouse, mas);
	mlx_hook(mas[1], 2, 0, manage_key, mas);
	mlx_hook(mas[1], 6, 0, manage_move, mas);
	mlx_loop(mas[0]);
	return (0);
}
