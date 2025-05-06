#include <stdio.h>
#include "lda.h"

void compute_mean(double mean[400], unsigned char data[80][400]) {
    for (int i = 0; i < 400; i++) {
        mean[i] = 0;
        for (int j = 0; j < 80; j++) {
            mean[i] += data[j][i];
        }
        mean[i] /= 80.0;
    }
}

void center_data(double centered[80][400], unsigned char data[80][400], double mean[400]) {
    for (int i = 0; i < 80; i++)
        for (int j = 0; j < 400; j++)
            centered[i][j] = data[i][j] - mean[j];
}

void compute_covariance(double cov[400][400], double centered[80][400]) {
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 400; j++) {
            cov[i][j] = 0;
            for (int k = 0; k < 80; k++) {
                cov[i][j] += centered[k][i] * centered[k][j];
            }
            cov[i][j] /= 79.0;
        }
    }
}

// Placeholder: This would ideally do eigenvalue decomposition
void lda_projection(double projected[80][2], unsigned char data[80][400]) {
    for (int i = 0; i < 80; i++) {
        projected[i][0] = data[i][0];  // naive projection
        projected[i][1] = data[i][1];
    }
}
