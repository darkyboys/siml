#include "../siml.hh"
#include <iostream>

int main(){
    siml::ImageReader reader;
    siml::Image image = reader.read("myfile.png");

    siml::effect::grayscale(image);
    siml::effect::brightness(image, 50, siml::NEGATIVE_PIXEL);
    
    // siml::effect::brightness(image, 100);
    // siml::effect::brightness(image, 50, siml::PIXEL);
    // siml::effect::brightness(image, 50, siml::PIXEL);
    // siml::effect::brightness(image, 50, siml::PIXEL);
    // siml::effect::brightness(image, 50, siml::PIXEL);
    // siml::effect::brightness(image, 50, siml::PIXEL);
    // siml::effect::brightness(image, 50, siml::PIXEL);
    // siml::effect::brightness(image, 50, siml::PIXEL);

    siml::ImageWriter writer;
    writer.write(image, "mod.png");
}