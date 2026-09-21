#include "../siml.hh"
#include <iostream>

int main(){
    std::cout << "Reading the image!\n";
    siml::ImageReader reader;

    siml::Image img = reader.read("myfile.png");
    std::cout << "Bit depth: "<<(int)img.bitdepth<<"\n";
    std::cout << "Height: "<<img.height<<"\n";
    std::cout << "Width: "<<img.width<<"\n";

    std::cout << "Writing the image!\n";
    siml::ImageWriter writer;
    writer.write(img, "new.png");

    // std::cout << "Percentage: " << siml::util::normalize_percentage(100);

}