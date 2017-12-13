#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 3

int size = 0;
int avg = 0;
int max = 0;
int min = 0;

void *average(int *total_elements[]);
void *maxValue(int *total_elements[]);
void *minValue(int *total_elements[]);

int main(int argc, char *argv[]){
	pthread_t tidAvg, tidMax, tidMin;
	pthread_t workers[NUM_THREADS];
	pthread_attr_t attr;

	if (argc < 2) { fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}

	size = argc - 1;

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	pthread_create(&tidAvg,&attr,average, argv);

	pthread_create(&tidMax,&attr,maxValue, argv);

	pthread_create(&tidMin,&attr,minValue, argv);


	for (int i = 0; i <= NUM_THREADS; i++){
		pthread_join(workers[i], NULL);
	}
	// /* wait for the thread to exit */
	printf("The average value is %d\n",avg);
	printf("The maximum value is  = %d\n",max);
	printf("The minimum value is  = %d\n",min);
}

void *average(int *total_elements[]) {
	int sum=0;
	for (int i = 1; i <= size; i++){
		sum = sum + atoi(total_elements[i]);
	}

	avg = sum/size;
	pthread_exit(0);
}

void *maxValue(int *total_elements[]){
	max = atoi(total_elements[1]);
	for(int i = 1; i <= size ; i++){
		int element = atoi(total_elements[i]);
		if(element > max){
			max = atoi(total_elements[i]);
		}
	}
	pthread_exit(0);
}

void *minValue(int *total_elements[]){

	min = atoi(total_elements[1]);
	for(int i = 1; i <= size ; i++){
		int element = atoi(total_elements[i]);
		if(element < min){
			min = atoi(total_elements[i]);
		}
	}
	pthread_exit(0);
}
