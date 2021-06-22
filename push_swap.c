/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:04:47 by egomez-a          #+#    #+#             */
/*   Updated: 2021/06/17 12:08:04 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(const char *str)
{
	int	signo;
	int	n;

	n = 0;
	signo = 1;
	while ((*str == ' ') || ((*str >= 9) && (*str <= 13)))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			signo = -1;
		str++;
	}
	if ((*str == '-') || (*str == '+'))
		return (0);
	while ((*str >= '0') && (*str <= '9'))
	{
		n = n * 10;
		n = n + (int)(*str - 48);
		str++;
	}
	n = n * signo;
	return (n);
}

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		sa_sb(t_stack **stack_ab)
{
	t_stack	*stack;

	stack = *stack_ab;
	if (stack && stack->next)
		swap(&stack->num, &stack->next->num);
	return (0);
}

int		ss(t_stack **stack_a, t_stack **stack_b)
{
	sa_sb(stack_a);
	sa_sb(stack_b);
	return (0);
}

int		pa_pb(t_stack **head_from, t_stack **head_to)
{
	t_stack	*temp;
	t_stack *stack_from;
	t_stack *stack_to;

	stack_from = *head_from;
	stack_to = *head_to;
	if (!stack_from)
		return (0);
	temp = stack_from;
	stack_from = stack_from->next;
	*head_from = stack_from;
	if (!stack_to)
	{
		stack_to = temp;
		stack_to->next = NULL;
		*head_to = stack_to;
	}
	else
	{
		temp->next = stack_to;
		*head_to = temp;
	}
	return (0);	
}

int 	ra_rb(t_stack **stack_ab)
{
	t_stack	*temptop;
	t_stack	*templast;
	t_stack *stack;

	stack = *stack_ab;
	if (!(stack && stack->next))
		return (0);
	temptop = stack;
	stack = stack->next;
	templast = stack;
	while (templast->next)
		templast = templast->next;
	templast->next = temptop;
	temptop->next = NULL;
	*stack_ab = stack;
	return (0);
}

int		rra_rrb(t_stack **stack_ab)
{
	t_stack	*templast;
	t_stack	*previous;
	t_stack *stack;

	stack = *stack_ab;
	if (!(stack && stack->next))
		return (0);
	templast = stack;
	while (templast->next)
	{
		previous = templast;
		templast = templast->next;
	}
	templast->next = stack;
	previous->next = NULL;
	*stack_ab = templast;
	return (0);
}

int		rr(t_stack **stack_a, t_stack **stack_b)
{
	ra_rb(stack_a);
	ra_rb(stack_b);
	return (0);
}
	
int		rrr(t_stack **stack_a, t_stack **stack_b)
{
	rra_rrb(stack_a);
	rra_rrb(stack_b);
	return (0);
}

int		s_len(t_stack *stack)
{
	int 	len;
	t_stack	*tmp;

	len = 0;
	tmp = stack;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

t_stack	*create_node(void)
{
	t_stack	*first;

	first = (t_stack *)malloc(sizeof(t_stack));
	first->num = 0;
	first->next = NULL;
	return (first);
}

int		*create_array_from_stack(t_stack *stack, int len)
{
	int	*array;
	int	i;

	array = (int *)malloc(sizeof(int) * len);
	i = 0; 
	while (i < len)
	{
		array[i] = stack->num;
		stack = stack->next;
		i++;
	}
	return (array);
}

void	delete_stack(t_stack **stack)
{
	t_stack	*del;
	t_stack *temp;

	temp = *stack;
	while (temp)
	{
		del = temp;
		temp = temp->next;
		free(del);
	}
	*stack = NULL;
}

void	printarray(t_stack **stack)
{
	int i;
	int l;
	int *matrix;

	i = 0;
	l = s_len(*stack);
	matrix = create_array_from_stack(*stack, l);
	while (i < l)
	{
		printf("el termino %d del array es %d \n", i, matrix[i]);
		i++;
	}
	free (matrix);
	return; 
}

int 	check_duplicates(t_stack **stack)
{
	int i;
	int j;
	int len; 
	int *array;

	printarray(stack);
	i = 0;
	while (i < len)
	{
		j = 1 + i;
		while (j < len)
		{
			if (array[i] == array[j])
			{
				printf("Duplicates terms %d %d \n", i, j);
				delete_stack(stack);
				free(array);
				return (0);
			}
			j++;
		}
		i++;
	}
	free(array);
	return (1);
}

t_stack	*copy_args_in_stack(int argc, char **argv)
{
	int i;
	t_stack	*first;
	t_stack	*tmp;

	i = 1;
	first = create_node();
	tmp = first;
	while (i < argc)
	{
		tmp->num = ft_atoi(argv[i]);
		if (i < argc - 1)
		{
			tmp->next = create_node();
			tmp = tmp->next;
		}
		i++;
	}
	check_duplicates(&first);
	return(first);
}

void	orderthree(t_stack **stack)
{
	int i;
	int len; 

	len = s_len(*stack);
	if (len == 1)
		return ;
	else if (len == 2 && (*stack)->num > (*stack)->next->num)
	{
		write(2, "sa\n", 3);
		sa_sb(stack);
		return ;
	}
	else if ((*stack)->num > (*stack)->next->num && (*stack)->next->num >
		(*stack)->next->next->num && (*stack)->next->next->num < (*stack)->num)
	{
		write(2, "sa\n", 3);
		sa_sb(stack);
		write(2, "rra\n", 4);
		rra_rrb(stack);
	}
	else if((*stack)->num > (*stack)->next->num && (*stack)->next->num <
		(*stack)->next->next->num && (*stack)->next->next->num < (*stack)->num)
	{
		write(2, "ra\n", 3);
		ra_rb(stack);
	}
	else if((*stack)->num > (*stack)->next->num && (*stack)->next->num <
		(*stack)->next->next->num && (*stack)->next->next->num > (*stack)->num)
	{
		write(2, "sa\n", 3);
		sa_sb(stack);
	}
	else if((*stack)->num < (*stack)->next->num && (*stack)->next->num >
		(*stack)->next->next->num && (*stack)->next->next->num > (*stack)->num)
	{
		write(2, "sa\n", 3);
		sa_sb(stack);
		write(2, "ra\n", 3);
		ra_rb(stack);
	}
	else if((*stack)->num < (*stack)->next->num && (*stack)->next->num >
		(*stack)->next->next->num && (*stack)->next->next->num < (*stack)->num)
	{
		write(2, "rra\n", 4);
		rra_rrb(stack);
	}
	return;
}

void	orderlow(t_stack **stack)
{
	int i;
	int len; 
	int *array;

	len = s_len(*stack);
	if (len == 1)
		return ;
	else if (len == 2 && (*stack)->num > (*stack)->next->num)
	{
		write(2, "sa\n", 3);
		sa_sb(stack);
	}
	else if (len == 3)
		orderthree(stack);
	printarray(stack);
	return;
}
   
int mid_insertionSort(int *array, int n) 
{ 
	int i;
	int j;
	int element;
	int	midpoint;
 
	i = 1;
	while (i < n)
	{ 
		element = array[i]; 
		j = i - 1;
		while (j >= 0 && array[j] > element) 
		{ 
			array[j + 1] = array[j]; 
            j = j - 1; 
        } 
        array[j + 1] = element;
		i++;
    }
	midpoint = array[(n/2)];
	printf("El midpoint del array es %d\n", midpoint);
	return(midpoint);
}

int	movechunk(t_stack **stack_a, t_stack **stack_b, int midpoint)
{
	t_stack *stacktemp;

	int i;
	int len;
	int *array;
	
	printf("stack a\n");
	printarray(stack_a);
	if ((*stack_a)->num < midpoint)
	{
		while ((*stack_a)->num < midpoint)
		{
			pa_pb(stack_a, stack_b);
			printf("pa\n");
			(*stack_a) = (*stack_a)->next;
		}
	}
	printf("stack_a\n");
	printarray(stack_a);
	printf("stack_b\n");
	printarray(stack_b);
	if ((*stack_a)->num >= midpoint)
	{
		stacktemp = (*stack_a);
		while(stacktemp->next)
			stacktemp = stacktemp->next;
		if (stacktemp->num < midpoint)
			while (stacktemp->num < midpoint)
			{
				rra_rrb(stack_a);
				printf("rra\n");
				pa_pb(stack_a, stack_b);
				printf("pa\n");
			}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int	len;
	int midpoint;

	if (!(stack_a = copy_args_in_stack(argc, argv)))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	len = s_len(stack_a);
	printf("El numero de terminos es %d", len);
	stack_b = NULL;
	printf("El stack original es: \n");
	printarray(&stack_a);
	if (len <= 4)
		orderlow(&stack_a);
	else if (len > 4)
		movechunk(&stack_a, &stack_b, midpoint);
	return (0);
}
