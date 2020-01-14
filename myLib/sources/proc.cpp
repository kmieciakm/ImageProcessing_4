#include "../headers/proc.h"
#include <cmath>

#ifndef M_E
    #define M_E 2.71828182845904523536
#endif

Channel::Channel(int _width, int _height){
    this->width = _width;
    this->height = _height;
    this->fill.resize(_width);
    for(int i=0; i<_width; i++)
        this->fill[i].resize(_height);
}

Channel::Channel(){
    this->width = 0;
    this->height = 0;
}

void Channel::SetValue(int _x, int _y, std::complex<double> _value){
    this->fill[_x][_y] = _value;
}

std::complex<double> Channel::GetValue(int _x, int _y){
    return this->fill[_x][_y];
}

void Channel::SetRow(int _rowNumber, std::vector<std::complex<double>> _row){
    for(int i = 0; i < this->GetWidth(); i++){
        this->fill[i][_rowNumber] = _row[i];
    }
}

std::vector<std::complex<double>> Channel::GetRow(int _rowNumber){
    std::vector<std::complex<double>> row;
    row.resize(this->GetWidth());
    for(int i = 0; i < this->GetWidth(); i++){
        row[i] = this->fill[i][_rowNumber];
    }
    return row;
}

Channel Channel::GetScaledChannel(){
    int R = 0;
    Channel copy(this->GetWidth(), this->GetHeight());

    for(int p = 0; p < this->GetWidth(); p++){
        for(int q = 0; q < this->GetHeight(); q++){
            if(abs(this->fill[p][q]) > R)
                R = abs(this->fill[p][q]);
        }
    }

    for(int p = 0; p < this->GetWidth(); p++){
        for(int q = 0; q < this->GetHeight(); q++){
            double scaledValue = log(abs(this->fill[p][q])) * 255 / log(R);
            copy.SetValue(p, q, scaledValue);
        }
    }
    return copy;
}
 
Channel Channel::GetUnScaledChannel(){
    int R = 0;
    Channel copy(this->GetWidth(), this->GetHeight());

    for(int p = 0; p < this->GetWidth(); p++){
        for(int q = 0; q < this->GetHeight(); q++){
            if(abs(this->fill[p][q]) > R)
                R = abs(this->fill[p][q]);
        }
    }

    for(int p = 0; p < this->GetWidth(); p++){
        for(int q = 0; q < this->GetHeight(); q++){
            double scaledValue = pow( M_E, (abs(this->fill[p][q])* log(R) / 255) );
            // double scaledValue = sqrt(-2*pow(this->fill[p][q].real() + 1, R / 255) + pow(this->fill[p][q].real()+1, 2*R/255) - pow(this->fill[p][q].imag(),2) + 1 );
            copy.SetValue(p, q, scaledValue);
        }
    }
    return copy;
}

void Channel::SetColumn(int _columnNumber, std::vector<std::complex<double>> _column){
    this->fill[_columnNumber] = _column;
}

std::vector<std::complex<double>> Channel::GetColumn(int _columnNumber){
    return this->fill[_columnNumber];
}

double Channel::GetMagnitude(int _x, int _y){
    return abs(this->fill[_x][_y]);
}

int Channel::GetWidth(){
    return this->width;
}

int Channel::GetHeight(){
    return this->height;
}

Photo::Photo(){
    this->width=0;
    this->height=0;
    this->channel_amount=0;
    this->filename="image.bmp";
}

Photo::Photo(int _width,int _height, int _channelAmount, std::string _filename){
    this->width =_width;
    this->height =_height;
    this->channel_amount = _channelAmount;
    this->filename = _filename;
    this->channels.resize(_channelAmount);
    for(int i = 0; i < _channelAmount; i++)
        this->channels[i] = Channel(_width, _height);
}

int Photo::GetHeight(){
    return this->height;
}

int Photo::GetWidth(){
    return this->width;
}

int Photo::GetChannelAmount(){
    return this->channel_amount;
}

std::string Photo::GetFilename(){
    return this->filename;
}

void Photo::SetFilename(std::string _newFilename){
    this->filename = _newFilename;
}

void Photo::SetChannel(int _channelId, Channel _channel){
    this->channels[_channelId] = _channel;
}

Channel& Photo::GetChannel(int _channelIndex){
    return this->channels[_channelIndex];
}