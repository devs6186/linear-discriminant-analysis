#ifndef LDA_H
#define LDA_H

void compute_mean(double mean[1024], unsigned char data[80][1024]);
void center_data(double centered[80][1024], unsigned char data[80][1024], double mean[1024]);
void compute_covariance(double cov[1024][1024], double centered[80][1024]);
void lda_projection(double projected[80][1], unsigned char data[80][1024]);

#endif
