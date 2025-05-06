#ifndef LDA_H
#define LDA_H

void compute_mean(double mean[400], unsigned char data[80][400]);
void center_data(double centered[80][400], unsigned char data[80][400], double mean[400]);
void compute_covariance(double cov[400][400], double centered[80][400]);
void lda_projection(double projected[80][2], unsigned char data[80][400]);

#endif
