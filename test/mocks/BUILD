load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "mocks",
    srcs = ["Arduino.cc"],
    hdrs = ["Arduino.h"],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_googletest//:gtest",
    ],
)
