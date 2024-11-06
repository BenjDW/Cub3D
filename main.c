/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:12:05 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/06 07:35:48 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_chrcub(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i > 4)
	{
		i--;
		if (str[i] == 'b')
			i--;
		if (str[i] == 'u')
			i--;
		if (str[i] == 'c')
			i--;
		if (str[i] == '.')
			return (0);
	}
	return (1);
}

int	verif_arg(char	**argv)
{
	int	fd;

	if (ft_chrcub(argv[1]) == 1)
		return (printf("need file in .cub\n"), 1);
	fd = open(argv, O_WRONLY, 777);
	if (fd = -1)
		return (printf("file not fund\n"), 1);
	
}

int	parsing(int argc, char **argv)
{
	if (argc != 2 || verif_arg((argv + 1)) == 1 || verif_map() == 1)
		return (1);
}

int	main(int argc, char **argv)
{
	data	*data;

	if (parsing(argc, argv) == 1)
		return (1);

}
