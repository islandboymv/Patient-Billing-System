#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100 // Maximum number of patients that can be stored

// Structure to represent a patient
struct Patient {
    int id;
    char name[50];
    float treatment_cost;
};

/* Function to Add Patient and Treatment Records */
void addPatient(struct Patient patients[], int *count) {
    struct Patient newPatient;

    // Input patient details from the user
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

    // Add the new patient to the array
    patients[*count] = newPatient;
    (*count)++;
}

/* Function to Delete Patient Records */
void deletePatient(struct Patient patients[], int id, int *count) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (patients[i].id == id) {
            // Shift elements to the left to fill the gap
            for (int j = i; j < *count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            (*count)--; // Decrement the count of patients
            found = 1; // Set found flag to true
            break; // Exit loop once patient is found and deleted
        }
    }
    if (!found) {
        printf("\nPatient with ID %d not found.\n", id);
    } else {
        printf("\nPatient with ID %d deleted successfully.\n", id);
    }
}

/* Function to Display all Patient and Treatment Records */
void displayPatients(struct Patient patients[], int count) {
    // Print table headers
    printf("\n+------------+----------------------------+------------------+\n");
    printf("| Patient ID | Name                       | Treatment Cost   |\n");
    printf("+------------+----------------------------+------------------+\n");
    // Iterate through the patients array and print each patient's details
    for (int i = 0; i < count; i++) {
        printf("| %-10d | %-26s | %.2f           |\n", patients[i].id, patients[i].name, patients[i].treatment_cost);
    }
    // Print table footer
    printf("+------------+----------------------------+------------------+\n");
}

/* Function to Add Treatment Bills */
void addBill(struct Patient patients[], int count) {
    int id;
    float additional_cost;
    // Prompt user for patient ID and additional bill amount
    printf("\nEnter Patient ID to add bill: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            // Prompt user for additional bill amount for the specified patient
            printf("Enter additional bill amount for %s: ", patients[i].name);
            scanf("%f", &additional_cost);
            patients[i].treatment_cost += additional_cost; // Add the additional bill to the treatment cost
            printf("Additional bill added successfully.\n");
            return; // Exit the function after adding the bill
        }
    }
    // If patient ID is not found
    printf("Patient with ID %d not found.\n", id);
}

/* Function to Calculate and Return Total Treatment Cost */
float calculateBill(float treatment_cost) {
    // You can add tax or discounts calculation here if needed
    return treatment_cost;
}

int main() {
    struct Patient patients[MAX_PATIENTS]; // Array to store patient records
    int count = 0; // Variable to keep track of the number of patients
    int choice, id;

    // Main menu loop
    do {
        printf("\n*** Patient Billing System ***\n");
        printf("+----------------------------------------+\n");
        printf("| Option |          Description           |\n");
        printf("+----------------------------------------+\n");
        printf("|   1    | Add New Patient                |\n");
        printf("|   2    | Delete Patient                 |\n");
        printf("|   3    | Display All Patients           |\n");
        printf("|   4    | Add Additional Bill            |\n");
        printf("|   5    | Exit                           |\n");
        printf("+----------------------------------------+\n");
        printf("Select an option (1-5): ");
        scanf("%d", &choice);

        // Switch case based on user choice
        switch (choice) {
            case 1:
                addPatient(patients, &count); // Add new patient
                break;
            case 2:
                printf("\nEnter Patient ID to Delete: ");
                scanf("%d", &id);
                deletePatient(patients, id, &count); // Delete patient
                break;
            case 3:
                displayPatients(patients, count); // Display all patients
                break;
            case 4:
                addBill(patients, count); // Add additional bill for a patient
                break;
            case 5:
                printf("\nExiting the Program...\n"); // Exit the program
                break;
            default:
                printf("\nInvalid option. Please select a valid option (1-5).\n"); // Invalid option
        }
    } while (choice != 5); // Continue loop until user chooses to exit

    return 0;
}