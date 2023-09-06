#!/bin/bash

set -e

IMAGE=clang-cuda

# If you have a GPU instance configured in your machine
docker run --rm -v "$PWD":/src -w /src --gpus all --privileged -it "$IMAGE" /bin/bash -l
