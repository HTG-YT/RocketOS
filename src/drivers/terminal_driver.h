#pragma once
#include "vga_driver.h"

#define PROMPT "> "

size_t start_of_command;
size_t end_of_command;

void terminal_start(void);
void terminal_end(void);
void terminal_process_command(void);

const char* get_command(void);