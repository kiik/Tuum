
#include <chrono>
#include <ctime>

using namespace std::chrono;

auto T0 = high_resolution_clock::now();

size_t millis() {
  auto ep = high_resolution_clock::from_time_t(0);
  auto now = high_resolution_clock::now();
  auto msec = duration_cast<milliseconds>(now - ep).count();
  return (size_t)msec;
}

long long micros() {
  auto elapsed = std::chrono::high_resolution_clock::now() - T0;
  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}
