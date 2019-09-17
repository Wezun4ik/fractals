/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:28:13 by sbrella           #+#    #+#             */
/*   Updated: 2019/08/28 18:48:02 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	another_fractal(int keycode, void **mas)
{
	((t_screen*)(mas[4]))->fract = keycode - 17;
	if (keycode == 23)
		((t_screen*)(mas[4]))->fract = 5;
	if (keycode == 22)
		((t_screen*)(mas[4]))->fract = 6;
	if (keycode == 26)
		((t_screen*)(mas[4]))->fract = 7;
	init_fract(mas, mas[4]);
}

void	rezoom(int button, int x, int y, t_screen *screen)
{
	long double	re;
	long double	im;

	im = (screen->max_i - screen->min_i) * 0.1;
	re = (screen->max_r - screen->min_r) * 0.1;
	if (button == 5)
	{
		screen->min_i += im * ((long double)y / WIN_Y);
		screen->max_i -= im * (1.0 - (long double)y / WIN_Y);
		screen->min_r += re * ((long double)x / WIN_X);
		screen->max_r -= re * (1.0 - (long double)x / WIN_X);
	}
	else
	{
		screen->min_i -= im * ((long double)y / WIN_Y);
		screen->max_i += im * (1.0 - (long double)y / WIN_Y);
		screen->min_r -= re * ((long double)x / WIN_X);
		screen->max_r += re * (1.0 - (long double)x / WIN_X);
	}
}
