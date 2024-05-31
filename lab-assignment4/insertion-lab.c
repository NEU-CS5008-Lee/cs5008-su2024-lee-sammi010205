//Fang Huang
//huang.fang@northeastern.edu
//To perform insertion sort of integers stored in a file and display the output and store it in another file.
#include <stdio.h>
#include<stdlib.h>

void insertion_sort(int arr[], int n) {
        int i, j, key;
        for (i = 1; i < n; i++) {
                key = arr[i];
                j = i - 1;
                while (j >= 0 && arr[j] > key) {
                        arr[j+1] = arr[j];
                        j--;
                }
                arr[j+1] = key;
        }

}


int main()
{
    FILE *fp;
    int arr[10],temp;
    int count=0,i,j;
    /*count will have the total number of elements in the array*/

    /*read the file*/
    fp=fopen("Input1.txt","r");
    if(fp==NULL){
        //if file returns NULL then can't open the file
        printf("\n Cannot open the file \n");
        exit(0);
    }
    
    //insert your code here
    while (fscanf(fp, "%d", &arr[count]) != EOF && count < 10){
		    count ++;
    }
    fclose(fp);

    insertion_sort(arr, count); // will be defined later;

    printf("Sorted array is: \n");
    for (i = 0; i < count; i++) {
	    printf("%d\n", arr[i]);
    }

    fp = fopen("Sorted.txt","w");
    if (fp == NULL) {
	    printf("\nCannot open the file for writing.\n");
	    exit(0);
    }

    for (i=0; i<count; i++){
	    fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);  
    
    return 0;
}

