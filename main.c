#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100 // Maximum number of patients that can be stored

// Structure to represent a patient
struct Patient {
    int id;
    char name[50];
    float treatment_cost;
};

/* Function to Get Integer Input */
int getIntInput(const char* prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n'); // Clear invalid input
        printf("Invalid input. Please enter a valid number: ");
    }
    return value;
}

/* Function to Get Float Input */
float getFloatInput(const char* prompt) {
    float value;
    printf("%s", prompt);
    while (scanf("%f", &value) != 1) {
        while (getchar() != '\n'); // Clear invalid input
        printf("Invalid input. Please enter a valid number: ");
    }
    return value;
}

/* Function to Get String Input */
void getStringInput(const char* prompt, char* buffer, int bufferSize) {
    printf("%s", prompt);
    getchar(); // Clear the input buffer
    fgets(buffer, bufferSize, stdin);
    // Remove newline character if present
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
}

/* Function to Check for Duplicate IDs */
int isDuplicateID(struct Patient patients[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            return 1;
        }
    }
    return 0;
}

/* Function to Add Patient and Treatment Records */
void addPatient(struct Patient patients[], int *count) {
    if (*count >= MAX_PATIENTS) {
        printf("Patient list is full. Cannot add more patients.\n");
        return;
    }

    struct Patient newPatient;
    newPatient.id = getIntInput("Enter Patient ID: ");

    // Check for duplicate ID
    if (isDuplicateID(patients, *count, newPatient.id)) {
        printf("Patient with ID %d already exists. Please use a unique ID.\n", newPatient.id);
        return;
    }

    getStringInput("Enter Patient Name: ", newPatient.name, sizeof(newPatient.name));
    newPatient.treatment_cost = getFloatInput("Enter Treatment Cost: ");

    // Add the new patient to the array
    patients[*count] = newPatient;
    (*count)++;
    printf("Patient added successfully.\n");
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
        printf("Patient with ID %d not found.\n", id);
    } else {
        printf("Patient with ID %d deleted successfully.\n", id);
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
        printf("| %-10d | %-26s | %-16.2f |\n", patients[i].id, patients[i].name, patients[i].treatment_cost);
    }
    // Print table footer
    printf("+------------+----------------------------+------------------+\n");
}

/* Function to Add Treatment Bills */
void addBill(struct Patient patients[], int count) {
    int id = getIntInput("Enter Patient ID to add bill: ");
    float additional_cost;

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            additional_cost = getFloatInput("Enter additional bill amount: ");
            patients[i].treatment_cost += additional_cost; // Add the additional bill to the treatment cost
            printf("Additional bill added successfully.\n");
            return; // Exit the function after adding the bill
        }
    }
    // If patient ID is not found
    printf("Patient with ID %d not found.\n", id);
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

        choice = getIntInput("");

        // Switch case based on user choice
        switch (choice) {
            case 1:
                addPatient(patients, &count); // Add new patient
                break;
            case 2:
                id = getIntInput("Enter Patient ID to Delete: ");
                deletePatient(patients, id, &count); // Delete patient
                break;
            case 3:
                displayPatients(patients, count); // Display all patients
                break;
            case 4:
                addBill(patients, count); // Add additional bill for a patient
                break;
            case 5:
                printf("Exiting the Program...\n"); // Exit the program
                break;
            default:
                printf("Invalid option. Please select a valid option (1-5).\n"); // Invalid option
        }
    } while (choice != 5); // Continue loop until user chooses to exit

    return 0;
}