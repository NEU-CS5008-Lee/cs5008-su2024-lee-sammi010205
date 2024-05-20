/* Name: Fang Huang, Summer_2024
 * Email: huang.fang@northeastern.edu
 * C Program to read and print the n employee details using structure and dynamic memory allocation*/

#include <stdio.h>
#include <stdlib.h>

/*structure to hold the details of an employee*/

typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;


/* Read the employee details using scanf*/
void readData(int n, employee_t* s){

   for (int i = 0; i < n; i++) {
	printf("Employee %d:\n", i+1);
    	printf("please enter your ID: ");
	scanf("%d", &(s->empId));
	printf("name: ");
	scanf("%s", s->Name);
	printf("designation: ");
	scanf("%s", s->Designation);
	printf("department: ");
	scanf("%s", s->Dept);
	printf("\n");
	s++;
    }
   
}


/* function to print the employee details*/
void display(int n, employee_t* s)
{
    // display the details of this employee
    for (int i = 0; i < n; i++) {
	printf("The details of the employee %d:\n", i+1);
	printf("Employee ID: %d\n", s -> empId);
	printf("Name: %s\n", s->Name);
	printf("Designation: %s\n", s->Designation);
	printf("Department: %s\n\n", s-> Dept);
	s++;
    }
    
}


/*----main function-----*/

int main() {
    // Main Function to print the employee details

    printf("Enter the  number of employees: ");
    int n;
    scanf("%d", &n);
    employee_t* s = (employee_t*) malloc(n*sizeof(employee_t));
    readData(n, s);
    display(n, s);
    return 0;

}

