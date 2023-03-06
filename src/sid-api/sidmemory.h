#pragma once
#include <stdint.h>
#include <stdio.h>

#define INIT_SIZE 1024

// Memory Manager that avoid to copy any data. We dynamically allocated any accessd memory in segments of 256 bytes
class SIDMemory {
public:
  SIDMemory() = default;

  void set(int start, int offset, uint8_t *data, size_t len) {
    fprintf(stderr, "Start: 0x%x\n", start);
    fprintf(stderr, "Offset: 0x%x\n", offset);
    this->start = start;
    this->offset = offset;
    this->data = data + offset + 2;
    this->len = len - offset - 2;
  }

  /// Access via index
  uint8_t &operator[](int idx) {
    // data e.g. stored in PROGMEM
    if (idx >= start && idx < start + len) {
      return data[idx - start];
    }

    // Addresses that are not mapped yet
    int dyn_idx = idx / 256;
    int dyn_offset = idx % 256;
    uint8_t *tmp = dynamic_data[dyn_idx];
    if (tmp == 0) {
      // Dynamically allocate memory based on the requested address
      tmp = dynamic_data[dyn_idx] = (uint8_t *)calloc(1, 256);
      fprintf(stderr, "Allocate: 0x%x\n", idx);
    }
    return tmp[dyn_offset];
  }

  /// Release all allocated memory
  void clear() {
    for (int j=0;j<256;j++){
      uint8_t *tmp = dynamic_data[j];
      if (tmp!=nullptr){
        free(tmp);
        dynamic_data[j] = nullptr;
      }
    }
  }

protected:
  uint8_t zero = 0;
  int start;
  int offset;
  int len;
  uint8_t *data;
  uint8_t *dynamic_data[256];
};