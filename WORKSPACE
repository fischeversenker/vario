load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "platformio_rules",
    commit = "882a88e4be94a3b0aadf8d694c012ffeec5eb32a",
    remote = "http://github.com/mum4k/platformio_rules.git",
)

http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-release-1.10.0",
    urls = ["https://github.com/google/googletest/archive/release-1.10.0.zip"],
)
