#include <iostream>
#include "CImg/CImg.h"
#include "myLib/headers/converter.h"
#include "myLib/headers/proc.h"
#include "myLib/headers/parser.h"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc == 2 && (std::string)argv[1]=="--help")
        DisplayHelpInformations();
    
    cimg_library::cimg::exception_mode(0); 
    try{
        cimg_library::CImg<unsigned char> loadedPicture(argv[1]);
        std::string command;

        if(argv[2]){
            command = (std::string)argv[2];
        }else{
            std::cout<<"Command not given";
            exit(0);
        }
        
        // create Photo object and convert Cimg into it 
        std::string fileName = ExtractFilenameFromPath((std::string)argv[1]);
        Photo myPicture(loadedPicture.width(), loadedPicture.height(), loadedPicture.spectrum(), fileName);
        CopyCImgToPhotoObject(loadedPicture,myPicture);

        // parsing command
        ParseCommandAndRun(command, argc, argv, myPicture);        

        // convert Photo object to Cimg, dispaly and save
        cimg_library::CImg<unsigned char> img(myPicture.GetWidth(), myPicture.GetHeight(), 1, myPicture.GetChannelAmount());
        CopyPhotoObjectToCImg(myPicture,img);
        DisplayImage(img);
        std::string savePath = "./output/" + myPicture.GetFilename() + ".bmp";
        img.save(savePath.c_str());

    }catch(cimg_library::CImgException& e){
        std::cout << "Image does not exist.";
        exit(0);
    }

    return 1;
}