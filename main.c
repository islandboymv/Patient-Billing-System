#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

struct Patient {
    int id;
    char name[50];
    float treatment_cost;
};

void addPatient(struct Patient patients[], int *count) {
    struct Patient newPatient;

    printf("\nEnter Patient ID: ");
    scanf("%d", &newPatient.id);
    printf("Enter Patient Name: ");
    getchar(); // Clear the input buffer
    fgets(newPatient.name, sizeof(newPatient.name), stdin);
    // Remove newline character if present
    if (newPatient.name[strlen(newPatient.name) - 1] == '\n') {
        newPatient.name[strlen(newPatient.name) - 1] = '\0';
    }
    printf("Enter Treatment Cost: ");
    scanf("%f", &newPatient.treatment_cost);

    patients[*count] = newPatient;
    (*count)++;
}

void updatePatient(struct Patient patients[], int id, int count) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("\nEnter New Treatment Cost for Patient %d: ", id);
            scanf("%f", &patients[i].treatment_cost);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nPatient with ID %d not found.\n", id);
    }
}

void deletePatient(struct Patient patients[], int id, int *count) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (patients[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            (*count)--;
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nPatient with ID %d not found.\n", id);
    } else {
        printf("\nPatient with ID %d deleted successfully.\n", id);
    }
}

void displayPatients(struct Patient patients[], int count) {
    printf("\n+------------+----------------------------+------------------+\n");
    printf("| Patient ID | Name                       | Treatment Cost   |\n");
    printf("+------------+----------------------------+------------------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %-10d | %-26s | %.2f           |\n", patients[i].id, patients[i].name, patients[i].treatment_cost);
    }
    printf("+------------+----------------------------+------------------+\n");
}

void addBill(struct Patient patients[], int count) {
    int id;
    float additional_cost;
    printf("\nEnter Patient ID to add bill: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("Enter additional bill amount for %s: ", patients[i].name);
            scanf("%f", &additional_cost);
            patients[i].treatment_cost += additional_cost;
            printf("Additional bill added successfully.\n");
            return;
        }
    }
    printf("Patient with ID %d not found.\n", id);
}

float calculateBill(float treatment_cost) {
    // You can add tax or discounts calculation here if needed
    return treatment_cost;
}

int main() {
    struct Patient patients[MAX_PATIENTS];
    int count = 0;
    int choice, id;

    do {
        printf("\n*** Patient Billing System ***\n");
        printf("1. Add New Patient\n");
        printf("2. Update Patient Treatment Cost\n");
        printf("3. Delete Patient\n");
        printf("4. Display All Patients\n");
        printf("5. Add Additional Bill\n");
        printf("6. Exit\n");
        printf("Select an option (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient(patients, &count);
                break;
            case 2:
                printf("\nEnter Patient ID: ");
                scanf("%d", &id);
                updatePatient(patients, id, count);
                break;
            case 3:
                printf("\nEnter Patient ID to Delete: ");
                scanf("%d", &id);
                deletePatient(patients, id, &count);
                break;
            case 4:
                displayPatients(patients, count);
                break;
            case 5:
                addBill(patients, count);
                break;
            case 6:
                printf("\nExiting the Program...\n");
                break;
            default:
                printf("\nInvalid option. Please select a valid option (1-6).\n");
        }
    } while (choice != 6);

    return 0;
}
