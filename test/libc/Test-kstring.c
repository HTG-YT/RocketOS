#include <multiboot.h>


#include <stdbool.h>
#include <stdint.h>

#include "unity.h"
#include "kstring.h"
#include "hardware_io.h"
#include "vga_driver.h"


uint16_t buffer[2048u];

void setUp(void) {
    terminal_initialize_test(buffer); //so that printing doesn't seg fault
}
void tearDown(void) {}


//for base 10 numbers
void kint_to_string_util(const char *const expected_text, const int32_t number) {
    char str[128u];
    kint_to_string(number, str, 128u, 10u, false);
    const size_t size_of_str = kstrlen(expected_text);
    TEST_ASSERT_EQUAL_MEMORY(expected_text, str, size_of_str);
}


void test_cstrlen(void) {
    TEST_ASSERT_EQUAL_INT(5, kstrlen("hello"));
    TEST_ASSERT_EQUAL_INT(0, kstrlen(""));
    TEST_ASSERT_EQUAL_INT(3, kstrlen("foo"));
    TEST_ASSERT_EQUAL_INT(1, kstrlen("4"));

    //testing that the asserts are triggered
    TEST_ASSERT_EQUAL_INT(0, kstrlen(NULL));
}

void test_cstrcmp(void) {
    TEST_ASSERT_EQUAL_INT(0, kstrcmp("a", "a"));
    TEST_ASSERT_LESS_THAN_INT32(0, kstrcmp("a", "b"));
    TEST_ASSERT_GREATER_THAN_INT32(0, kstrcmp("b", "a"));
    TEST_ASSERT_EQUAL_INT(0, kstrcmp("b", "b"));

    TEST_ASSERT_EQUAL_INT(0, kstrcmp("sdfgs", "sdfgs"));
    TEST_ASSERT_LESS_THAN_INT32(0, kstrcmp("lkjjio", "lkjkio"));
    TEST_ASSERT_GREATER_THAN_INT32(0, kstrcmp("sbgsd", "sbgjd"));

    //testing that the asserts are triggered
    TEST_ASSERT_EQUAL_INT(0, kstrcmp(NULL, NULL));
}

void test_kint_to_string(void) {
    kint_to_string_util("-12735", -12735);
    kint_to_string_util("784032", 784032);
    kint_to_string_util("0", 0);

    //negative zero should be the same as positive zero since this is integers.
    //contrast this with floats where 0.0f != -0.0f
    kint_to_string_util("0", -0);
}


void kernel_early(const uint32_t mboot_magic, const multiboot_info_t *const mboot_header) {
    terminal_initialize();
    if (mboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        terminal_writestring_color("Invalid Multiboot Magic!\n", VGA_COLOR_RED);
    } else {
        terminal_writestring("The multiboot structure was loaded properly\n");
    }
}

void kernel_main(void) {
    serial_init();
    UNITY_BEGIN();
    RUN_TEST(test_cstrlen);
    RUN_TEST(test_cstrcmp);
    RUN_TEST(test_kint_to_string);
    UNITY_END();
    outb(0xf4, 0x10);
}
