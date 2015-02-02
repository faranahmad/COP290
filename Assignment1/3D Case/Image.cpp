#include "Image.h"

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {}

Image::~Image() {
    delete[] pixels;
}
