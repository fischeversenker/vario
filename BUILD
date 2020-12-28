load(
    "@platformio_rules//platformio:platformio.bzl",
    "platformio_library",
    "platformio_project",
)

platformio_project(
    name = "vario",
    src = "main.cc",
    board = "nodemcuv2",
    framework = "arduino",
    platform = "espressif8266",
    deps = [
        "//act/beeper:Beeper",
        "//act/blinker:Blinker",
        "//legacy",
    ],
)
