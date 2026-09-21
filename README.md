# SIML

**SIML — Simple Image Manipulation Library for C++**

A lightweight, easy-to-use image manipulation library for C++ with a focus on **simplicity, transparency, and performance**.

SIML provides a straightforward API for reading images, applying effects, and writing the result back to disk.

SIML is also completely open source and comes under public domain with the CC0-V1-Universal License (Please make sure to check the LICENSE file for more information.)

---

## Repository

[GitHub Repository — darkyboys/siml](https://github.com/darkyboys/siml)

---

## Features

* Simple C++ API
* Image manipulation through `siml::effect`
* In-place image effects
* Support for multiple pixel bit depths
* STL-based implementation
* No external image-processing framework required
* Performance-oriented implementation
* Cross-platform design
* **Linux-first development**
* Designed to be easy to understand and use

---

## Platform Support

SIML is designed to be **cross-platform** and aims to avoid unnecessary platform-specific dependencies.

However, development and testing currently happen primarily on **Linux**.

> **Cross-platform by design. Linux-first in development.**

Linux is currently the primary development environment, so Linux users may get the smoothest experience while the project is being developed.

---

## Basic Usage

```cpp
#include <siml.hh>

int main()
{
    siml::ImageReader reader;

    siml::Image image =
        reader.read("input.png");

    siml::effect::brightness(
        image,
        10,
        siml::PIXEL
    );

    siml::ImageWriter writer;

    writer.write(
        image,
        "output.png"
    );
}
```

The basic workflow is:

```text
Read → Manipulate → Write
```

---

## Image Handling

SIML provides an `Image` type for storing image data.

Images contain information such as:

* Width
* Height
* Bit depth
* Pixel data

SIML supports 8-bit, 16-bit, and 32-bit pixel storage.

Only the pixel buffer corresponding to the image's active bit depth is used.

---

## Effects

Image manipulation functionality lives under:

```cpp
siml::effect
```

For example:

```cpp
siml::effect::brightness(
    image,
    10,
    siml::PIXEL
);
```

Effects operate directly on the supplied `Image`.

---

## Brightness

Currently, SIML provides a brightness effect.

### Pixel mode

```cpp
siml::effect::brightness(
    image,
    10,
    siml::PIXEL
);
```

### Percentage mode

```cpp
siml::effect::brightness(
    image,
    10,
    siml::PERCENTAGE
);
```

The first argument is always the image being manipulated.

---

## Design Philosophy

SIML aims to keep image manipulation simple.

Instead of exposing complicated processing pipelines, the API is designed around direct operations:

```cpp
effect(image, value, unit);
```

The goal is that using SIML should require very little knowledge of its internal implementation.

### Performance First

SIML is designed with performance in mind.

For example, the brightness effect operates directly on the underlying pixel buffer using a tight loop rather than introducing unnecessary per-pixel abstractions.

A benchmark using a **1920×1080 image** currently measures the brightness effect at roughly:

```text
Average : ~14.48 ms
Median  : ~14.04 ms
```

across 1000 iterations in the current benchmark environment.

Benchmark results depend on hardware, compiler, optimization settings, operating system, and image representation, so these numbers should be treated as a reference rather than a universal performance guarantee.

---

## Building

SIML currently uses simple shell scripts and `g++` for building.

### Requirements

You need:

* A C++ compiler with C++ support
* `g++`
* `ar`
* A Unix-like shell environment

Linux is currently the primary development environment.

### Build the library

To build the static library:

```bash
./mklib.sh
```

This compiles the source files into object files and creates:

```text
siml/libsiml.a
```

Intermediate object files are stored separately:

```text
objects/
```

The build process is:

```text
src/*.cc
    ↓
objects/*.o
    ↓
ar
    ↓
siml/libsiml.a
```

### Build everything

To build the current development/test setup:

```bash
./build.sh
```

### Run tests

```bash
./test.sh
```

### Run benchmarks

```bash
./benchmark.sh
```

### Clean build artifacts

```bash
./clean.sh
```

---

## Using the Static Library

After running:

```bash
./mklib.sh
```

SIML produces:

```text
siml/libsiml.a
```

You can link it into your own C++ program with:

```bash
g++ main.cc -I. -Lsiml -lsiml -o myprogram
```

Where:

* `-I.` tells the compiler where to find SIML headers
* `-Lsiml` tells the linker where to find the library
* `-lsiml` links `libsiml.a`

Then run:

```bash
./myprogram
```

---

## Project Structure

```text
siml/
├── objects/
│   ├── image.o
│   ├── imagereader.o
│   ├── rgb.o
│   ├── util.o
│   └── brightness.o
│
├── siml/
│   └── libsiml.a
│
├── benchmark/
│   ├── benchmark.cc
│   └── myfile.png
│
├── effects/
│   └── brightness.hh
|   --- More effects as well ---
│
├── image/
│   ├── image.hh
│   ├── imagereader.hh
│   └── rgb.hh
│
├── src/
│   ├── effects/
│   │   └── brightness.cc
│   └── image/
│       ├── image.cc
│       ├── imagereader.cc
│       └── rgb.cc
│
├── test/
│   ├── effect_apply.cc
│   ├── reader.cc
│   └── ...
│
├── siml.hh
├── util.hh
├── util.cc
├── build.sh
├── mklib.sh
├── clean.sh
├── benchmark.sh
├── test.sh
├── README.md
└── LICENSE
```

The project separates:

* **Public headers** from implementation
* **Source code** from build artifacts
* **Tests** from benchmarks
* **Image functionality** from effects
* **Intermediate object files** from the final static library

---

## Testing

SIML keeps correctness testing separate from performance benchmarking.

Tests can be found in:

```text
test/
```

Performance benchmarks can be found in:

```text
benchmark/
```

This keeps questions of **correctness** and **performance** separate.

---

## License

SIML is dedicated to the public domain using the **CC0 1.0 Universal** dedication.

See [`LICENSE`](LICENSE) for the complete legal text.

You are free to use, modify, copy, distribute, and build upon the work to the extent permitted by the CC0 dedication.

The images are also mine (Tanishq Pal) and i am happy to release them under the CC0 License as well! So feel free to do what you want 😃 You can maybe use them as a learning tool like i did to learn color grading.

---

## Status

SIML is currently under active development.

The API and internal implementation may change as the library grows.

More image manipulation effects and functionality are planned for future versions.

---

## Author

**Tanishq Pal**

SIML was founded on **September 21, 2026**.

---

> **SIML — Simple image manipulation, without the unnecessary complexity.**
