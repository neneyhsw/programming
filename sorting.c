/*
    This topic use different sorting algorithm to test different array of sorting
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define MAX_SIZE 10000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

struct timespec diff(struct timespec, struct timespec);
void Selection_Sort (int []);
void Bubble_Sort(int []);
void max_heapify(int [], int, int);
void Heap_Sort(int [], int);
double Gettime_Selection_Sort(int [], struct timespec, struct timespec, struct timespec);
double Gettime_Bubble_Sort(int [], struct timespec, struct timespec, struct timespec);
double Gettime_Heap_Sort(int [], struct timespec, struct timespec, struct timespec);

int main(void)
{
	int i = 0, j = 0, k = 0, n = 0, temp = 0;
	int list0[MAX_SIZE], list1[MAX_SIZE], list2[MAX_SIZE], list3[MAX_SIZE];
	double stest1 = 0, stest2 = 0, stest3 = 0, btest1 = 0, btest2 = 0, btest3 = 0, htest1 = 0, htest2 = 0, htest3 = 0;
	struct timespec tt1, tt2, ft;
   
	srand(time(NULL));  //to let rand function is random by timing
		
	for(i = 0; i < MAX_SIZE; i++)  //store 1~10000 to list0
		list0[i] = i+1;
		
	//copy list0 to list1 and list3
	memcpy(list1, list0, MAX_SIZE * sizeof(int));  //Generate Case A
	memcpy(list3, list0, MAX_SIZE * sizeof(int));
	
	for(k = 0; k < 10; k++)  //k = run times 
	{
		//randomly generate list3 and store 10000~1 to list2
		for(i = 0; i < MAX_SIZE; i++)  
		{
			n++;
			list2[MAX_SIZE-n] = list0[i];  //generate Case B
			j = rand()%10000;  //generate Case C
			SWAP(list3[i], list3[j], temp);  //randomly swap every space and every space has to be swaped
		}
		j = 0;  n = 0;  //reset j, n = 0
	
		//get the selection sort time to stest
		stest1 += Gettime_Selection_Sort(list1, tt1, tt2, ft);
		stest2 += Gettime_Selection_Sort(list2, tt1, tt2, ft);
		stest3 += Gettime_Selection_Sort(list3, tt1, tt2, ft);
	
		//reset Case B and Case C
		for(i = 0; i < MAX_SIZE; i++)  
		{
			n++;
			list2[MAX_SIZE-n] = list0[i];
			j = rand()%10000;
			SWAP(list3[i], list3[j], temp);
		}
		j = 0;  n = 0;
		
		//get the bubble sort time to btest
		btest1 += Gettime_Bubble_Sort(list1, tt1, tt2, ft);
		btest2 += Gettime_Bubble_Sort(list2, tt1, tt2, ft);
		btest3 += Gettime_Bubble_Sort(list3, tt1, tt2, ft);
	
		//reset Case B and Case C
		for(i = 0; i < MAX_SIZE; i++)  
		{
			n++;
			list2[MAX_SIZE-n] = list0[i];
			j = rand()%10000;
			SWAP(list3[i], list3[j], temp);
		}
		j = 0;  n = 0;
		
		//get the Heap Sort time to htest
		htest1 += Gettime_Heap_Sort(list1, tt1, tt2, ft);
		htest2 += Gettime_Heap_Sort(list2, tt1, tt2, ft);
		htest3 += Gettime_Heap_Sort(list3, tt1, tt2, ft);
	}

		//print list1, list2, list3 to test generated data and sorted data 
/*		printf("Case A:\n");
		for(i = 0; i < MAX_SIZE; i++) 
			printf("%d ", list1[i]);
		printf("\n\n");
	
		printf("Case B:\n"); 
		for(i = 0; i < MAX_SIZE; i++)
			printf("%d ", list2[i]);
		printf("\n\n");
	
		printf("Case C:\n");
		for(i = 0; i < MAX_SIZE; i++)
			printf("%d ",list3[i]);
		printf("\n");
*/

	//print Average Time
	printf("Selection Sort:\n");
	printf("Case A: Average Time %.9f secs\n", stest1 / k);
	printf("Case B: Average Time %.9f secs\n", stest2 / k);
	printf("Case C: Average Time %.9f secs\n\n", stest3 / k);
	
	printf("Bubble Sort:\n");
	printf("Case A: Average Time %.9f secs\n", btest1 / k);
	printf("Case B: Average Time %.9f secs\n", btest2 / k);
	printf("Case C: Average Time %.9f secs\n\n", btest3 / k);

	printf("Heap Sort:\n");
	printf("Case A: Average Time %.9f secs\n", htest1 / k);
	printf("Case B: Average Time %.9f secs\n", htest2 / k);
	printf("Case C: Average Time %.9f secs\n", htest3 / k);
	
	system("pause");
	return 0;
}

// for time calculate
struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec - start.tv_nsec) < 0) 
	{
		temp.tv_sec = end.tv_sec - start.tv_sec-1;
		temp.tv_nsec = 1000000000 + end.tv_nsec-start.tv_nsec;
	}
	else
	{
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}

void Selection_Sort(int list[])
{
	int i = 0, j = 0, min = 0, temp = 0;
	for(i = 0; i < MAX_SIZE-1; i++)
	{
		min = i;
		for(j = i+1; j < MAX_SIZE; j++)
			if(list[j] < list[min])
				min = j;
		SWAP(list[i], list[min], temp);
	}
}

void Bubble_Sort(int list[])
{
	int i = 0, j = 0, temp = 0;
	for (i = 0 ; i < MAX_SIZE-1 ; ++i) 
	{
		int flag = 1;
		for (j = 0; j < MAX_SIZE - i - 1; ++j) 
		{
			if (list[j] > list[j+1]) 
			{
				SWAP(list[j], list[j+1], temp);
				flag = 0;
			}
		}
		if (flag) return;
	}
}

// prepare for head sort.
void max_heapify(int arr[], int start, int end)
{

	int temp = 0;
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end)
	{
		if (son + 1 <= end && arr[son] < arr[son + 1])
			son++;
		if (arr[dad] > arr[son])
			return;
		else
		{
			SWAP(arr[dad], arr[son], temp);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void Heap_Sort(int arr[], int len)
{
	int i, temp = 0;
	for (i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	for (i = len - 1; i > 0; i--)
	{
		SWAP(arr[0], arr[i], temp);
		max_heapify(arr, 0, i - 1);
	}
}

// calculate time to nm unit
double Gettime_Selection_Sort(int list1[], struct timespec tt1, struct timespec tt2, struct timespec ft)
{
	double stest1 = 0;
	clock_gettime(CLOCK_MONOTONIC, &tt1);
	Selection_Sort(list1);
	clock_gettime(CLOCK_MONOTONIC, &tt2);
	ft = diff(tt1, tt2);
	stest1 = ft.tv_sec + (double) ft.tv_nsec / 1000000000.0;
	return stest1;
}

double Gettime_Bubble_Sort(int list1[], struct timespec tt1, struct timespec tt2, struct timespec ft)
{
	double btest1 = 0;
	clock_gettime(CLOCK_MONOTONIC, &tt1);
	Bubble_Sort(list1);
	clock_gettime(CLOCK_MONOTONIC, &tt2);
	ft = diff(tt1, tt2);
	btest1 = ft.tv_sec + (double) ft.tv_nsec / 1000000000.0;
	return btest1;
}

double Gettime_Heap_Sort(int list1[], struct timespec tt1, struct timespec tt2, struct timespec ft)
{
	double htest1 = 0;
	clock_gettime(CLOCK_MONOTONIC, &tt1);
	Heap_Sort(list1, MAX_SIZE);
	clock_gettime(CLOCK_MONOTONIC, &tt2);
	ft = diff(tt1, tt2);
	htest1 = ft.tv_sec + (double) ft.tv_nsec / 1000000000.0;
	return htest1;
}
