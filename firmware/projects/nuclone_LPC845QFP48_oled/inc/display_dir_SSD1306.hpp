/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file display_dir_SSD1306.hpp
 * @brief display middle ware for SSD1306, direct mode only
 */
#ifndef DISPLAY_DIR_SSD1306_HPP
#define DISPLAY_DIR_SSD1306_HPP

#include <cstdint>
#include <array>
#include <span>

namespace libMcuMiddleware::display {
template <auto& config, auto& driver>
// TODO maybe rename to displayDriverColumn based?
class displayDirSSD1306 {
 public:
  displayDirSSD1306() {};
  void fill(std::uint32_t pattern) {
    buffer.fill(static_cast<std::uint8_t>(pattern));
    driver.setColumnAddress(0, config.xSize - 1);
    driver.setPageAddress(0, (config.ySize / 8) - 1);
    for (uint32_t y = 0; y < config.ySize; y += 8) {
      for (uint32_t x = 0; x < config.xSize; x += 16) {
        driver.sendData(buffer);
      }
    }
  }
  // TODO write block (only on divisible by 8 boundary)
  void writeBlock(std::uint32_t xStart, std::uint32_t yStart, std::uint32_t xEnd, std::uint32_t yEnd,
                  std::span<const std::uint8_t> data) {
    driver.setColumnAddress(xStart, xEnd - 1);
    driver.setPageAddress(yStart / 8, yEnd / 8);
    driver.sendData(data);
  }
  void setPixel(std::uint32_t x, std::uint32_t y, std::uint32_t color) {
    static_assert(false, "not implemented for this display");
  }
  void getPixel(std::uint32_t x, std::uint32_t y, std::uint32_t& color) {
    static_assert(false, "not implemented for this display");
  }

 private:
  std::array<std::uint8_t, 16> buffer; /*!< buffer for display operations*/
};
}  // namespace libMcuMiddleware::display

#endif