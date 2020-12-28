load("@platformio_rules//platformio:platformio.bzl", "platformio_library")

platformio_library(
    name = "Beeper",
    src = "Beeper.cc",
    hdr = "Beeper.h",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cc_beeper",
    srcs = ["Beeper.cc"],
    hdrs = ["Beeper.h"],
    deps = ["//test/mocks"],
)

cc_test(
    name = "unit_test",
    srcs = ["Beeper_test.cc"],
    deps = [
        ":cc_beeper",
        "@com_google_googletest//:gtest_main",
    ],
)
