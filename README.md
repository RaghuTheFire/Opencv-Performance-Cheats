# OpenCV Performance Demos
Each file is a minimal, focused demo for a single tip.

## Build prerequisites
- OpenCV 4.x (with CUDA for CUDA demos)
- For cudacodec examples, OpenCV must be built with `cudacodec` and your system needs compatible codecs.
- For NVTX profiling example: install `nvtx3` dev package (`-lnvToolsExt` linker flag).

## Compile examples
```bash
# Example
g++ -O3 -std=c++17 01_preallocate.cpp `pkg-config --cflags --libs opencv4` -o demo01
```
Follow the build comment at the top of each file.
