#include "lda.h"

void compute_mean(double mean[1024], unsigned char data[80][1024]) {
    for (int i = 0; i < 1024; i++) {
        mean[i] = 0;
        for (int j = 0; j < 80; j++) {
            mean[i] += data[j][i];
        }
        mean[i] /= 80.0;
    }
}

void center_data(double centered[80][1024], unsigned char data[80][1024], double mean[1024]) {
    for (int i = 0; i < 80; i++)
        for (int j = 0; j < 1024; j++)
            centered[i][j] = data[i][j] - mean[j];
}

void compute_covariance(double cov[1024][1024], double centered[80][1024]) {
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            cov[i][j] = 0;
            for (int k = 0; k < 80; k++) {
                cov[i][j] += centered[k][i] * centered[k][j];
            }
            cov[i][j] /= 79.0;
        }
    }
}

void lda_projection(double projected[80][1], unsigned char data[80][1024]) {
    int n_features = 1024;
    int n_class1 = 40, n_class2 = 40;

    double mean1[1024] = {0}, mean2[1024] = {0};
    double Sw[1024] = {0}, w[1024];

    for (int i = 0; i < n_class1; i++)
        for (int j = 0; j < n_features; j++)
            mean1[j] += data[i][j];
    for (int j = 0; j < n_features; j++)
        mean1[j] /= n_class1;

    for (int i = n_class1; i < 80; i++)
        for (int j = 0; j < n_features; j++)
            mean2[j] += data[i][j];
    for (int j = 0; j < n_features; j++)
        mean2[j] /= n_class2;

    for (int i = 0; i < n_class1; i++)
        for (int j = 0; j < n_features; j++) {
            double diff = data[i][j] - mean1[j];
            Sw[j] += diff * diff;
        }

    for (int i = n_class1; i < 80; i++)
        for (int j = 0; j < n_features; j++) {
            double diff = data[i][j] - mean2[j];
            Sw[j] += diff * diff;
        }

    for (int j = 0; j < n_features; j++)
        w[j] = (mean1[j] - mean2[j]) / (Sw[j] + 1e-6);

    for (int i = 0; i < 80; i++) {
        projected[i][0] = 0;
        for (int j = 0; j < n_features; j++)
            projected[i][0] += data[i][j] * w[j];
    }
}
