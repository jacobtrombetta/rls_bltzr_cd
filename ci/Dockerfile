FROM nvidia/cuda:12.1.0-devel-ubuntu22.04

WORKDIR /third_party

ADD setup_build_environment.sh /third_party
ADD install_bazel.sh /third_party

RUN /third_party/setup_build_environment.sh
RUN /third_party/install_bazel.sh
