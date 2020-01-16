#include "../headers/functions.h"
#include "../headers/proc.h"
#include <cmath>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

std::complex<double> W(double n, double k, double N){
    std::complex<double> output = (0, 0);
    output.real( cos(2*M_PI*n*k/N) );
    output.imag( -sin(2*M_PI*n*k/N) );

    return output;
}

std::vector<std::complex<double>> DFT1D(std::vector<std::complex<double>> x){
    std::vector<std::complex<double>> xCopy = x;
    int N = x.size();
    std::complex<double> sum = (0.0, 0.0);
    std::complex<double> point;

    for(int k = 0; k < x.size(); k++){
        sum = (0.0, 0.0);
        for(int n = 0; n < N; n++){
            point = xCopy[n];    
            sum += point * W(n, k, N);
        }
        x[k] = sum;
    }

    return x;
}

std::vector<std::complex<double>> IDFT1D(std::vector<std::complex<double>> x){
    std::vector<std::complex<double>> xCopy = x;
    int N = x.size();
    std::complex<double> sum = (0.0, 0.0);
    std::complex<double> point;

    for(int n = 0; n < x.size(); n++){
        sum = (0.0, 0.0);
        for(int k = 0; k < N; k++){
            point = xCopy[k];
            sum += point * W(-n, k, N);
        }
        sum /= N;
        x[n] = sum;
    }

    return x;
}

std::vector<std::complex<double>> FFT1D(std::vector<std::complex<double>> x){
    std::vector<std::complex<double>> xCopy = x;
    int N = x.size();
    int Nhalf = N / 2;
    std::complex<double> sum = (0.0, 0.0);

    for(int k = 0; k < N; k++){
        sum = (0.0, 0.0);
        if( k % 2 == 0){
            for(int n = 0; n < Nhalf; n++){
                sum += (xCopy[n] + xCopy[n + Nhalf]) * W(k, n, N);
            }
        }else{
            for(int n = 0; n < Nhalf; n++){
                sum += ( (xCopy[n] - xCopy[n + Nhalf]) * W(1, n, N) ) * W(k, n, N);
            }
        }
        x[k] = sum;
    }

    return x;
}

std::vector<std::complex<double>> IFFT1D(std::vector<std::complex<double>> x){
    std::vector<std::complex<double>> xCopy = x;
    int N = x.size();
    int Nhalf = N / 2;
    std::complex<double> sum = (0.0, 0.0);

    for(int k = 0; k < N; k++){
        sum = (0.0, 0.0);
        if( k % 2 == 0){
            for(int n = 0; n < Nhalf; n++){
                sum += (xCopy[n] + xCopy[n + N/2]) * W(-k, n, N);
            }
        }else{
            for(int n = 0; n < Nhalf; n++){
                sum += ( (xCopy[n] - xCopy[n + N/2]) * W(-1, n, N) ) * W(-k, n, N);
            }
        }
        sum /= N;
        x[k] = sum;
    }

    return x;
}

void ApplyDFT1D(Channel& channel){
    for(int r = 0; r < channel.GetHeight(); r++){
        std::vector<std::complex<double>> row;
        row = channel.GetRow(r);
        row = DFT1D(row);
        channel.SetRow(r, row);
    }

    for(int c = 0; c < channel.GetWidth(); c++){
        std::vector<std::complex<double>> column;
        column = channel.GetColumn(c);
        column = DFT1D(column);
        channel.SetColumn(c, column);
    }
}

void ApplyIDFT1D(Channel& channel){
    for(int r = 0; r < channel.GetHeight(); r++){
        std::vector<std::complex<double>> row;
        row = channel.GetRow(r);
        row = IDFT1D(row);
        channel.SetRow(r, row);
    }

    for(int c = 0; c < channel.GetWidth(); c++){
        std::vector<std::complex<double>> column;
        column = channel.GetColumn(c);
        column = IDFT1D(column);
        channel.SetColumn(c, column);
    }
}

void ApplyFFT(Channel& channel){
     for(int r = 0; r < channel.GetHeight(); r++){
        std::vector<std::complex<double>> row;
        row = channel.GetRow(r);
        row = FFT1D(row);
        channel.SetRow(r, row);
    }

    for(int c = 0; c < channel.GetWidth(); c++){
        std::vector<std::complex<double>> column;
        column = channel.GetColumn(c);
        column = FFT1D(column);
        channel.SetColumn(c, column);
    }
}

void ApplyIFFT(Channel& channel){
     for(int r = 0; r < channel.GetHeight(); r++){
        std::vector<std::complex<double>> row;
        row = channel.GetRow(r);
        row = IFFT1D(row);
        channel.SetRow(r, row);
    }

    for(int c = 0; c < channel.GetWidth(); c++){
        std::vector<std::complex<double>> column;
        column = channel.GetColumn(c);
        column = IFFT1D(column);
        channel.SetColumn(c, column);
    }
}

void ApplyLowPassFilter(Channel& channel, int radius){
    ApplyFFT(channel);
    Mirror(channel);
    for(int x = 0; x < channel.GetWidth(); x++){
        for(int y = 0; y < channel.GetHeight(); y++){
            if(sqrt(pow((channel.GetWidth()/2 - x), 2) + pow(channel.GetWidth()/2 - y, 2)) > radius)
                channel.SetValue(x,y, (0, 0));
        }
    }
    Mirror(channel);
    ApplyIFFT(channel);
}

void ApplyHighPassFilter(Channel& channel, int radius){
    ApplyFFT(channel);
    Mirror(channel);
    for(int x = 0; x < channel.GetWidth(); x++){
        for(int y = 0; y < channel.GetHeight(); y++){
            if (x == channel.GetWidth() / 2 && y == channel.GetHeight() / 2) 
                continue;
			if (sqrt(pow((channel.GetWidth() / 2 - x), 2) + pow(channel.GetHeight() / 2 - y, 2)) <= radius)
				channel.SetValue(x, y, (0, 0));
        }
    }
    Mirror(channel);
    ApplyIFFT(channel);
}

void ApplyBandPassFilter(Channel& channel, int radiusLow, int radiusHigh){
    ApplyFFT(channel);
    Mirror(channel);
    for(int x = 0; x < channel.GetWidth(); x++){
        for(int y = 0; y < channel.GetHeight(); y++){
            if (x == channel.GetWidth() / 2 && y == channel.GetHeight() / 2) 
                continue;
            if (sqrt(pow((channel.GetWidth() / 2 - x), 2) + pow(channel.GetHeight() / 2 - y, 2)) <= radiusLow) 
                channel.SetValue(x, y, (0, 0)); 
			if (sqrt(pow((channel.GetWidth() / 2 - x), 2) + pow(channel.GetHeight() / 2 - y, 2)) > radiusHigh)
				channel.SetValue(x, y, (0, 0)); 
        }
    }
    Mirror(channel);
    ApplyIFFT(channel);
}

void ApplyBandCutFilter(Channel& channel, int radiusLow, int radiusHigh){
    ApplyFFT(channel);
    Mirror(channel);
    for(int x = 0; x < channel.GetWidth(); x++){
        for(int y = 0; y < channel.GetHeight(); y++){
            if (sqrt(pow((channel.GetWidth() / 2 - x), 2) + pow(channel.GetHeight() / 2 - y, 2)) <= radiusLow) 
                continue;
			if (sqrt(pow((channel.GetWidth() / 2 - x), 2) + pow(channel.GetHeight() / 2 - y, 2)) <= radiusHigh)
				channel.SetValue(x, y, (0, 0)); 
        }
    }
    Mirror(channel);
    ApplyIFFT(channel);
}

void ApplyEdgeDetectionFilter(Channel& channel, double slopeAngle, double widthAngle, int radius){
    ApplyFFT(channel);
    Mirror(channel);
    Channel mask = BuildMask(channel, slopeAngle, widthAngle, radius);
    for(int x = 0; x < channel.GetWidth(); x++){
        for(int y = 0; y < channel.GetHeight(); y++){
            if(mask.GetValue(x, y) == (255.0, 255.0))
                channel.SetValue(x, y, (0, 0));
        }
    }
    Mirror(channel);
    ApplyIFFT(channel);
}

void ApplyPhaseFilter(Channel& channel, int k, int l){
    ApplyFFT(channel);
    Mirror(channel);
    Channel mask = channel;
    for(int x = 0; x < channel.GetWidth(); x++){
        for(int y = 0; y < channel.GetHeight(); y++){
            double realPart = cos( (-2*M_PI*x*k/channel.GetWidth()) + (-2*M_PI*y*l/channel.GetHeight()) + ((k+l) * M_PI) );
            double imagPart = sin( (-2*M_PI*x*k/channel.GetWidth()) + (-2*M_PI*y*l/channel.GetHeight()) + ((k+l) * M_PI) );
            mask.SetValue(x, y, (realPart, imagPart));
            channel.SetValue(x, y, channel.GetValue(x, y) * mask.GetValue(x, y));
        }
    }
    Mirror(channel);
    ApplyIFFT(channel);
}

void Mirror(Channel& channel){
    Channel copyChannel = channel;
    int widthHalf = channel.GetWidth()/2;
    int heightHalf = channel.GetHeight()/2;

    for(int x=0; x<widthHalf; x++){
        for(int y=0; y<channel.GetHeight(); y++){
            channel.SetValue(x + widthHalf, y, copyChannel.GetValue(x, y));
            channel.SetValue(x, y, copyChannel.GetValue(x + widthHalf, y));
        }
    }

    copyChannel = channel;
    for(int x=0; x<channel.GetWidth(); x++){
        for(int y=0; y<heightHalf; y++){
            channel.SetValue(x, y + heightHalf, copyChannel.GetValue(x, y));
            channel.SetValue(x, y, copyChannel.GetValue(x, y + heightHalf));
        }
    }
}

Channel BuildMask(Channel& channel, double angle, double wideAngle, int radius){
    Channel mask = channel;
    int DCx = floor(mask.GetWidth() / 2);
    int DCy = floor(mask.GetHeight() / 2);

    wideAngle /= 2;
    for(int x = 0; x < mask.GetWidth(); x++){
        for(int y = 0; y < mask.GetHeight(); y++){
            mask.SetValue(x, y, (0, 0));
            if( angle+wideAngle == 90 ){
                if( ((x - DCx >= 0) 
                    && - y + DCy >= (tan( (angle - wideAngle) * M_PI / 180.0) * (x - DCx))) 
                || 
                    ((x - DCx <= 0) 
                    && - y + DCy <= (tan( (angle - wideAngle) * M_PI / 180.0) * (x - DCx)))
                ){
                    mask.SetValue(x, y, (255, 255));
                }
            }else if( tan( (angle + wideAngle) * M_PI / 180.0)  >= 0.0 ) {
                if( (  - y + DCy <= (tan( (angle + wideAngle) * M_PI / 180.0) * (x - DCx))
                    && - y + DCy >= (tan( (angle - wideAngle) * M_PI / 180.0) * (x - DCx)) )
                || 
                    (  - y + DCy >= (tan( (angle + wideAngle) * M_PI / 180.0) * (x - DCx))
                    && - y + DCy <= (tan( (angle - wideAngle) * M_PI / 180.0) * (x - DCx)) )  
                ){
                    mask.SetValue(x, y, (255, 255));
                }
            }else{
                if( (  - y + DCy >= (tan( (angle + wideAngle) * M_PI / 180.0) * (x - DCx))
                    && - y + DCy >= (tan( (angle - wideAngle) * M_PI / 180.0) * (x - DCx)) )
                || 
                    (  - y + DCy <= (tan( (angle + wideAngle) * M_PI / 180.0) * (x - DCx))
                    && - y + DCy <= (tan( (angle - wideAngle) * M_PI / 180.0) * (x - DCx)) )  
                ){
                    mask.SetValue(x, y, (255, 255));
                }
            }

            if( pow(x - DCx, 2) + pow(y - DCy, 2) <= radius ){ 
                mask.SetValue(x, y, (0, 0));
            }
            mask.SetValue(DCx, DCy, (255, 255));
        }
    }

    return mask;
}