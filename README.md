# Variometer for ESP8266

work in progress...

# build instructions
```bash
bazel build //:vario
```

# test execution

```bash
#run all tests
bazel test //...
# or specific target
bazel test //act/beeper:unit_test
```