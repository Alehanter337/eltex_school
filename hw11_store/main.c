#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int store[5];
pthread_mutex_t mutexes[5];
int count;

struct Buyer_data
{
	int id;
	int need;
};

struct Buyer_data buyer_data[3];

void store_start(int *store)
{
	for (int i = 0; i < 5; i++)
	{
		store[i] = rand() % (1100 - 900 + 1) + 900;
		printf("store %d = %d\n", i + 1, store[i]);
		
	}
}

void *buyer_what_to_do(void *arg)
{
	struct Buyer_data *buyer_data = (struct Buyer_data*) arg;
	printf("in thread buyer %d need %d\n", buyer_data->id, buyer_data->need);

	while (buyer_data -> need > 0)
	{
		sleep(3);
		int current_store = (rand() % 4);
		pthread_mutex_lock(&mutexes[current_store]);
		printf("Buyer %d enter store %d and buy %d", 
				buyer_data -> id, current_store + 1, store[current_store]);
		buyer_data -> need -= store[current_store];
		store[current_store] = 0;
		printf("  now store %d is empty\n", current_store + 1);
		pthread_mutex_unlock(&mutexes[current_store]);
	}	
	printf("   buyer %d need 0\n", buyer_data -> id);
	count++;
	pthread_exit(0);
}

void *loader_what_to_do(void *arg)
{
	while (count < 5)
	{
		int current_store = rand() % 4;
		printf("    Current loader store is %d\n", current_store + 1);
		pthread_mutex_lock(&mutexes[current_store]);
		store[current_store] += 1000;
		printf("     Loader  enter store %d and load %d\n Store %d have %d\n", current_store + 1, 1000, current_store + 1, store[current_store]);
		pthread_mutex_unlock(&mutexes[current_store]);
		sleep(2);
	}
	pthread_exit(0);
}

void buyer_buy(pthread_t *buyer)
{
	for (int i = 0; i < 3; i++)
	{
		buyer_data[i].id = i + 1; 
		buyer_data[i].need = rand() % (11000-9900 + 1) + 9900;
		printf("buyer %d need %d\n", buyer_data[i].id, buyer_data[i].need);
	}
	for (int i = 0; i < 3; i++)
	{
		void *current_buyer = &buyer_data[i];
		//pthread_create(&buyer[i], NULL, buyer_what_to_do, current_buyer);
		if(pthread_create(&buyer[i], NULL, buyer_what_to_do, current_buyer) != 0)
		{
			perror("ERROR: buyer create failed");
			exit(EXIT_FAILURE);
		}
		
	}
}

void loader_load(pthread_t loader)
{
	if (pthread_create(&loader, NULL, loader_what_to_do, NULL) != 0)
	{
		perror("ERROR: loader create failed");
		exit(EXIT_FAILURE);
	}
}

void threads_join(pthread_t *buyer, pthread_t loader)
{
	for (int i = 0; i < 3; i++)
	{
		pthread_join(buyer[i], NULL);
	}
	pthread_join(loader, NULL);
}

int main()
{
	srand(time(NULL));
	pthread_t buyer[3];
	pthread_t loader;
	store_start(store);
	buyer_buy(buyer);
	loader_load(loader);
	threads_join(buyer, loader);
	return 0;
}
