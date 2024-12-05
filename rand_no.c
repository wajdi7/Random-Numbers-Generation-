#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANDOM_NUMBERS 10000  // Change this to 10000 for the second part

void generate_random_numbers(const char *filename, int num_numbers) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to create file %s\n", filename);
        return;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate random numbers
    for (int g = 0; g < num_numbers; g++) {
        double random_number = (double)rand() / RAND_MAX;
        fprintf(file, "%.6f\n", random_number);  // Save to file
    }

    fclose(file);
    printf("Generated %d random numbers and saved to %s\n", num_numbers, filename);
}

void display_random_numbers(const char *filename, int num_numbers_per_row) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    double random_number;
    int count = 0;
    while (fscanf(file, "%lf", &random_number) != EOF) {
        printf("%.6f\t", random_number);
        count++;
        if (count % num_numbers_per_row == 0) {
            printf("\n");
        }
    }

    fclose(file);
}

int main() {
    const char *filename = "RN-file.txt";
    generate_random_numbers(filename, NUM_RANDOM_NUMBERS);

    printf("\n Displaying random numbers from %s:\n\n", filename);
    display_random_numbers(filename, 10);  // Display 10 numbers per row

    return 0;
}
