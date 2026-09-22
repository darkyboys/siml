# Build the library
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
clang++ -O3 src/effects/grayscale.cc -c -o siml/grayscale.o &&\
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