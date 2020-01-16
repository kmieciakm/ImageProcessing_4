#include <iostream>
#include "../headers/proc.h"
#include "../headers/converter.h"
#include "../headers/functions.h"
#include "../../CImg/CImg.h"

bool isIntNumber(std::string str){
    for (int i=0 ; i < str.length(); i++){
        if(str[0] == '-')
            continue;
        if ( !isdigit(str[i]) ) 
            return false;
    }
    return true;
}

void DisplayHelpInformations(){
    std::cout << std::endl << "Usage" << std::endl;
    std::cout << "task3 -pathToImage --command [-argument=value [...]]" << std::endl << std::endl;
    std::cout << "Options" << std::endl << std::endl;
    std::cout 
        << "--dft        =  Apply DFT" << std::endl
        << std::endl;
    exit(0);
}

std::string ExtractFilenameFromPath(std::string path){
    std::string filename = "";
    short indexOfSlash = 0;
    for(int characterIndex = path.length()-1; characterIndex >= 0; characterIndex--){
        if(path[characterIndex] == '/'){
            indexOfSlash = characterIndex;
            break;
        }
    }
    for(int currentIndex = indexOfSlash+1; currentIndex<path.length(); currentIndex++){
        filename += path[currentIndex];
    }
    short indexOfDot = 0;
    for(int i = filename.length()-1; i >= 0; i--){
        if(filename[i] == '.'){
            indexOfDot = i;
            break;
        }
    }
    std::string newFilename = "";
    for(int i = 0; i<indexOfDot; i++){
        newFilename += filename[i];
    }
    return newFilename;
}

void ParseCommandAndRun(std::string command, int argumentsAmount, char *arguments[], Photo & photo){
    const int CHANNEL_AMOUNT = photo.GetChannelAmount();

    if(command == "--dft"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            ApplyDFT1D(photo.GetChannel(i));
            Mirror(photo.GetChannel(i));
            photo.SetChannel(i, photo.GetChannel(i).GetScaledChannel());
        }
        photo.SetFilename( photo.GetFilename() + "_dft");
    }else if(command == "--idft"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            ApplyDFT1D(photo.GetChannel(i));
            ApplyIDFT1D(photo.GetChannel(i));
        }
        photo.SetFilename( photo.GetFilename() + "_idft");
    }else if(command == "--lowpass"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            ApplyLowPassFilter(photo.GetChannel(i), 60);
        }
        photo.SetFilename( photo.GetFilename() + "_lowpass");
    }else if(command == "--highpass"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            ApplyHighPassFilter(photo.GetChannel(i), 60);
        }
        photo.SetFilename( photo.GetFilename() + "_highpass");
    }else if(command == "--bandcut"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            ApplyBandCutFilter(photo.GetChannel(i), 25, 50);
        }
        photo.SetFilename( photo.GetFilename() + "_bandcut");
    }else if(command == "--bandpass"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            ApplyBandPassFilter(photo.GetChannel(i), 30, 60);
        }
        photo.SetFilename( photo.GetFilename() + "_bandpass");
    }else if(command == "--edge"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            ApplyEdgeDetectionFilter(photo.GetChannel(i), 90.0, 10.0, 100);
        }
        photo.SetFilename( photo.GetFilename() + "_edge");
    }else if(command == "--phase"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            ApplyPhaseFilter(photo.GetChannel(i), 30, 50);
        }
        photo.SetFilename( photo.GetFilename() + "_phase");
    }else if(command == "--test"){
        for(int i=0; i < CHANNEL_AMOUNT; i++){
            photo.SetChannel(i, BuildMask(photo.GetChannel(i), 90.0, 10.0, 100));
        }
        photo.SetFilename( photo.GetFilename() + "_test");
    }else{
        std::cout << "Illigal command: " << command;
        exit(0);
    }
    
}