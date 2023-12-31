load(
    "//bazel:sxt_component.bzl",
    "sxt_cc_component",
)

sxt_cc_component(
    name = "multiproduct",
    impl_deps = [
        "//sxt/base/macro:cuda_callable",
        "//sxt/algorithm/base:gather_mapper",
        "//sxt/curve21/operation:accumulator",
        "//sxt/curve21/operation:neg",
        "//sxt/execution/async:future",
        "//sxt/multiexp/multiproduct_gpu:multiproduct",
    ],
    is_cuda = True,
    with_test = False,
    deps = [
        "//sxt/base/container:span",
        "//sxt/base/type:raw_stream",
        "//sxt/execution/async:future_fwd",
    ],
)

sxt_cc_component(
    name = "multiexponentiation",
    impl_deps = [
        ":multiproduct",
        ":pippenger_multiproduct_solver",
        "//sxt/base/container:blob_array",
        "//sxt/curve21/operation:accumulator",
        "//sxt/execution/async:future",
        "//sxt/curve21/type:element_p3",
        "//sxt/memory/management:managed_array",
        "//sxt/multiexp/curve:multiexponentiation_cpu_driver",
        "//sxt/multiexp/curve:multiproducts_combination",
        "//sxt/multiexp/pippenger:multiexponentiation",
        "//sxt/base/device:memory_utility",
        "//sxt/base/device:event",
        "//sxt/base/device:event_utility",
        "//sxt/base/iterator:index_range",
        "//sxt/memory/resource:device_resource",
        "//sxt/memory/resource:async_device_resource",
        "//sxt/multiexp/pippenger:multiproduct_decomposition_gpu",
        "//sxt/multiexp/base:exponent_sequence",
        "//sxt/execution/async:coroutine",
        "//sxt/execution/device:device_viewable",
        "//sxt/execution/device:for_each",
        "//sxt/base/device:stream",
    ],
    test_deps = [
        "//sxt/memory/management:managed_array",
        "//sxt/curve21/type:element_p3",
        "//sxt/base/test:unit_test",
        "//sxt/multiexp/test:multiexponentiation",
        "//sxt/memory/resource:managed_device_resource",
        "//sxt/execution/async:future",
        "//sxt/execution/schedule:scheduler",
    ],
    deps = [
        "//sxt/base/container:span",
        "//sxt/execution/async:future_fwd",
        "//sxt/memory/management:managed_array_fwd",
    ],
)

sxt_cc_component(
    name = "pippenger_multiproduct_solver",
    impl_deps = [
        "//sxt/base/container:blob_array",
        "//sxt/execution/async:future",
        "//sxt/memory/management:managed_array",
        "//sxt/multiexp/curve:multiproduct_cpu_driver",
        "//sxt/multiexp/pippenger_multiprod:multiproduct",
        "//sxt/multiexp/pippenger_multiprod:active_offset",
        "//sxt/curve21/type:element_p3",
        "//sxt/multiexp/index:index_table",
        "//sxt/multiexp/index:reindex",
        "//sxt/multiexp/base:generator_utility",
    ],
    test_deps = [
        "//sxt/base/container:blob_array",
        "//sxt/multiexp/index:index_table",
        "//sxt/curve21/type:element_p3",
        "//sxt/curve21/operation:overload",
        "//sxt/ristretto/type:literal",
        "//sxt/base/test:unit_test",
        "//sxt/memory/management:managed_array",
        "//sxt/execution/async:future",
    ],
    deps = [
        "//sxt/curve21/operation:add",
        "//sxt/curve21/operation:double",
        "//sxt/curve21/operation:neg",
        "//sxt/multiexp/curve:multiproduct_solver",
    ],
)
