#pragma once
/**
 * Prevent that we use file sizes which are too big
*/
#ifndef MAX_FILE_SIZE
#  define MAX_FILE_SIZE 20000
#endif

/**
 * Memory Allocation Logic
 * 1) dynamic allocation with malloc
 * 2) ESP32 using PSRAM (psmalloc) 
 * 3) static allocation
 * 
*/
#ifndef MEMORY_ALLOCATION_LOGIC
#  define MEMORY_ALLOCATION_LOGIC 3
#endif


