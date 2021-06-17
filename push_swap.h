/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:11:13 by egomez-a          #+#    #+#             */
/*   Updated: 2021/06/07 18:00:44 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_stack
{
	int				num;
	struct s_stack	*next;
}					t_stack;

t_stack				*create_node(void);
t_stack				*copy_args_in_stack(int argc, char **argv);
int					check_duplicates(t_stack **stack);
void				swap(int *a, int *b);
int					sa_sb(t_stack **head);
int					pa_pb(t_stack **head_from, t_stack **head_to);
int					ra_rb(t_stack **head);
int					rra_rrb(t_stack **head);
int					ss(t_stack **stack_a, t_stack **stack_b);
int					rr(t_stack **stack_a, t_stack **stack_b);
int					rrr(t_stack **stack_a, t_stack **stack_b);
int					s_len(t_stack *stack);

t_stack				*create_node(void);
void				delete_stack(t_stack **stack);
int					*create_array_from_stack(t_stack *stack, int len);
int					find_mid_value(t_stack *stack, int len);
int					main(int argc, char **argv);

int					check_int_overflow(char *str);

int					ft_atoi(const char *str);

#endif
