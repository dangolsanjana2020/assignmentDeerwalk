
/* C program to manage the patient records in a hospital.
AUTHOR: Sanjana Dangol
DATE: 2020/05/03
*/

#include <stdio.h>
#include <string.h>


void add(FILE*);
void search(FILE*);
void deleteRecord(FILE*);

struct patient{
    char name[51];
    char disease[51];
    int mobile_no,age;
};

int main() {
    int choice = 0;
    FILE *fptr;
    fptr = fopen("hospital_management.txt","a+");
    printf(" ***Welcome To Hospital Management System***\n");

    while (choice != 4) {
        printf("\n**Enter your choice**\n");
        printf("1. Add Records\n2. Search Records\n3. Delete Records\n4. Exit\n");
        printf("choice=\n");

        scanf("%d", &choice); //selecting the number
        fflush(stdin);

        switch (choice) {
            case 1:
                add(fptr);
                break;
            case 2:
                search(fptr);
                break;
            case 3:
                deleteRecord(fptr);
                break;
            case 4:
                return 0;
            default:
                printf("NOT VALID");
        }
        fclose(fptr);
    }
}

void add(FILE *fptr) {
    struct patient addnew;

    printf("First Name: ");
    scanf("%50s",addnew.name);

    printf("Name of Disease: ");
    scanf("%50s",addnew.disease);

    printf("Age of patient: ");
    scanf("%d", &addnew.age);

    printf("Mobile Number: ");
    scanf("%d", &addnew.mobile_no);


    fwrite(&addnew, sizeof(addnew), 1, fptr);

    printf("Successful!");
}

void search(FILE *fptr) {
    int found = 0;
    struct patient hospital_record;
    char name[50];

    printf("Enter the first name of patient: ");
    scanf("%s", name);

    while (!feof(fptr)) {
        fread(&hospital_record, sizeof(hospital_record), 1, fptr);
        if (strcmp(hospital_record.name,name) == 0) {
            found = 1;
            printf("Name of patient: ");
            puts(hospital_record.name);
            printf("Disease: ");
            puts(hospital_record.disease);
            printf("Mobile number = 0%d\nAge = %d", hospital_record.mobile_no, hospital_record.age);
            printf("\n");
        }
    }
    if (!found)
        printf("INVALID");
}

void deleteRecord(FILE *fptr){
    fclose(fptr);
    FILE *fptrTemp;
    fptr = fopen("hospital_management.txt","r");
    fptrTemp = fopen("temp.txt","w");
    struct patient tempRecord;
    char searchName[21];

    printf("Please enter the name: ");
    scanf("%20s",searchName);

    while (!feof(fptr)){
        fread(&tempRecord, sizeof(tempRecord), 1, fptr);
        if (strcmp(searchName, tempRecord.name) == 0 ) {
            continue;
        } else{
            fwrite(&tempRecord,sizeof(tempRecord),1,fptrTemp);
        }
    }

    fclose(fptrTemp);
    fclose(fptr);

    fptrTemp = fopen("temp.txt","r");
    fptr = fopen("hospital_management.txt","w");

    while (!feof(fptrTemp)){
        fread(&tempRecord, sizeof(tempRecord), 1, fptrTemp);
        fwrite(&tempRecord,sizeof(tempRecord),1,fptr);
        printf("Name: %s\n", tempRecord.name);
        printf("Age: %d", tempRecord.age);

    }

    fclose(fptrTemp);
    fclose(fptr);
}
