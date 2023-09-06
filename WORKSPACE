workspace(name = "rls_bltzr_cd")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "rules_cuda",
    commit = "e772553",
    remote = "https://github.com/bazel-contrib/rules_cuda",
)

load("@rules_cuda//cuda:repositories.bzl", "register_detected_cuda_toolchains", "rules_cuda_dependencies")
rules_cuda_dependencies()
register_detected_cuda_toolchains()

git_repository(
    name = "com_github_catchorg_catch2",
    commit = "6f21a3609cea360846a0ca93be55877cca14c86d",
    remote = "https://github.com/catchorg/Catch2",
)
