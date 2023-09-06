load(
    "//bazel:sxt_component.bzl",
    "sxt_cc_component",
)

sxt_cc_component(
    name = "async_device_resource",
    impl_deps = [
        "//sxt/base/error:panic",
    ],
    test_deps = [
        "//sxt/base/test:unit_test",
    ],
    with_test = False,
    deps = [
        "//sxt/base/type:raw_stream",
        "@local_cuda//:cuda_headers",
        "@local_cuda//:cuda_runtime_static",
    ],
)

sxt_cc_component(
    name = "device_resource",
    impl_deps = [
        "//sxt/base/error:panic",
    ],
    test_deps = [
        "//sxt/base/test:unit_test",
    ],
    deps = [
        "@local_cuda//:cuda_headers",
        "@local_cuda//:cuda_runtime_static",
    ],
)

sxt_cc_component(
    name = "pinned_resource",
    impl_deps = [
        "//sxt/base/error:panic",
    ],
    test_deps = [
        "//sxt/base/test:unit_test",
    ],
    with_test = False,
    deps = [
        "@local_cuda//:cuda_headers",
        "@local_cuda//:cuda_runtime_static",
    ],
)

sxt_cc_component(
    name = "managed_device_resource",
    impl_deps = [
        "//sxt/base/error:panic",
    ],
    test_deps = [
        "//sxt/base/test:unit_test",
    ],
    deps = [
        "@local_cuda//:cuda_headers",
        "@local_cuda//:cuda_runtime_static",
    ],
)
