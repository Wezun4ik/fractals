/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:29:26 by sbrella           #+#    #+#             */
/*   Updated: 2019/08/28 18:54:12 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		red_button(void *param)
{
	t_cl_str *prm;

	prm = ((void**)param)[2];
	clReleaseCommandQueue(prm->queue);
	clReleaseContext(prm->context);
	mlx_destroy_window(((void**)param)[0], ((void**)param)[1]);
	mlx_destroy_image(((void**)param)[0], ((void**)param)[3]);
	exit(0);
}

int		manage_mouse(int button, int x, int y, void *param)
{
	void	**mas;

	mas = (void**)param;
	if (button == 4 || button == 5)
	{
		rezoom(button, x, y, mas[4]);
		draw_fractal(mas, mas[2]);
	}
	return (0);
}

void	keys(int keycode, void *param, void **mas)
{
	long double		diff;

	if (keycode == 53)
	{
		mlx_destroy_image(((void**)param)[0], ((void**)param)[3]);
		mlx_destroy_window(mas[0], mas[1]);
		exit(0);
	}
	else if (keycode == 0 || keycode == 2)
	{
		diff = (keycode == 2 ?
		((t_screen*)(mas[4]))->max_r - ((t_screen*)(mas[4]))->min_r :
		-(((t_screen*)(mas[4]))->max_r - ((t_screen*)(mas[4]))->min_r)) * 0.1;
		((t_screen*)(mas[4]))->max_r += diff;
		((t_screen*)(mas[4]))->min_r += diff;
	}
	else if (keycode == 1 || keycode == 13)
	{
		diff = (keycode == 13 ?
		((t_screen*)(mas[4]))->max_i - ((t_screen*)(mas[4]))->min_i :
		-(((t_screen*)(mas[4]))->max_i - ((t_screen*)(mas[4]))->min_i)) * 0.1;
		((t_screen*)(mas[4]))->max_i += diff;
		((t_screen*)(mas[4]))->min_i += diff;
	}
}

int		manage_key(int keycode, void *param)
{
	void			**mas;

	mas = (void**)param;
	if (keycode == 53 || keycode == 0 ||
	keycode == 2 || keycode == 1 || keycode == 13)
		keys(keycode, param, mas);
	else if (keycode == 24 ||
	(keycode == 27 && ((t_screen*)(mas[4]))->iter > 5))
		((t_screen*)(mas[4]))->iter += keycode == 27 ? -5 : 5;
	else if (keycode == 8 ||
	(keycode == 7 && ((t_screen*)(mas[4]))->rgb_col > 200))
		((t_screen*)(mas[4]))->rgb_col += keycode == 7 ? -200 : 200;
	else if (keycode == 49)
		((t_screen*)(mas[4]))->space = !(((t_screen*)(mas[4]))->space);
	else if (keycode == 6)
		((t_screen*)(mas[4]))->colors = !(((t_screen*)(mas[4]))->colors);
	else if ((keycode >= 18 && keycode <= 21) || keycode == 23 ||
	keycode == 22 || keycode == 26)
		another_fractal(keycode, mas);
	else
		return (0);
	draw_fractal(mas, mas[2]);
	return (0);
}

int		manage_move(int x, int y, void *param)
{
	void	**mas;

	mas = (void**)param;
	if ((((t_screen*)(mas[4]))->fract == 3 ||
	((t_screen*)(mas[4]))->fract == 4 ||
	((t_screen*)(mas[4]))->fract == 5 ||
	((t_screen*)(mas[4]))->fract == 6) && ((t_screen*)(mas[4]))->space == 1)
	{
		((t_screen*)(mas[4]))->jul_im = (y - WIN_Y / 2) * 0.002;
		((t_screen*)(mas[4]))->jul_re = (x - WIN_X / 2) * 0.002;
		draw_fractal(mas, mas[2]);
	}
	return (0);
}
