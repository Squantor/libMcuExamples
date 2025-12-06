/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main application class
 */
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <nuclone_LPC845BD48_small_SH1106_i2c.hpp>
#include <command_interpreter_number.hpp>
#include <command_value_stack.hpp>
#include <command_handlers.hpp>
#include <console.hpp>

namespace application {

enum class ApplicationState : std::uint8_t {
  idle, /*!< idle state */
};

class Application {
 public:
  Application() : state{ApplicationState::idle} {}
  void Init();
  void Progress();
  ApplicationState GetState() {
    return state;
  }

 private:
  ApplicationState state;
};

extern squLib::console<usart_peripheral> commandConsole;
extern squLib::commandValueStack<8, commandConsole> commandValues;
extern squLib::commandInterpreter<commandHandlers, commandValues, commandConsole> commandInterpreter;
extern Application controller;

}  // namespace application

#endif