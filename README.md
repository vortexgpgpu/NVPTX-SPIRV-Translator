# NVPTX-SPIR-V Translator

We implement a translator that support translating [NVPTX](https://llvm.org/docs/NVPTXUsage.html) to [SPIR-V](https://www.khronos.org/registry/spir-v/). This translator is modified from [LLVM-SPIR-V Translator](https://github.com/KhronosGroup/SPIRV-LLVM-Translator).

## Requirements

Here are the environment requirements for building&executing the translators. Using environments with other versions may require modification in source code.

- Ubuntu 16.0.4
- LLVM 10.0.1
- CMake 3.5.1
- gcc 7.5.0

## Build Instructions

```
git clone https://github.com/gthparch/NVPTX-SPIRV-Translator
mkdir NVPTX-SPIRV-Translator/build
cd NVPTX-SPIRV-Translator/build
cmake .. -DLLVM_DIR=<llvm_build_dir>/lib/cmake/llvm/
make llvm-spirv -j`nproc`
```

Where `llvm_build_dir` is the LLVM build directory.

## Run Instructions for `llvm-spirv`

To translate a NVPTX IR (`nvptx_input.bc`) to a SPIR-V (`spirv_output.spv`), execute the following command:

```
llvm-spirv -o spirv_output.spv nvptx_input.bc
```

We maintain the code for converting SPIR-V to OpenCL IR in the originally translator. To translate a SPIRV IR (`spirv_input.spv`) to a OpenCL IR (`ocl_output.bc`), execute the following command:

```
llvm-spirv -r -o ocl_output.bc spirv_input.spv
```
