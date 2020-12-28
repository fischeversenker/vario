load(
    "@platformio_rules//platformio:platformio.bzl",
    "platformio_library",
)

platformio_library(
    name = "legacy",
    hdr = "legacy.h",
    add_hdrs = [
        "Beeper.h",
        "Blinker.h",
        "Vario.h",
    ],
    add_srcs = [
        "Beeper.cpp",
        "Blinker.cpp",
        "Vario.cpp",
    ],
    visibility = ["//visibility:public"]
)