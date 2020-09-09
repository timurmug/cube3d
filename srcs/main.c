/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 10:03:29 by qtamaril          #+#    #+#             */
/*   Updated: 2020/09/09 17:34:51 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		key_press(int key, t_sets *sets)
{
	if (key == 53)
		mlx_destroy_window(sets->mlx, sets->wdw);
	else if (key == 123)
		ft_putendl_fd("left", 1);
	else if (key == 124)
		ft_putendl_fd("rigth", 1);
	else if (key == 13)
		ft_putendl_fd("W", 1);
	else if (key == 1)
		ft_putendl_fd("S", 1);
	else if (key == 0)
		ft_putendl_fd("A", 1);
	else if (key == 2)
		ft_putendl_fd("D", 1);
	return (0);
}

void	create_window(char **map)
{
	t_sets	sets;

	// получает разрешение экрана компа
	// mlx_get_screen_size(sets.mlx, &width_screen, &height_screen);
	sets.mlx = NULL;
	sets.wdw = NULL;
	sets.mlx = mlx_init();
	sets.wdw = mlx_new_window(sets.mlx, 2560, 1440, "cub3d");
	draw_2dmap(map, sets);
	mlx_key_hook(sets.wdw, key_press, &sets);
	mlx_loop(sets.mlx);
}

void	create_map(t_list **lines_list, int size)
{
	char		**map;
	int			i;
	t_list		*tmp;

	map = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	tmp = *lines_list;
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	i = 18;
	while (map[++i])
		ft_putendl_fd(map[i], 1);
	create_window(map);
}

int		main(int ac, char **av)
{
	int			fd;
	char		*line;
	t_list		*lines_list;

	fd = open(av[1], O_RDONLY);
	line = NULL;
	lines_list = NULL;
	if (ac == 2)
	{
		while (get_next_line(fd, &line))
			ft_lstadd_back(&lines_list, ft_lstnew(line));
		ft_lstadd_back(&lines_list, ft_lstnew(line));
		create_map(&lines_list, ft_lstsize(lines_list));
	}
	return (0);
}