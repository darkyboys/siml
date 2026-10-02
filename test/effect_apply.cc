#include "../siml.hh"
#include <iostream>

int main(){
    siml::ImageReader reader;
    siml::Image image = reader.read("myfile.png");

    // siml::effect::precision_brightness(image, -10);
    siml::effect::invert(image);
    siml::effect::invert(image);
    // siml::effect::temperature(image, 10);
    // siml::effect::channel_blue_intensity(image, -10);
    // siml::effect::channel_red_intensity(image, 10);

    siml::effect::temperature(image, -10);


    // siml::effect::grayscale(image);
    // siml::effect::brightness(image, 50, siml::NEGATIVE_PIXEL);
    
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