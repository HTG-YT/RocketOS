#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#include "kassert.h"
#include "default_vga_driver.h"
#include "kstring.h"


int kprintf(const char *format, ...);
