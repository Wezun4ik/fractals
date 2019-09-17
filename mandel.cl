struct RGB
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct HSV
{
	double H;
	double S;
	double V;
};

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_point;

typedef struct	s_screen
{
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
	int			iter;
	int			fr_col;
	int			rgb_col;
	int			fract;
	double		jul_im;
	double		jul_re;
	int			space;
	int			colors;
}				t_screen;

struct RGB HSVToRGB(struct HSV hsv) {
	double r = 0, g = 0, b = 0;

	if (hsv.S == 0)
	{
		r = hsv.V;
		g = hsv.V;
		b = hsv.V;
	}
	else
	{
		int i;
		double f, p, q, t;

		if (hsv.H == 360)
			hsv.H = 0;
		else
			hsv.H = hsv.H / 60;

		i = (int)trunc(hsv.H);
		f = hsv.H - i;

		p = hsv.V * (1.0 - hsv.S);
		q = hsv.V * (1.0 - (hsv.S * f));
		t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

		switch (i)
		{
		case 0:
			r = hsv.V;
			g = t;
			b = p;
			break;

		case 1:
			r = q;
			g = hsv.V;
			b = p;
			break;

		case 2:
			r = p;
			g = hsv.V;
			b = t;
			break;

		case 3:
			r = p;
			g = q;
			b = hsv.V;
			break;

		case 4:
			r = t;
			g = p;
			b = hsv.V;
			break;

		default:
			r = hsv.V;
			g = p;
			b = q;
			break;
		}

	}

	struct RGB rgb;
	rgb.R = r * 255;
	rgb.G = g * 255;
	rgb.B = b * 255;

	return rgb;
}

int		get_color(int iter, t_screen *scr, double rng)
{
	struct HSV		col;
	struct RGB		ret_col;
	unsigned int c;

	if (iter == scr->iter)
		return (scr->fr_col);
	if (scr->colors)
	{
	iter = iter + 1 - log(log(rng));
	col.H = (180 * ((double)iter) + scr->rgb_col) / scr->iter;
	col.S = 1;
	col.V = 1;
	ret_col = HSVToRGB(col);
	}
	else
	{
		ret_col.R = (unsigned char)(sin(0.016 * iter + 4) * 230 + 25) * scr->rgb_col;
		ret_col.G = (unsigned char)(sin(0.013 * iter + 2) * 230 + 25) * scr->rgb_col;
		ret_col.B = (unsigned char)(sin(0.01 * iter + 1) * 230 + 25) * scr->rgb_col;
	}
	c = (ret_col.R << 16) + (ret_col.G << 8) + ret_col.B;
	return (c);
}

void	put_mandel(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
{
	int			x;
	int			y;
	int			iter;
	double		step_i;
	double		step_r;
	double		res_i;
	double		res_r;
	double		r;
	double		i;
	double		dbl_i;
	t_point		point;

    x = get_global_id(0);
    y = get_global_id(1);
	step_i = (scr.max_i - scr.min_i) / WIN_Y;
	step_r = (scr.max_r - scr.min_r) / WIN_X;
	iter = -1;
	i = scr.max_i - step_i * y;
	r = scr.min_r + step_r * x;
	res_i = 0;
	res_r = 0;
	point.x = x; 
	point.y = WIN_Y - y;
	while (++iter < scr.iter)
	{
		dbl_i = res_i;
		res_i = res_i * res_r * 2 + i;
		res_r = res_r * res_r - dbl_i * dbl_i + r;
		if (res_i * res_i + res_r * res_r > 4)
			break;
	}
	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
	res[WIN_X * (WIN_Y - y) + x] = point.color;
}

void	put_spider(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
{
	int			x;
	int			y;
	int			iter;
	double		step_i;
	double		step_r;
	double		res_i;
	double		res_r;
	double		r;
	double		i;
	double		dbl_i;
	t_point		point;

    x = get_global_id(0);
    y = get_global_id(1);
	step_i = (scr.max_i - scr.min_i) / WIN_Y;
	step_r = (scr.max_r - scr.min_r) / WIN_X;
	iter = -1;
	i = scr.max_i - step_i * y;
	r = scr.min_r + step_r * x;
	res_i = 0;
	res_r = 0;
	point.x = x; 
	point.y = WIN_Y - y;
	while (++iter < scr.iter)
	{
		dbl_i = res_i;
		res_i = res_i * res_r * 2 + i;
		res_r = res_r * res_r - dbl_i * dbl_i + r;
		i = i / 2 + res_i;
		r = r / 2 + res_r;
		if (res_i * res_i + res_r * res_r > 4)
			break;
	}
	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
	res[WIN_X * (WIN_Y - y) + x] = point.color;
}

void	put_burning(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
{
	int			x;
	int			y;
	int			iter;
	double		step_i;
	double		step_r;
	double		res_i;
	double		res_r;
	double		r;
	double		i;
	double		dbl_i;
	t_point		point;

    x = get_global_id(0);
    y = get_global_id(1);
	step_i = (scr.max_i - scr.min_i) / WIN_Y;
	step_r = (scr.max_r - scr.min_r) / WIN_X;
	iter = -1;
	i = scr.max_i - step_i * y; 
	r = scr.min_r + step_r * x;
	res_i = 0;
	res_r = 0;
	point.x = x; 
	point.y = WIN_Y - y;
	while (++iter < scr.iter)
	{
		dbl_i = res_i > 0 ? res_i : -res_i;
		res_i = dbl_i;
		res_r = res_r > 0 ? res_r : -res_r;
		res_i = res_i * res_r * 2 + i;
		res_r = res_r * res_r - dbl_i * dbl_i + r;
		if (res_i * res_i + res_r * res_r > 4)
			break;
	}
	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
	res[WIN_X * (WIN_Y - y) + x] = point.color;
}

void	put_julia(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
{
	int			x;
	int			y;
	int			iter;
	double		step_i;
	double		step_r;
	double		res_i;
	double		res_r;
	double		r;
	double		i;
	double		dbl_i;
	t_point		point;

    x = get_global_id(0);
    y = get_global_id(1);
	step_i = (scr.max_i - scr.min_i) / WIN_Y;
	step_r = (scr.max_r - scr.min_r) / WIN_X;
	iter = -1;
	i = scr.jul_im; 
	r = scr.jul_re;
	res_i = scr.max_i - step_i * y;
	res_r = scr.min_r + step_r * x;
	point.x = x; 
	point.y = WIN_Y - y;
	while (++iter < scr.iter)
	{
		dbl_i = res_i;
		res_i = res_i * res_r * 2 + i;
		res_r = res_r * res_r - dbl_i * dbl_i + r;
		if (res_i * res_i + res_r * res_r > 4)
			break;
	}
	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
	res[WIN_X * (WIN_Y - y) + x] = point.color;
}

void	put_xernya(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
{
	int			x;
	int			y;
	int			iter;
	double		step_i;
	double		step_r;
	double		res_i;
	double		res_r;
	double		r;
	double		i;
	double		dbl_i;
	t_point		point;

    x = get_global_id(0);
    y = get_global_id(1);
	step_i = (scr.max_i - scr.min_i) / WIN_Y;
	step_r = (scr.max_r - scr.min_r) / WIN_X;
	i = scr.jul_im;
	r = scr.jul_re;
	res_i = scr.max_i - step_i * y;
	res_r = scr.min_r + step_r * x;
	point.x = x; 
	point.y = WIN_Y - y;
	iter = -1;
	while (++iter < scr.iter)
	{
		dbl_i = res_i;
		res_i = 3 * res_r * res_i * res_r - res_i * res_i * res_i + i;
		res_r = res_r * res_r * res_r - 3 * dbl_i * dbl_i * res_r + r - 1;
		if (fabs(res_r) > 50 && fabs(res_i) > 2500)
			break;
	}
	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
	res[WIN_X * (WIN_Y - y) + x] = point.color;
}

void	put_antimandel(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
{
	int			x;
	int			y;
	int			iter;
	double		step_i;
	double		step_r;
	double		res_i;
	double		res_r;
	double		r;
	double		i;
	double		dbl_i;
	double		disk;
	t_point		point;

    x = get_global_id(0);
    y = get_global_id(1);
	step_i = (scr.max_i - scr.min_i) / WIN_Y;
	step_r = (scr.max_r - scr.min_r) / WIN_X;
	iter = -1;
	i = scr.jul_im;
	r = scr.jul_re;
	res_i = scr.max_i - step_i * y;
	res_r = scr.min_r + step_r * x;
	point.x = x; 
	point.y = WIN_Y - y;
	while (res_i * res_i + res_r * res_r < log((double)scr.iter) && ++iter < scr.iter)
	{
		dbl_i = res_i;
		disk = res_r * res_r * res_r * res_r + 2 * res_r * res_r * res_i * res_i + res_i * res_i * res_i * res_i;
		if (disk == 0)
			break;
		res_i = (-2 * res_r * res_i) / (disk) + i;
		res_r = (res_r * res_r - dbl_i * dbl_i) / (disk) + r;
	}
	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
	res[WIN_X * (WIN_Y - y) + x] = point.color;
}

double	div_i(double a, double b, double c, double d)
{
	return ((b * c - a * d) / (c * c + d * d));
}
double	div_r(double a, double b, double c, double d)
{
	return ((a * c + b * d) / (c * c + d * d));
}

// void	put_solaria(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
// {
// 	int			x;
// 	int			y;
// 	int			iter;
// 	double		step_i;
// 	double		step_r;
// 	double		res_i;
// 	double		res_r;
// 	double		r;
// 	double		i;
// 	double		dbl_i;
// 	t_point		point;

//     x = get_global_id(0);
//     y = get_global_id(1);
// 	step_i = (scr.max_i - scr.min_i) / WIN_Y;
// 	step_r = (scr.max_r - scr.min_r) / WIN_X;
// 	iter = -1;
// 	i = scr.jul_im; 
// 	r = scr.jul_re;
// 	res_i = scr.max_i - step_i * y;
// 	res_r = scr.min_r + step_r * x;
// 	point.x = x; 
// 	point.y = WIN_Y - y;
// 	while (++iter < scr.iter)
// 	{
// 		dbl_i = res_i;
// 		res_i = res_i * res_r * 2 + i;
// 		res_r = res_r * res_r - dbl_i * dbl_i + r;
// 		if (res_i * res_i + res_r * res_r < 4)
// 			break;
// 	}
// 	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
// 	res[WIN_X * (WIN_Y - y) + x] = point.color;
// }

void	put_graphself(t_screen scr, int WIN_X, int WIN_Y, __global int *res)
{
	int			x;
	int			y;
	int			iter;
	double		step_i;
	double		step_r;
	double		res_i;
	double		res_r;
	double		dbl_i;
	// double		a;
	// double		b;
	// double		c;
	// double		d;
	t_point		point;

    x = get_global_id(0);
    y = get_global_id(1);
	step_i = (scr.max_i - scr.min_i) / WIN_Y;
	step_r = (scr.max_r - scr.min_r) / WIN_X;
	iter = -1;
	// a = scr.jul_re; 
	// b = scr.jul_im;
	// c = -1;
	// d = (b * c + 1) / a;
	res_i = scr.max_i - step_i * y;
	res_r = scr.min_r + step_r * x;
	point.x = x; 
	point.y = WIN_Y - y;
	while (++iter < scr.iter)
	{
		dbl_i = res_i;
		res_i = 2 * res_r * res_i - scr.jul_re * scr.jul_im * div_i(res_r * res_r - res_i * res_i, 2 * res_i * res_r, 2 * res_r, 2 * res_i);
		res_r =res_r * res_r - dbl_i * dbl_i - scr.jul_re * scr.jul_im * div_r(res_r * res_r - dbl_i * dbl_i, 2 * dbl_i * res_r, 2 * res_r, 2 * dbl_i);
		if (res_i * res_i + res_r * res_r < 0.0000000001)
			break;
	}
	point.color = get_color(iter, &scr, res_i * res_i + res_r * res_r);
	res[WIN_X * (WIN_Y - y) + x] = point.color;
}


__kernel void	fractal(t_screen scr, int WIN_X, int WIN_Y, __global int *res, int fractal)
{
	if (fractal == 1)
		put_mandel(scr, WIN_X, WIN_Y, res);
	else if (fractal == 3)
		put_julia(scr, WIN_X, WIN_Y, res);
	else if (fractal == 2)
		put_burning(scr, WIN_X, WIN_Y, res);
	else if (fractal == 4)
		put_xernya(scr, WIN_X, WIN_Y, res);
	else if (fractal == 5)
		put_antimandel(scr, WIN_X, WIN_Y, res);
	else if (fractal == 6)
		put_graphself(scr, WIN_X, WIN_Y, res);
	else if (fractal == 7)
		put_spider(scr, WIN_X, WIN_Y, res);
}