/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:48:38 by sbrella           #+#    #+#             */
/*   Updated: 2019/08/28 18:52:48 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				read_source_file(t_cl_str *params)
{
	FILE			*fp;
	const char		filename[] = "./mandel.cl";
	size_t			source_size;
	char			*source_str;
	int				ret;

	fp = fopen(filename, "r");
	if (!fp)
		exit(1);
	source_str = (char *)malloc(50000);
	source_size = fread(source_str, 1, 50000, fp);
	fclose(fp);
	params->program = clCreateProgramWithSource(params->context, 1,
	(const char **)&source_str, (const size_t *)&source_size, &ret);
	if (!params->program)
		exit(0);
	ret = clBuildProgram(params->program, 1,
	&(params->device), NULL, NULL, NULL);
	params->kernel = clCreateKernel(params->program, "fractal", &ret);
	free(source_str);
}

int					prepare_cl(t_cl_str *params)
{
	cl_platform_id	platf;
	cl_uint			num_platforms;
	cl_uint			dev;
	int				ret;

	ret = clGetPlatformIDs(1, &platf, &num_platforms);
	ret = clGetDeviceIDs(platf, CL_DEVICE_TYPE_DEFAULT,
	1, &(params->device), &dev);
	(params->context) = clCreateContext(NULL,
	1, &(params->device), NULL, NULL, &ret);
	if (ret < 0)
		exit(0);
	(params->queue) = clCreateCommandQueue(params->context,
	params->device, 0, &ret);
	if (ret < 0)
		exit(0);
	read_source_file(params);
	return (1);
}

void				paint_fractal(t_cl_str *cl_params, char *image, void **mas)
{
	cl_mem			memobj;
	int				ret;
	int				xy[2];
	int				arg;
	size_t			global_work_size[2];

	global_work_size[0] = WIN_X;
	global_work_size[1] = WIN_Y;
	xy[0] = WIN_X;
	xy[1] = WIN_Y;
	memobj = clCreateBuffer(cl_params->context,
	CL_MEM_READ_WRITE, WIN_X * WIN_Y * 4, NULL, &ret);
	ret = clSetKernelArg(cl_params->kernel, 0, sizeof(t_screen), mas[4]);
	ret = clSetKernelArg(cl_params->kernel, 1, sizeof(int), (void*)(&xy[0]));
	ret = clSetKernelArg(cl_params->kernel, 2, sizeof(int), (void*)(&xy[1]));
	ret = clSetKernelArg(cl_params->kernel, 3, sizeof(char*), (void*)(&memobj));
	arg = (((t_screen*)(mas[4]))->fract > 7) ? 2 : ((t_screen*)(mas[4]))->fract;
	ret = clSetKernelArg(cl_params->kernel, 4, sizeof(int), (void*)(&arg));
	ret = clEnqueueNDRangeKernel(cl_params->queue,
	cl_params->kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(cl_params->queue, memobj,
	CL_FALSE, 0, WIN_X * WIN_Y * 4, image, 0, NULL, NULL);
	clFinish(cl_params->queue);
	clReleaseMemObject(memobj);
}
