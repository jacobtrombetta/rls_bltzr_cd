# rls_bltzr_cd
The goal of `rls_bltzr_cd` is to create a minimal, compiling project using [`rules_cuda`](https://github.com/bazel-contrib/rules_cuda) with the clang complier. 

As of right now, I was able to:
- Compile the code on my system using clang-18 and the CUDA toolkit 12.1.
- Recreate the nvcc compiler bug and demonstrate that clang does not exhibit the same issue.
- Compile the code using the Blitzar Docker container. I needed to updated the version of clang as outlined in the [Install clang 18](#install-clang-18) section.

## Prerequisites
### System info
I have a System76 laptop running Ubuntu 20.04 LTS Jammy. The default clang version for Ubuntu 20.04 is 14, so I needed to install clang 18.

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

### Other requirements
If you are running locally, this repo assumes clang 18, `bazelisk`, and the CUDA toolkit are installed on your system.

## rls_bltzr_cd packages
To build all the packages in `rls_bltzr_cd`
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

### Support statically linking the standard c++ library
Follow the Google discussion, [How to link libstdc++ statically with Bazel?](https://groups.google.com/g/bazel-discuss/c/WM2OzIejonc/m/xgmN50ThAAAJ), I've added the following lines to the `.bazelrc` file
```
build --action_env=BAZEL_LINKLIBS='-l%:libstdc++.a'
build --action_env=BAZEL_LINKOPTS='-static-libstdc++ -lm'
```

To test, I added a dependency to `<iostream>` in the `coroutine` component. After compiling with the lines above I verified the shared object dependencies.
```
ldd ./bazel-bin/coroutine/main    
  linux-vdso.so.1 (0x00007ffd75dd0000)
  libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f08db52a000)
  libcudart.so.12 => /usr/local/cuda/targets/x86_64-linux/lib/libcudart.so.12 (0x00007f08db200000)
  libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f08db50a000)
  libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f08dafd8000)
  /lib64/ld-linux-x86-64.so.2 (0x00007f08db70e000)
  libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f08db503000)
  libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f08db4fe000)
  librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007f08db4f9000)
```

Without the build action lines above, `libstdc++.so` is now in the shared object dependencies list.
```
ldd ./bazel-bin/coroutine/main
  linux-vdso.so.1 (0x00007ffcbd956000)
  libcudart.so.12 => /usr/local/cuda/targets/x86_64-linux/lib/libcudart.so.12 (0x00007f9e6aa00000)
  libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f9e6a7d4000)
  libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f9e6ad47000)
  libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f9e6a5ac000)
  /lib64/ld-linux-x86-64.so.2 (0x00007f9e6ae3e000)
  libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f9e6ad40000)
  libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f9e6ad3b000)
  librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007f9e6ad36000)
  libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f9e6ad16000)
```
TODO(jacob.trombetta) - Clang still issued a warning: `clang: warning: argument unused during compilation: '-static-libstdc++'`. I'm not sure if testing the shared object dependencies list on the binary is best way to verify if `libstdc++` has been statically linked. 


## Useful links
- [CUDA Rules for Bazel](https://github.com/bazel-contrib/rules_cuda/tree/main#cuda-rules-for-bazel)
- [LLVM Project](https://github.com/llvm/llvm-project)
