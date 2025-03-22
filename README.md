# Stato

A minimal, single-header C++ library for project status handling, built with type safety and efficiency in mind.

## Features

- **Single-header Integration:** Self explanatory lol
- **Type Safety:** Enforces strong type checking
- **Extensible Design:** Structured in a way that allows easy extension for additional statuses or custom error handling needs
- **`std::format` Support:** Supports `std::format`, `std::print`, and `std::println`

## Usage
```cpp
#include "Stato.hpp"
#include <print>

int main() {
    auto s = Stato::status::success;
    std::println("Status: {}", s);
}
```
