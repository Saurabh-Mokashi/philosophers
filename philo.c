/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokashi <smokashi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:38:27 by smokashi          #+#    #+#             */
/*   Updated: 2023/03/01 13:38:27 by smokashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct pinfo
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int freq;
}   s_info;

void* rout()
{
    printf("\n\nhello world!!!!\n\n");
    // write(1,"hhh",3);
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	num;

	sign = 1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n' \
			||*str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (num > 2147483647 && sign == 1)
		return (-1);
	if (num > 2147483648 && sign == -1)
		return (0);
	return (num * sign);
}

int errcheck(int ac, char **agv)
{
    int i;
    int num;

    i = 1;
    if (ac <= 4 || ac >= 7)
        return (1);
    while (i < ac)
    {
        num = ft_atoi(agv[i]);
        if(num < 0)
            return (1);
        i++;
    }
    return (0);
}

int main(int ac, char **agv)
{
    s_info *s;

    if(errcheck(ac,agv))
    {
        printf("error\n");
        return (0);
    }
    s = malloc(sizeof(s_info));
    s->num_of_philo = ft_atoi(agv[1]);
    s->time_to_die = ft_atoi(agv[2]);
    s->time_to_eat = ft_atoi(agv[3]);
    s->time_to_sleep = ft_atoi(agv[4]);
    if(ac == 6)
        s->freq = ft_atoi(agv[5]);
    
    return (0);
    
}