static int	header(t_struct_m *main, int fd)
{
	char	s[54];
	int		width;
	int		y;

	ft_bzero(s, 54);
	s[0] = 0x42;
	s[1] = 0x4D;
	width = main->place.s_width;
	y = 0;
	while ((3 * width + y) % 4 != 0)
		y++;
	s[2] = 3 * (width + y) * main->place.s_height + 54;
	s[10] = 54;
	s[14] = 40;
	ft_memcpy(s + 18, &main->place.s_width, 4);
	ft_memcpy(s + 22, &main->place.s_height, 4);
	s[26] = 1;
	s[28] = 24;
	write(fd, s, 54);
	return (y);
}

static void	image(t_struct_m *main)
{
	main->img.img = mlx_new_image(main->vars.mlx, main->place.s_width, main->place.s_height);
	if (!img->img)
	{
		main->place.error_c = 24;//right
		ft_error(main);
	}
	main->img.addr = mlx_get_data_addr(main->img.img, &main->img.bits_per_pixel, &main->img.line_length,
                                 &main->img.endian);
	set_value_texture(main);
	ft_putstr("done, start drawing screenshot");
	render_next_frame_structure(main);
}

void		bmp(t_struct_m *main)
{
	int			fd;
	char		*clr;
	int			y;

	image(main);
	fd = open("screen.bmp", O_RDWR | O_CREAT, 0666);
	y = header(main, fd);
	c.y = main->place.s_height - 1;
	while (c.y >= 0)
	{
		c.x = 0;
		while (c.x < main->place.s_width)
		{
			clr = (img.addr + (c.y * img.line_length + c.x * (img.bpp / 8)));
			write(fd, clr, 3);
			c.x++;
		}
		write(fd, "\0\0\0", y);
		c.y--;
	}
	close(fd);
}