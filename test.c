#include<stdio.h>
#include<string.h>

#define KRED  "\x1B[31m"
#define KYEL  "\x1B[33m"
#define RESET "\033[0m"
#define TRUE 1
#define FALSE 0

struct{
    int born;
    char firstName[20];
    char lastName[20];
    double phoneNumber;
    int record;
}dataBase;

void showRecord(void);
void noRecord(char record[]);
void searchString(FILE *file, char string[]);

int main(void){
    char name[20];
    const char *db = "database.txt";
    FILE *file = fopen(db, "r");
    dataBase.record=1;

    printf("Please type First or Last name to search:\t");
    scanf("%s", name);

    searchString(file, name);
    fclose(file);
   return 0;
}

void showRecord(void){
    printf("\n\t\tRecord\t%d\n",dataBase.record++);
    printf("First Name:\t%s\n", dataBase.firstName);
    printf("Last Name:\t%s\n", dataBase.lastName);
    printf("Born:\t\t%d\n", dataBase.born);
    printf("Phone Number:\t%.0f\n", dataBase.phoneNumber);
    printf("------------------------------\n");
}

void noRecord(char record[]){
    printf(KRED "\n\t\t\tNo record found with name\t"RESET KYEL "%s\n"RESET , record);
}

void searchString(FILE *file, char string[]){
    int check = 0;

    while(!feof(file)){
      fscanf(file,"\n%s\t%s\t%d\t%lf\t",dataBase.firstName,dataBase.lastName,&dataBase.born,&dataBase.phoneNumber);

        if(strcasecmp(dataBase.firstName,string)==0){
             showRecord();
             check = TRUE;
        }else if(strcasecmp(dataBase.lastName,string)==0){
             showRecord();
             check = TRUE;
        }
    }
    if(check == FALSE) {
        noRecord(string);
    }
}