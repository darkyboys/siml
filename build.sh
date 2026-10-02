# Build the library
rm -rf siml
echo "Making the 'siml' directory"
mkdir -p siml 2>/dev/null
echo ""

# Image
echo "Making the library!"
clang++ -O3 src/image/image.cc -c -o siml/image.o &&\
clang++ -O3 src/image/imagereader.cc -c -o siml/imagereader.o &&\
clang++ -O3 src/image/rgb.cc -c -o siml/rgb.o &&\
clang++ -O3 src/util.cc -c -o siml/util.o &&\
echo ""

# Effects
echo "Making the effects!"
clang++ -O3 src/effects/brightness.cc -c -o siml/brightness.o &&\
clang++ -O3 src/effects/precision_brightness.cc -c -o siml/precision_brightness.o &&\
clang++ -O3 src/effects/grayscale.cc -c -o siml/grayscale.o &&\
clang++ -O3 src/effects/invert.cc -c -o siml/invert.o &&\
clang++ -O3 src/effects/temperature.cc -c -o siml/temperature.o &&\
clang++ -O3 src/effects/channel_blue_intensity.cc -c -o siml/channel_blue_intensity.o &&\
clang++ -O3 src/effects/channel_red_intensity.cc -c -o siml/channel_red_intensity.o &&\
clang++ -O3 src/effects/channel_green_intensity.cc -c -o siml/channel_green_intensity.o &&\
echo ""


# Test
echo "Making the test executable!"
# clang++ test/reader.cc -c -o siml/reader.o

# clang++ siml/* -o test/reader

clang++ -O3 test/effect_apply.cc siml/* -o test/effect_apply
echo ""


# benchmark
echo "Making the benchmark executable!"
clang++ -O3 benchmark/benchmark.cc siml/* -o benchmark/benchmark
echo ""