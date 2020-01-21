#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"
#include <vector>
#include <complex>

void ApplyDFT1D(Channel& channel);
void ApplyIDFT1D(Channel& channel);
void ApplyFFT(Channel& channel);
void ApplyIFFT(Channel& channel);
void ApplyLowPassFilter(Channel& channel, int radius);
void ApplyHighPassFilter(Channel& channel, int radius);
void ApplyBandPassFilter(Channel& channel, int radiusLow, int radiusHigh);
void ApplyBandCutFilter(Channel& channel, int radiusLow, int radiusHigh);
void ApplyEdgeDetectionFilter(Channel& channel, double slopeAngle, double widthAngle, int radius);
void ApplyPhaseFilter(Channel& channel, int k, int l);

void Mirror(Channel& channel);
Channel BuildMask(Channel& channel, double angle, double wideAngle, int radius);
std::complex<double> W(double n, double k, double N);
std::vector<std::complex<double>> DFT1D(std::vector<std::complex<double>> x);
std::vector<std::complex<double>> IDFT1D(std::vector<std::complex<double>> x);
void FFT1D(std::vector<std::complex<double>>& x);
std::vector<std::complex<double>> FFT1DRadix4(std::vector<std::complex<double>> x);
std::vector<std::complex<double>> IFFT1DRadix4(std::vector<std::complex<double>> x);
void IFFT1D(std::vector<std::complex<double>>& x);

#endif