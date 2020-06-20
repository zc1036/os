
#include <stddef.h>
#include <string.h>
#include <utility>


#include <printf.h>

void terminal_write(const char* data, size_t size);

struct khex {
  long value;
};

struct terminal_file {
  size_t write(const char* const c, const size_t len) {
    terminal_write(c, len);
    return len;
  }
};

template<typename... Args>
size_t kprint(Args&&... args) {
  return kfprint(terminal_file{}, std::forward<Args>(args)...);
}

template<typename File, typename T, typename... Args>
size_t kfprint(File&& f, T&& t, Args&&... args) {
  size_t first = kfprint(f, std::forward<T>(t));
  return first + kfprint(f, std::forward<Args>(args)...);
}

template<typename File>
size_t kfprint(File&& f, const char* const str) {
  return f.write(str, strlen(str));
}

template<typename File>
size_t kfprint(File&& f, const int x) {
  char buf[16];
  sprintf(buf, "%d", x);
  return f.write(buf, strlen(buf));
}

template<typename File>
size_t kfprint(File&& f, const khex x) {
  char buf[16];
  sprintf(buf, "%x", x.value);
  return f.write(buf, strlen(buf));
}

template<typename File>
size_t kfprint(File&& f, const char x) {
  return f.write(&x, 1);
}
