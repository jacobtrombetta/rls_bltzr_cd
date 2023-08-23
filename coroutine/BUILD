load("@rules_cuda//cuda:defs.bzl", "cuda_library")

package(default_visibility = ["//visibility:public"])

cuda_copts = ["-std=c++20"]

cuda_library(
    name = "kernel",
    srcs = ["kernel.cu"],
    hdrs = ["kernel.h", "coroutine.h"],
    copts = cuda_copts,
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [":kernel"],
)
