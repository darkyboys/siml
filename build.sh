# Build the library
echo "Making the 'siml' directory"
mkdir -p siml 2>/dev/null
echo ""

# Image
echo "Making the library!"
g++ -O3 src/image/image.cc -c -o siml/image.o &&\
g++ -O3 src/image/imagereader.cc -c -o siml/imagereader.o &&\
g++ -O3 src/image/rgb.cc -c -o siml/rgb.o &&\
g++ -O3 src/util.cc -c -o siml/util.o &&\
echo ""

# Effects
echo "Making the effects!"
g++ -O3 src/effects/brightness.cc -c -o siml/brightness.o &&\
g++ -O3 src/effects/grayscale.cc -c -o siml/grayscale.o &&\
echo ""


# Test
echo "Making the test executable!"
# g++ test/reader.cc -c -o siml/reader.o

# g++ siml/* -o test/reader

g++ -O3 test/effect_apply.cc siml/* -o test/effect_apply
echo ""


# benchmark
echo "Making the benchmark executable!"
g++ -O3 benchmark/benchmark.cc siml/* -o benchmark/benchmark
echo ""