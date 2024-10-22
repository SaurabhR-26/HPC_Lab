#include <stdio.h>
#include <omp.h>

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 20

int buffer[BUFFER_SIZE];
int count = 0;
int produced_items = 0;
int consumed_items = 0;

omp_lock_t lock;

// Producer function
void producer(int id)
{
    while (1)
    {
        omp_set_lock(&lock);
        if (produced_items >= TOTAL_ITEMS)
        {
            omp_unset_lock(&lock);
            break;
        }

        if (count < BUFFER_SIZE)
        {
            buffer[count] = id;
            count++;
            produced_items++;
            printf("Producer %d produced item %d, buffer size: %d\n", id, produced_items, count);
        }
        omp_unset_lock(&lock);
    }
}

// Consumer function
void consumer(int id)
{
    while (1)
    {
        omp_set_lock(&lock);
        if (consumed_items >= TOTAL_ITEMS)
        {
            omp_unset_lock(&lock);
            break;
        }

        if (count > 0)
        {
            int item = buffer[count - 1];
            count--;
            consumed_items++;
            printf("Consumer %d consumed item %d, buffer size: %d\n", id, item, count);
        }
        omp_unset_lock(&lock);
    }
}

int main()
{
    int num_producers = 2;
    int num_consumers = 2;

    omp_init_lock(&lock);

// Parallel region
#pragma omp parallel num_threads(num_producers + num_consumers)
    {
        int id = omp_get_thread_num();
        if (id < num_producers)
        {
            producer(id);
        }
        else
        {
            consumer(id - num_producers);
        }
    }

    omp_destroy_lock(&lock);

    return 0;
}
