#include "act/beeper/Beeper.h"

#include <gtest/gtest.h>

namespace {

TEST(Beeper, Instantiation) {
  Beeper();
  SUCCEED();
}
} // namespace