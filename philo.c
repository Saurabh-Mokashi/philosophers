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

typedef struct ginfo
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_of_philo;
    int freq;
    struct pinfo *ptr;
}   g_info;

typedef struct pinfo
{
    int id;
    pthread_t thread;
    pthread_mutex_t lfork;
    pthread_mutex_t *rfork;
    pthread_mutex_t print;
    struct timeval s_time;  
    struct ginfo *g;
}   s_info;

long time_in_ms(s_info *philo, struct timeval curr_time)
{
    long time;

    time = ((curr_time.tv_sec - philo->s_time.tv_sec)*1000 + (curr_time.tv_usec - philo->s_time.tv_usec)/1000);
    return (time);
}

void death(s_info *philo,int i)
{
    g_info *g;

    g=philo->g;
    printf("%d %d died\n",g->time_to_die+1,philo[i].id);
    // printf("bye\n");
}

long getcurrtime(s_info *philo)
{
    struct timeval curr_time;
    long time;
    gettimeofday(&curr_time, NULL);
    time = time_in_ms(philo, curr_time);
    return (time);
}


void sleepy(s_info *philo)
{
    printf("\ngo back to sleep!!");
}

void lockprint(s_info *philo, int choice)
{
    pthread_mutex_lock(&philo->print);
    if(choice == 2)
        printf("%ld %d has taken a fork\n",getcurrtime(philo),philo->id);
    if(choice == 3)
        printf("%ld %d is eating\n",getcurrtime(philo),philo->id);
    if(choice == 4)
        printf("%ld %d is sleeping\n",getcurrtime(philo),philo->id);
    pthread_mutex_unlock(&philo->print);
    
}

void freefork(s_info *philo)
{
    if((philo->id)%2==0)
    {
        pthread_mutex_unlock(philo->rfork);
        lockprint(philo,2);
        // printf("%ld %d has released a fork\n",getcurrtime(philo),philo->id);
        pthread_mutex_unlock(&philo->lfork);
        lockprint(philo,2);
        // printf("%ld %d has released a fork\n",getcurrtime(philo),philo->id);
    }
    else
    {
        pthread_mutex_unlock(&philo->lfork);
        // printf("%ld %d has released a fork\n",getcurrtime(philo),philo->id);
        pthread_mutex_unlock(philo->rfork);
        // printf("%ld %d has released a fork\n",getcurrtime(philo),philo->id);
    }
}
void takefork(s_info *philo)
{
    if((philo->id)%2==0)
    {
        pthread_mutex_lock(&philo->lfork);
        // printf("%ld %d has taken a fork\n",getcurrtime(philo),philo->id);
        lockprint(philo,2);
        pthread_mutex_lock(philo->rfork);
        lockprint(philo,2);
        // printf("%ld %d has taken a fork\n",getcurrtime(philo),philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->rfork);
        lockprint(philo,2);
        // printf("%ld %d has taken a fork\n",getcurrtime(philo),philo->id);
        pthread_mutex_lock(&philo->lfork);
        lockprint(philo,2);
        // printf("%ld %d has taken a fork\n",getcurrtime(philo),philo->id);
    }
}

void multiphilo(s_info *philo)
{
    // struct timeval curr_time;
    // long time;

    // gettimeofday(&curr_time, NULL);
    // time = time_in_ms(philo, curr_time);
    // printf("time is %ld\n",time);//prolly need mutex for time calc.
    // while(1){
    takefork(philo);
    lockprint(philo,3);
    freefork(philo);
    // sleepy(philo);
    lockprint(philo,4);
    // }
    return ;

}

void single_philo(s_info *philo)
{
    struct timeval curr_time;
    long time;

    // sleep(1);
    gettimeofday(&curr_time, NULL);
    time = time_in_ms(philo, curr_time);
    // printf("single philo, and time is %ld",time);
    death(philo,0);
    // printf("%ld is in seconds and %ld is in microseconds",philo->s_time.tv_sec, philo->s_time.tv_usec);
    // printf("\n%ld\n",philo->curr_time.tv_sec - philo->s_time.tv_sec);
}

void* rout(void *s)
{
    s_info *philo;
    g_info *comm;
    // long time;
    // time = philo->time.tv_sec;

    philo = (s_info *)s;
    comm = (g_info *)philo->g;
    // usleep(100);
    // printf("\n\nhello world and id is %d!!!!\n",philo->id);
    // printf("died\n");
    // printf("And time is %ld with microsecs as %ld\n", philo->s_time.tv_sec,philo->s_time.tv_usec);
    // write(1,"mynameis",8);
    // free(philo);

    //main code crux
        // printf("%d\n",philo->id);
        // printf("hi\n");
        // printf("%d\n",comm->num_of_philo);
    if(comm->num_of_philo == 1)
        single_philo(philo);
    else
        multiphilo(philo);
    return NULL;
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

int isalph(char **agv,int ac)
{
    int i;
    int j;

    i = 1;
    while(i<ac)
    {
        j = 0;
        while(agv[i][j])
        {
            if(agv[i][j]<'0' || agv[i][j]>'9')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int errcheck(int ac, char **agv)
{
    int i;
    int num;

    i = 1;
    if (ac <= 4 || ac >= 7 || isalph(agv,ac))
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
    g_info *comm;
    int     i;

    if(errcheck(ac,agv))
    {
        printf("Invalid arguments\n");
        return (0);
    }
    i = 0;
    comm = malloc(sizeof(g_info));
    s = malloc(sizeof(s_info) * ft_atoi(agv[1]));
    comm[i].num_of_philo = ft_atoi(agv[1]);
    comm[i].time_to_die = ft_atoi(agv[2]);
    comm[i].time_to_eat = ft_atoi(agv[3]);
    comm[i].time_to_sleep = ft_atoi(agv[4]);
    if(ac == 6)
        comm[i].freq = ft_atoi(agv[5]);
    else
        comm[i].freq=-1;
    while (i < ft_atoi(agv[1]))
    {
        s[i].id = i+1;
        pthread_mutex_init(&s[i].lfork,NULL);
        pthread_mutex_init(&s[i].print,NULL);
        s[i].rfork = NULL;
        s[i].g=comm;
        gettimeofday(&s[i].s_time,NULL);
        i++;
    }
    i = 0;
    while (i < comm[i].num_of_philo)
    {
        if(i == comm[i].num_of_philo - 1)
            s[i].rfork = &(s[0].lfork);
        else
            s[i].rfork = &(s[i+1].lfork);
        i++;
    }
    // printf("agv[1] val %d\n",ft_atoi(agv[1]));
    // while(i<ft_atoi(agv[1]))
    // {
    //     printf("id is %d\n",s[i].id);
    //     i++;
    // }
    i = 0;
    // printf("comis %d\n",comm->num_of_philo);
    // printf("\n\n%d\n\n",comm->num_of_philo);
    while(i<ft_atoi(agv[1]))
    {
        // s_info *q = malloc(sizeof(s_info));
        // *q = s[i];
        // printf("abt to create thread\n");
        if(pthread_create(&s[i].thread, NULL, &rout, &s[i]))
        {
            printf("create prob\n");
            free (s);
            free(comm);
            return (0);
        }
        // usleep(100);
        // printf("hhh\n");
        i++;
    }
    i = 0;
    while(i<ft_atoi(agv[1]))
    {
        if(pthread_join(s[i].thread,NULL))
        {
            free(s);
            free(comm);
            return (0);
        }
        i++;
    }
    free(s);
    free(comm);
    return (0);
}