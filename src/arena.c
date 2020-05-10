/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:22:33 by sscarecr          #+#    #+#             */
/*   Updated: 2020/05/10 16:49:58 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All arena read and write operations.
** NB: Arena is big-endian!
*/

#include "../include/corewar.h"

static t_process	*new_process(t_process *next, unsigned num,
	unsigned player_num, int pc)
{
	t_process	*p;

	if (!(p = (t_process*)ft_memalloc(sizeof(t_process))))
		sys_error(NULL);
	p->next = next;
	p->player_num = player_num;
	p->color = choose_color_char(player_num);
	p->num = num;
	p->pc = pc;
	return (p);
}

/*
** Place champions' code in the arena and create initial processes.
*/

void				init_arena(t_vm *vm)
{
	unsigned	i;
	unsigned	j;
	int			step;
	int			byte;
	int			temp;
	int			diff;

	diff = temp = step = MEM_SIZE / vm->num_players;
	i = -1;
	byte = 0;
	vm->amount_of_checks = 0;
	vm->vis_quit = 0;
	vm->vis_pause = 0;
	while (++i < vm->num_players)
	{
		vm->start = new_process(vm->start, ++vm->num_process,
		vm->players[i].num - 1, i * step);
		vm->arena[byte].cursor = 1;
		vm->start->reg[0] = -(i + 1);
		j = -1;
		while (++j < vm->players[i].header.prog_size)
		{
			vm->arena[byte].code = vm->players[i].code[j];
			vm->arena[byte].write_cycles = 0;
			choose_color(&vm->arena[byte], i);
			byte++;
		}
		while (byte < diff && byte < MEM_SIZE)
		{
			vm->arena[byte].color_b = 111;
			vm->arena[byte].color_g = 111;
			vm->arena[byte].color_r = 111;
			vm->arena[byte].code = 0x0;
			vm->arena[byte].color = 'n';
			vm->arena[byte].write_cycles = 0;
			byte++;
		}
		diff += temp;
		free(vm->players[i].code);
	}
}

/*
** Read an argument of T_DIR type.
*/

int					read_dir(int start, t_battlefield *arena)
{
	char	s[DIR_SIZE];
	int		i;

	start = cut(start);
	i = -1;
	while (++i < DIR_SIZE)
		s[DIR_SIZE - 1 - i] = arena[(start + i) % MEM_SIZE].code;
	return (*((int*)s));
}

/*
** Read an argument of T_IND type.
*/

int					read_ind(int start, t_battlefield *arena)
{
	char	s[IND_SIZE];
	int		i;

	start = cut(start);
	i = -1;
	while (++i < IND_SIZE)
		s[IND_SIZE - 1 - i] = arena[(start + i) % MEM_SIZE].code;
	return (*((short*)s));
}

/*
** Write an argument to the arena.
*/

void				write_bytes(int n, int start, t_battlefield *arena, char color)
{
	t_byte	*s;
	int		i;

	start = cut(start);
	s = (t_byte*)&n;
	i = -1;
	while (++i < REG_SIZE)
	{
		arena[(start + i) % MEM_SIZE].code = s[REG_SIZE - 1 - i];
		arena[(start + i) % MEM_SIZE].color = color;
		arena[(start + i) % MEM_SIZE].write_cycles = 100;
		choose_reverse_color(&arena[(start + i) % MEM_SIZE]);
	}
}
