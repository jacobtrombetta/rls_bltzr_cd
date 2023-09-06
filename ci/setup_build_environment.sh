#!/bin/bash

set -e

export DEBIAN_FRONTEND="noninteractive"
export TZ=Etc/UTC

apt-get update
apt-get install --no-install-recommends --no-install-suggests -y \
                software-properties-common \
                build-essential \
                git \
                wget

wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
./llvm.sh 18
update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100
update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 100
