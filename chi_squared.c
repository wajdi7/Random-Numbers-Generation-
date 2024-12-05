#include <stdio.h>
#include <math.h>

#define NUM_BINS 10         // Number of bins
#define TOTAL_NUMBERS 10000  // Total random numbers generated (adjust to 10000 for the second part)

void chi_squared_test(const char *bin_file, int num_bins, int total_numbers) {
    FILE *file = fopen(bin_file, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", bin_file);
        return;
    }

    int bin_counts[num_bins];
    double expected_count = (double)total_numbers / num_bins;  // Expected count in each bin
    double chi_squared = 0.0;

    // Read bin counts from the file
    char line[100];
    fgets(line, sizeof(line), file);  // Skip the header line
    for (int l = 0; l < num_bins; l++) {
        fscanf(file, "%*d %*f %*f %d", &bin_counts[l]);  // Read the bin count, ignore other values
    }

    fclose(file);

    // Calculate Chi-Squared statistic
    for (int ch = 0; ch < num_bins; ch++) {
        double observed = bin_counts[ch];
        chi_squared += pow((observed - expected_count), 2) / expected_count;
    }

    printf("Chi-Squared Statistic: %.4f\n", chi_squared);

    // Critical value for 9 degrees of freedom at 0.05 significance level
    double critical_value = 16.919;

    printf("Critical Value (df=9, α=0.05): %.3f\n", critical_value);

    if (chi_squared <= critical_value) {
        printf("Result: Fail to reject H₀. The numbers are uniformly distributed.\n");
    } else {
        printf("Result: Reject H₀. The numbers are not uniformly distributed.\n");
    }
}

int main() {
    const char *bin_file = "Bin-Counts.txt";  // File containing bin counts
    chi_squared_test(bin_file, NUM_BINS, TOTAL_NUMBERS);
    return 0;
}
