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

GrayscaleImage::GrayscaleImage(int heightVal, int widthVal)
{
  m_height = heightVal;
  m_width = widthVal;
  
  m_pixels = new uint8_t[m_height * m_width];

  for(int i = 0; i < m_height * m_width; i++){
    m_pixels[i] = 0;
  }
}

GrayscaleImage::~GrayscaleImage(){
  delete[] m_pixels;
}

int GrayscaleImage::getWidth() const
{
  return m_width;
}

int GrayscaleImage::getHeight() const
{
  return m_height;
}

uint8_t GrayscaleImage::getPixel(int row, int col) const
{
  if (row >= m_height || row < 0 || col >= m_width || col < 0)
    throw out_of_range("Bad index in getPixel");
  return m_pixels[row * m_width + col];
}

void GrayscaleImage::setPixel(int row, int col, uint8_t brightness){
  if(row >= m_height || row < 0 || col >= m_width || col < 0){
    throw out_of_range("bad index"); //error message
  }
  
  m_pixels[row * m_width + col] = brightness; 
}

void GrayscaleImage::fill(uint8_t brightness){
  for(int i = 0; i < m_height * m_width; i++){
    m_pixels[i] = brightness;
  }
}

string GrayscaleImage::toString() const{
  string result = "";

  for (int row = 0; row < m_height; row++){
    for (int col = 0; col < m_width; col++){
      result += to_string(getPixel(row, col));
      result += "\t";
    }
    result += "\n";
  }
  return result;
}

bool GrayscaleImage::operator==(const GrayscaleImage& other) const{
  if(m_height != other.m_height || m_width != other.m_width){
    return false;
  }

  for(int i = 0; i < m_height * m_width; i++){
    if(m_pixels[i] != other.m_pixels[i]){
      return false;
    }
  }

  return true;
}

GrayscaleImage GrayscaleImage::addFrame(int padding, uint8_t brightness) const{
  int newHeight = m_height + padding * 2;
  int newWidth = m_width + padding *2;

  GrayscaleImage framedImage(newHeight, new)
}

