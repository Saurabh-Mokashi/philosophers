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
    int id;
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int freq;
    pthread_t thread;
    pthread_mutex_t lfork;
    pthread_mutex_t rfork;

}   s_info;

void* rout(void *s)
{
    printf("\n\nhello world and id is %d!!!!\n\n",s->id);
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
    int     i;

    if(errcheck(ac,agv))
    {
        printf("error\n");
        return (0);
    }
    i = 0;
    s = malloc(sizeof(s_info) * ft_atoi(agv[1]));
    while (i < ft_atoi(agv[1]))
    {
        s[i].num_of_philo = ft_atoi(agv[1]);
        s[i].time_to_die = ft_atoi(agv[2]);
        s[i].time_to_eat = ft_atoi(agv[3]);
        s[i].time_to_sleep = ft_atoi(agv[4]);
        s[i].id = i+1;
        pthread_mutex_init(&s[i].lfork,NULL);
        pthread_mutex_init(&s[i].rfork,NULL);
        if(ac == 6)
            s[i].freq = ft_atoi(agv[5]);
        else
            s[i].freq=-1;
        i++;
    }
    i = 0;
    // printf("agv[1] val %d\n",ft_atoi(agv[1]));
    // while(i<ft_atoi(agv[1]))
    // {
    //     printf("id is %d\n",s[i].id);
    //     i++;
    // }
    while(i<ft_atoi(agv[1]))
    {
        pthread_create(&s[i].thread, NULL, s)

        i++;
    }

    free(s);
    return (0);
    
}