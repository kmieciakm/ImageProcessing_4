#ifndef CONVERTER_H
#define CONVERTER_H

#include "../../CImg/CImg.h"
#include "proc.h"

void CopyCImgToPhotoObject(cimg_library::CImg<unsigned char> &, Photo &);
void CopyPhotoObjectToCImg(Photo &, cimg_library::CImg<unsigned char> &);
void DisplayImage(cimg_library::CImg<unsigned char> &);

#endif