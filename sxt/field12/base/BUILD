load(
    "//bazel:sxt_component.bzl",
    "sxt_cc_component",
)

sxt_cc_component(
    name = "arithmetic_utility",
    test_deps = [
        "//sxt/base/test:unit_test",
    ],
    deps = [
        ":constants",
        "//sxt/base/macro:cuda_callable",
        "//sxt/base/type:int",
        "//sxt/base/type:narrow_cast",
    ],
)

sxt_cc_component(
    name = "byte_conversion",
    impl_deps = [
        ":montgomery",
        ":reduce",
        "//sxt/base/bit:load",
        "//sxt/base/bit:store",
    ],
    is_cuda = True,
    test_deps = [
        ":constants",
        "//sxt/base/test:unit_test",
    ],
    deps = [
        "//sxt/base/macro:cuda_callable",
    ],
)

sxt_cc_component(
    name = "constants",
    with_test = False,
)

sxt_cc_component(
    name = "montgomery",
    impl_deps = [
        ":arithmetic_utility",
        ":constants",
        ":reduce",
    ],
    is_cuda = True,
    test_deps = [
        ":constants",
        "//sxt/base/test:unit_test",
    ],
    deps = [
        "//sxt/base/macro:cuda_callable",
    ],
)

sxt_cc_component(
    name = "reduce",
    impl_deps = [
        ":arithmetic_utility",
        ":constants",
        "//sxt/base/type:narrow_cast",
    ],
    is_cuda = True,
    test_deps = [
        ":constants",
        "//sxt/base/test:unit_test",
    ],
    deps = [
        "//sxt/base/macro:cuda_callable",
    ],
)
