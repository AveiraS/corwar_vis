/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:30:27 by sscarecr          #+#    #+#             */
/*   Updated: 2020/05/11 19:29:14 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All basic output messages and dump.
*/

#ifdef _WIN32
# include <stdio.h>
#endif
#include <unistd.h>
#include "../include/corewar.h"

void		introduce(t_vm *vm)
{
	unsigned	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < vm->num_players)
	{
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
		i + 1, vm->players[i].header.prog_size, vm->players[i].header.prog_name,
		vm->players[i].header.comment);
		++i;
	}
}

void		declare_winner(t_vm *vm)
{
	ft_printf(COPYCAT ? "Contestant %u, \"%s\", has won !\n" :
	"Player %u (%s) won\n",
	vm->last_alive, vm->players[vm->last_alive - 1].header.prog_name);
}

void		print_movement(t_battlefield *arena, int pc, int n)
{
	char	line[7 + 3 * REG_SIZE * MAX_ARGS_NUMBER];
	t_byte	t;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < n)
	{
		t = arena[(pc + i) % MEM_SIZE].code;
		line[j++] = (t / 16 > 9 ? t / 16 - 10 + 'a' : t / 16 + '0');
		line[j++] = (t % 16 > 9 ? t % 16 - 10 + 'a' : t % 16 + '0');
		line[j++] = ' ';
		++i;
	}
	line[j] = '\0';
	ft_printf("ADV %d (0x%04x -> 0x%04x) %s\n", n, pc, pc + n, line);
}

int			dump(t_vm *vm)
{
	int	i;
	int	print_bytes;

	print_bytes = 0;
	i = -1;
	ft_printf("0x%04x : ", print_bytes);
	while (++i < MEM_SIZE)
	{
		if (print_bytes % LONG_DUMP == 0 && print_bytes != 0)
			ft_printf("\n0x%04x : ", print_bytes);
		else
			ft_printf("%02hhx ", vm->arena[i].code);
		print_bytes++;
	}
	write(1, "\n", 1);
	return (0);
}
