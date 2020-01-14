#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"
#include <vector>
#include <complex>

void ApplyDFT1D(Channel& channel);
void ApplyIDFT1D(Channel& channel);

void Mirror(Channel& channel);
Channel BuildMask(Channel& channel, double angle, double wideAngle, int radius);
std::complex<double> W(double n, double k, double N);
std::vector<std::complex<double>> DFT1D(std::vector<std::complex<double>> x);
std::vector<std::complex<double>> IDFT1D(std::vector<std::complex<double>> x);

#endif