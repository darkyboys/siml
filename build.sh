# Build the library
echo "Making the 'siml' directory"
mkdir -p siml 2>/dev/null
echo ""

# Image
echo "Making the library!"
g++ src/image/image.cc -c -o siml/image.o &&\
g++ src/image/imagereader.cc -c -o siml/imagereader.o &&\
g++ src/image/rgb.cc -c -o siml/rgb.o &&\
g++ src/util.cc -c -o siml/util.o &&\
echo ""

# Effects
echo "Making the effects!"
g++ src/effects/brightness.cc -c -o siml/brightness.o &&\
echo ""


# Test
echo "Making the test executable!"
# g++ test/reader.cc -c -o siml/reader.o

# g++ siml/* -o test/reader

g++ test/effect_apply.cc siml/* -o test/effect_apply
echo ""


# benchmark
echo "Making the benchmark executable!"
g++ benchmark/benchmark.cc siml/* -o benchmark/benchmark
echo ""