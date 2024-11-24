/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file display.hpp
 * @brief display class
 */
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstdint>
#include <array>
#include <span>

namespace sqEmbedded {
template <std::uint16_t width, std::uint16_t height, auto>
class display {
 public:
  display() = default;
  ~display() = default;
  void fill(std::uint8_t pattern) {
    frameBuffer.fill(pattern);
  }

 private:
  std::array<std::uint8_t, width * height> frameBuffer;
};
}  // namespace sqEmbedded

#endif