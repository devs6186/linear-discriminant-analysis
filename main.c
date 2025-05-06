#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data_face80.h"
#include "lda.h"

int main() {
    // Initialize random data (if not using real data)
    srand(time(0));
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 400; j++) {
            data_face80[i][j] = rand() % 256;  // Random values (0-255)
        }
    }

    // Debug: Print first 3 pixels of first 3 images
    printf("=== Data Sample ===\n");
    for (int i = 0; i < 3; i++) {
        printf("Image %d: %d, %d, %d...\n", 
               i, data_face80[i][0], data_face80[i][1], data_face80[i][2]);
    }

    // Compute LDA
    double mean[400];
    double centered[80][400];
    double covariance[400][400];
    double projected[80][2];

    compute_mean(mean, data_face80);
    center_data(centered, data_face80, mean);
    compute_covariance(covariance, centered);
    lda_projection(projected, data_face80);

    // Print LDA results
    printf("\n=== LDA Projection ===\n");
    for (int i = 0; i < 80; i++) {
        printf("Image %2d: (%.2f, %.2f)\n", i, projected[i][0], projected[i][1]);
    }

    return 0;
}