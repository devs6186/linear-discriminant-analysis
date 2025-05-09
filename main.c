#include <stdio.h>
#include <stdlib.h>
#include "data_face80.h"
#include "lda.h"
#include <math.h>

#define NUM_SAMPLES 80
#define NUM_CLASSES 8
#define SAMPLES_PER_CLASS 10

void print_first_5_features() {
    printf("\n=== First 5 Features of First 5 Images ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Image %d: ", i);
        for (int j = 0; j < 5; j++) {
            printf("%3d ", data_face80[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf(">>> PROGRAM STARTED <<<\n");
    fflush(stdout);

    printf("=== Starting LDA Program ===\n");
    fflush(stdout);

    // Debug: Verify data loading
    print_first_5_features();
    printf("\nSample pixel data_face80[0][0] = %d\n", data_face80[0][0]);
    fflush(stdout);

    // Declare matrices
    double mean[1024] = {0};
    static double centered[80][1024] = {0};
    static double covariance[1024][1024] = {0};
    static double projected[80][1] = {0};

    // Compute mean and verify
    compute_mean(mean, data_face80);
    printf("\n=== Mean Verification ===\n");
    printf("Mean[0] = %.2f\n", mean[0]);
    printf("Mean[1] = %.2f\n", mean[1]);
    printf("Mean[1023] = %.2f\n", mean[1023]);
    fflush(stdout);

    // Center data
    center_data(centered, data_face80, mean);
    printf("\nCentered data[0][0] = %.2f\n", centered[0][0]);
    fflush(stdout);

    // Compute covariance
    compute_covariance(covariance, centered);
    printf("\nCovariance[0][0] = %.2f\n", covariance[0][0]);
    printf("Covariance[0][1] = %.2f\n", covariance[0][1]);
    fflush(stdout);

    // LDA Projection
    lda_projection(projected, data_face80);

    // Print results with additional checks
    printf("\n=== LDA Projection Results ===\n");
    double min_val = projected[0][0];
    double max_val = projected[0][0];
    double sum = 0;

    for (int i = 0; i < 80; i++) {
        printf("Image %2d: %10.4f", i, projected[i][0]);
        
        // Print class indicator
        if (i == 39) printf(" <-- Class boundary");
        printf("\n");

        // Track stats
        if (projected[i][0] < min_val) min_val = projected[i][0];
        if (projected[i][0] > max_val) max_val = projected[i][0];
        sum += projected[i][0];
    }

    printf("\n=== Projection Statistics ===\n");
    printf("Min: %.4f\n", min_val);
    printf("Max: %.4f\n", max_val);
    printf("Mean: %.4f\n", sum / 80);
    printf("First-last difference: %.4f\n", projected[0][0] - projected[79][0]);

    // === Multi-class LDA Classification ===
    printf("\n=== Multi-class LDA Classification ===\n");

    // Step 1: Compute mean projected value for each class
    double class_means[NUM_CLASSES] = {0};
    for (int c = 0; c < NUM_CLASSES; c++) {
        double sum = 0;
        for (int i = 0; i < SAMPLES_PER_CLASS; i++) {
            int idx = c * SAMPLES_PER_CLASS + i;
            sum += projected[idx][0];
        }
        class_means[c] = sum / SAMPLES_PER_CLASS;
        printf("Class %d Mean: %.4f\n", c + 1, class_means[c]);
    }

    // Step 2: Classify each sample by nearest class mean
    int correct = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        // Find the nearest class mean
        double min_dist = fabs(projected[i][0] - class_means[0]);
        int predicted_label = 1;

        for (int c = 1; c < NUM_CLASSES; c++) {
            double dist = fabs(projected[i][0] - class_means[c]);
            if (dist < min_dist) {
                min_dist = dist;
                predicted_label = c + 1;
            }
        }

        // True label is determined by which class the sample belongs to
        int true_label = (i / SAMPLES_PER_CLASS) + 1;

        // Count correct predictions
        if (predicted_label == true_label) {
            correct++;
        }

        // Print classification results
        printf("Image %2d: Projected = %8.4f | Predicted = Class %d | True = Class %d\n",
               i, projected[i][0], predicted_label, true_label);
    }

    // Print accuracy
    printf("\nAccuracy: %.2f%% (%d / %d correct)\n", (100.0 * correct) / NUM_SAMPLES, correct, NUM_SAMPLES);

    return 0;
}
