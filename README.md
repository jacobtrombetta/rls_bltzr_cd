# rls_bltzr_cd
The goal of `rls_bltzr_cd` is to create a minimal, compiling project using [`rules_cuda`](https://github.com/bazel-contrib/rules_cuda) with the clang complier. 

As of right now, I can:
- Compile the code on my system using clang-18 and the CUDA toolkit 12.1.
- Recreate the nvcc compiler bug and demonstrate that clang does not exhibit the same issue.

## Prerequisites
### System info
I have a System76 laptop running Ubuntu 20.04 LTS Jammy. The default clang version for Ubuntu 20.04 is 14. The CUDA toolkit I tested with is 12.1.

### Install clang 18
I used the LLVM repository script for clang since Ubuntu 20.04 only allows you to install clang versions up to clang 15 [link](https://linux.how2shout.com/how-to-install-clang-on-ubuntu-linux/).
```
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 18
```

I set clang 18 as my default compiler [link](https://linux.how2shout.com/how-to-install-clang-on-ubuntu-linux/).
```
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 100
```

Note, setting the default clang compiler version to 18 might be optional if the following lines are added to `.bazelrc`.
```
build --action_env CC=/usr/bin/clang-18
build --action_env CXX=/usr/bin/clang++-18
```

### Other requirements
This repo assumes `bazelisk` and the CUDA toolkit are installed on your system.

## rls_bltzr_cd packages
To build all the packages in `rls_bltzr_cd`:
```
bazelisk build //...
```

### basic
The `basic` package contains a simple CUDA kernel. It is copied from the [rules_cuda repo](https://github.com/bazel-contrib/rules_cuda/tree/main/examples/basic). It builds a CUDA_LIBRARY and CC_BINARY. The `basic` package was used as an A/B test with the `coroutine` package.

To build:
```
bazelisk build //basic:main
```

To run:
```
bazel-bin/basic/main
```

### coroutine
The `coroutine` package contains a simple CUDA kernel with a C++20 coroutine. It builds a CUDA_LIBRARY and CC_BINARY. It is the code that the nvcc compiler cannot build successfully, [see bug](https://developer.nvidia.com/nvidia_bug/4251336).

To build:
```
bazelisk build //coroutine:main
```

To run:
```
bazel-bin/coroutine/main
```

To reproduce the compiler bug, change the default compiler to nvcc. To do this, comment out the following lines in the `.bazelrc` file:
```
build --config=clang
build --action_env CC=/usr/bin/clang-18
build --action_env CXX=/usr/bin/clang++-18
```

The nvcc compiler only has support up to clang 16. f you don't comment out the lines referencing clang 18, the nvcc compiler issues the follow: `error: -- unsupported clang version! clang version must be less than 16 and greater than 3.2`.

### cmath error
If you get a clang cannot find `cmath` error, try to install `libstdc++-12-dev` [link](https://stackoverflow.com/questions/22752000/clang-cmath-file-not-found).
```
sudo apt install libstdc++-12-dev
``` 
Note, I ran into this error before I upgraded my clang compiler to 18, so I am not sure this is an issue.

### Clang warning
Just an FYI, clang issues the following warning `clang: warning: CUDA version 12.1 is only partially supported` when building packages in `rls_bltzr_cd`.

### Clang will attempt to use CUDA toolkit 12.2 as if it were 12.1
As of two months ago, Intel LLVM project's instructions for compiling CUDA with Clang states:

> "CUDA is supported since llvm 3.9. Clang currently supports CUDA 7.0 through 12.1. If clang detects a newer CUDA version, it will issue a warning and will attempt to use detected CUDA SDK it as if it were CUDA 12.1."

I have not been able to test this yet. See [link](https://github.com/intel/llvm/blob/e600d7922489635290fd2cb63300d865fc72ee72/llvm/docs/CompileCudaWithLLVM.rst#prerequisites).

## Useful links
- [CUDA Rules for Bazel](https://github.com/bazel-contrib/rules_cuda/tree/main#cuda-rules-for-bazel)
- [Compiling CUDA with Clang](https://github.com/intel/llvm/blob/e600d7922489635290fd2cb63300d865fc72ee72/llvm/docs/CompileCudaWithLLVM.rst#compiling-cuda-with-clang) 
