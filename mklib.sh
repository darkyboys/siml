#!/bin/bash

# Build SIML static library

echo "Building SIML static library..."
echo ""

# Create directories
mkdir -p objects 2>/dev/null
mkdir -p siml 2>/dev/null

echo "Compiling image sources..."

g++ -O3 src/image/image.cc -c -o objects/image.o && \
g++ -O3 src/image/imagereader.cc -c -o objects/imagereader.o && \
g++ -O3 src/image/rgb.cc -c -o objects/rgb.o && \
g++ -O3 src/util.cc -c -o objects/util.o && \

echo ""
echo "Compiling effects..."

g++ -O3 src/effects/brightness.cc -c -o objects/brightness.o && \
g++ -O3 src/effects/grayscale.cc -c -o objects/grayscale.o && \

echo ""
echo "Creating static library..."

ar rcs siml/libsiml.a objects/*.o

echo ""
echo "SIML static library created:"
echo "  siml/libsiml.a"