// name: Fang Huang
// email: huang.fang@northeastern.edu

// format of document is a bunch of data lines beginning with an integer (rank which we ignore)
// then a ',' followed by a double-quoted string (city name)
// then a ',' followed by a double-quoted string (population) - ignore commas and covert to int; or (X) - convert to 0
// then a lot of entries that are ignored

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define TABLE_SIZE 400

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

typedef struct Node {
    char city[MAXSTRING];
    int population;
    struct Node *next;
} Node;

// check if a character c is a digit
bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

// append character c to string s
void appendChar(char *s, char c) {
    char charToStr[2];
    charToStr[0] = c;
    charToStr[1] = '\0';
    strcat(s, charToStr);
}

// remove commas from a string
void removeCommas(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != ',') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

// hash function 1: length of the city/state string modulo size of table
int hashFunction1(char *str) {
    return strlen(str) % TABLE_SIZE;
}

// hash function 2: sum of the character codes of the city/state string modulo size of table
int hashFunction2(char *str) {
    int sum = 0;
    while (*str) {
        sum += *str++;
    }
    return sum % TABLE_SIZE;
}

// hash function 3: product of the first 2 character codes in city/state string modulo size of table
int hashFunction3(char *str) {
    if (strlen(str) < 2) return 0;
    return (str[0] * str[1]) % TABLE_SIZE;
}

// insert into hash table
void insert(Node *table[], int index, char *city, int population) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->city, city);
    newNode->population = population;
    newNode->next = table[index];
    table[index] = newNode;
}

// initialize hash table
void initTable(Node *table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }
}

// print hash table
void printTable(Node *table[], const char *title) {
    printf("***** %s *****\n", title);
    printf("=======================\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            printf("TABLE[%d]:\n", i);
            Node *current = table[i];
            while (current != NULL) {
                printf("key/value: [%s] / [%d]\n", current->city, current->population);
                current = current->next;
            }
        }
    }
}

int main() {
    char inputLine[MAXSTRING];
    char cityStr[MAXSTRING];
    char popStr[MAXSTRING];
    int lineNum;
    int popInt;
    int state;
    int nextChar;
    char temp[MAXSTRING];

    // Initialize hash tables
    Node *hashTable1[TABLE_SIZE];
    Node *hashTable2[TABLE_SIZE];
    Node *hashTable3[TABLE_SIZE];
    initTable(hashTable1);
    initTable(hashTable2);
    initTable(hashTable3);

    FILE *fp;
    fp = fopen("pop.csv", "r");

    if (fp != NULL) {
        fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

        while (feof(fp) == 0) {
            nextChar = 0;
            state = STARTSTATE;
            strcpy(temp, ""); // temp = ""
            strcpy(cityStr, "");
            strcpy(popStr, "");

            if (nextChar >= strlen(inputLine)) {
                state = ERRORSTATE;
            }

            while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
                switch (state) {
                    case STARTSTATE:
                        if (isDigit(inputLine[nextChar])) {
                            state = S1;
                            appendChar(temp, inputLine[nextChar]);
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S1:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',') {
                            state = S2;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S2:
                        if (inputLine[nextChar] == '"') {
                            state = S3;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S3:
                        if (inputLine[nextChar] != '"') {
                            appendChar(cityStr, inputLine[nextChar]);
                        } else {
                            state = S4;
                        }
                        break;

                    case S4:
                        if (inputLine[nextChar] == ',') {
                            state = S5;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S5:
                        if (inputLine[nextChar] == '"') {
                            state = S6;
                        } else if (inputLine[nextChar] == '(') {
                            popInt = 0;
                            state = ACCEPTSTATE;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S6:
                        if (isDigit(inputLine[nextChar]) || inputLine[nextChar] == ',') {
                            appendChar(popStr, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == '"') {
                            removeCommas(popStr);
                            popInt = atoi(popStr);
                            state = ACCEPTSTATE;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case ACCEPTSTATE:
                        break;

                    default:
                        state = ERRORSTATE;
                        break;
                } // end switch

                // advance input
                nextChar++;
            } // end while state machine loop

            if (state == ACCEPTSTATE) {
                int index1 = hashFunction1(cityStr);
                int index2 = hashFunction2(cityStr);
                int index3 = hashFunction3(cityStr);

                insert(hashTable1, index1, cityStr, popInt);
                insert(hashTable2, index2, cityStr, popInt);
                insert(hashTable3, index3, cityStr, popInt);
            }

            // get next line
            fgets(inputLine, MAXSTRING, fp);
        } // end while file input loop

        fclose(fp);

        // Print hash table results
        printTable(hashTable1, "HASH TABLE 1");
        printTable(hashTable2, "HASH TABLE 2");
        printTable(hashTable3, "HASH TABLE 3");

    } else {
        printf("File not found!\n");
    }

    return 0;
}

