#include<stdio.h>
#include<omp.h>

int main()
{
    char* family[] = {"Saurabh", "Vijay", "Varsha", "Harshda"};
    int family_members = 4;

    #pragma omp parallel num_threads(family_members)
    {
        printf("Family member: %s , printed by %d\n", family[omp_get_thread_num()], omp_get_thread_num());
    }
    return 0;
}