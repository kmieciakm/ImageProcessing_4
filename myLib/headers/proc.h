#ifndef PROC_H
#define PROC_H

#include <iostream>
#include <vector>
#include <complex>

class Channel{
private:
    int width;
    int height;
    std::vector<std::vector<std::complex<double>>> fill;

public:
    void SetValue(int _x, int _y, std::complex<double> _value); 
    std::complex<double> GetValue(int _x, int _y);
    double GetMagnitude(int _x, int _y);
    void SetRow(int _rowNumber, std::vector<std::complex<double>> _row);
    std::vector<std::complex<double>> GetRow(int _rowNumber);
    void SetColumn(int _columnNumber, std::vector<std::complex<double>> _column);
    std::vector<std::complex<double>> GetColumn(int _columnNumber);
    int GetWidth();
    int GetHeight();
    Channel GetScaledChannel();
    Channel GetUnScaledChannel();
    Channel(int _width, int _height);
    Channel();
};

class Photo{
private:
    int width;
    int height;
    int channel_amount;
    std::string filename;
    std::vector<Channel> channels;

public:
    int GetWidth();
    int GetHeight();
    int GetChannelAmount();
    std::string GetFilename();
    void SetFilename(std::string);
    void SetChannel(int,Channel);
    Channel& GetChannel(int);
    Photo(int,int,int,std::string);
    Photo();
};

#endif