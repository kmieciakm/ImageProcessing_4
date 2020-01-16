#include "../../CImg/CImg.h"
#include "../headers/proc.h"

void CopyCImgToPhotoObject(cimg_library::CImg<unsigned char> & CImgPicture, Photo & photo){
    for(int currentChannel = 0; currentChannel < photo.GetChannelAmount(); currentChannel++){
        Channel newChannel(photo.GetWidth(), photo.GetHeight());
        for(int x=0; x<photo.GetWidth(); x++){
            for(int y=0; y<photo.GetHeight(); y++){
                int pixelValue = static_cast<int>(CImgPicture(x,y,0,currentChannel));
                newChannel.SetValue(x,y,pixelValue);
            }
        }
        photo.SetChannel(currentChannel,newChannel);
    }
}

void CopyPhotoObjectToCImg(Photo & photo, cimg_library::CImg<unsigned char> & CImgPicture){
    unsigned char color[photo.GetWidth()][photo.GetHeight()][3];

    for(int currentChannelID = 0; currentChannelID < photo.GetChannelAmount(); currentChannelID++){
        Channel currentChannel = photo.GetChannel(currentChannelID);
        for(int x=0; x<photo.GetWidth(); x++){
            for(int y=0; y<photo.GetHeight(); y++){
                color[x][y][currentChannelID] = currentChannel.GetMagnitude(x, y);
            }
        }
    }

    for(int x=0; x<photo.GetWidth(); x++)
        for(int y=0; y<photo.GetHeight(); y++)
            CImgPicture.draw_point(x,y,0,color[x][y]);
}

void DisplayImage(cimg_library::CImg<unsigned char> & imageToDisplay){
    cimg_library::CImgDisplay displayWindow(imageToDisplay);
    while (!displayWindow.is_closed()) {
        displayWindow.wait();
    }
}
