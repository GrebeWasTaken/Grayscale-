//----------------------------------------------------------
// CS162 Assignment Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may be republished without approval.
//----------------------------------------------------------

#include <stdexcept>
#include <string>
using namespace std;

#include "GrayscaleImage.h"


int GrayscaleImage::getWidth() const {

    
    return m_width;
}

int GrayscaleImage::getHeight() const {
    return m_height;
}

uint8_t GrayscaleImage::getPixel(int row, int col) const {
    if(row >= m_height || row < 0 || col >= m_width || col < 0)
        throw out_of_range("Bad index in getPixel");
    return m_pixels[row * m_width + col];
}