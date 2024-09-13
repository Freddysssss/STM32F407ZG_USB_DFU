#ifndef _LOG_H
#define _LOG_H

#include "rk_def.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"

#define     USING_LOG
#define     USING_RTT

#if defined(USING_LOG) && defined(USING_RTT)
#define LOG_USE_COLOR   1
#define LOG_USE_TIME    1

#include "SEGGER_RTT.h"

#ifndef LOG_TAG
#define LOG_TAG "rtt"
#endif

// #define LOG_I(fmt, ...) SEGGER_RTT_printf(0, "\033[32m[%s][%d] "fmt"\033[0m\n", LOG_TAG, __LINE__, ##__VA_ARGS__)
// #define LOG_W(fmt, ...) SEGGER_RTT_printf(0, "\033[33m[%s][%d] "fmt"\033[0m\n", LOG_TAG, __LINE__, ##__VA_ARGS__)
// #define LOG_E(fmt, ...) SEGGER_RTT_printf(0, "\033[31m[%s][%d] "fmt"\033[0m\n", LOG_TAG, __LINE__, ##__VA_ARGS__)

#define LOG(arg...)      SEGGER_RTT_printf(0,arg)
#define LOG_D(data,len)  SEGGER_RTT_Write(0,data,len)
#define LOG_S(str)       SEGGER_RTT_WriteString(0,str)

/************ use color ****************************/
#if LOG_USE_COLOR
#define LOG_COLOR_CLR        "\033[0m"
#define LOG_COLOR_RED        "\033[31m"
#define LOG_COLOR_GREEN      "\033[32m"
#define LOG_COLOR_YELLOW     "\033[33m"
#define LOG_COLOR_BLUE       "\033[34m"
#define LOG_COLOR_MAGENTA    "\033[35m"
#define LOG_COLOR_CYAN       "\033[36m"

#define LOG_I_COLOR         LOG_COLOR_GREEN
#define LOG_W_COLOR         LOG_COLOR_YELLOW
#define LOG_E_COLOR         LOG_COLOR_RED
#else
#define LOG_COLOR_CLR
#define LOG_I_COLOR         "[I]"
#define LOG_W_COLOR         "[W]"
#define LOG_E_COLOR         "[E]"

#define LOG_COLOR_HEX(info, buffer, size, color)                               \
    do {                                                                       \
        LOG_I("%s, %d bytes -->", info, size);                                 \
        for (uint32_t i = 0; i < size; i++)                                    \
            LOG("%s%02X ", color, *((uint8_t *)((uint32_t)buffer + i)));       \
        LOG("\r\n");                                                           \
    } while(0)

#endif /* End of #if LOG_USE_COLOR */

/************ use time ****************************/
#if LOG_USE_TIME
extern volatile uint32_t log_tick;
char* log_time(void);
#define LOG_I(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_I_COLOR, log_time(), LOG_TAG, __LINE__,##arg)
#define LOG_W(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_W_COLOR, log_time(), LOG_TAG, __LINE__,##arg)
#define LOG_E(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_E_COLOR, log_time(), LOG_TAG, __LINE__,##arg)

#define LOG_G(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_GREEN, log_time(), LOG_TAG, __LINE__,##arg)
#define LOG_Y(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_YELLOW, log_time(), LOG_TAG, __LINE__,##arg)
#define LOG_R(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_RED, log_time(), LOG_TAG, __LINE__,##arg)
#define LOG_B(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_BLUE, log_time(), LOG_TAG, __LINE__,##arg)
#define LOG_M(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_MAGENTA, log_time(), LOG_TAG, __LINE__,##arg)
#define LOG_C(fmt, arg...) LOG("%s[%s][%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_CYAN, log_time(), LOG_TAG, __LINE__,##arg)
#else
#define LOG_I(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_I_COLOR, LOG_TAG, __LINE__,##arg)
#define LOG_W(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_W_COLOR, LOG_TAG, __LINE__,##arg)
#define LOG_E(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_E_COLOR, LOG_TAG, __LINE__,##arg)

#define LOG_G(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_GREEN, LOG_TAG, __LINE__,##arg)
#define LOG_Y(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_YELLOW, LOG_TAG, __LINE__,##arg)
#define LOG_R(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_RED, LOG_TAG, __LINE__,##arg)
#define LOG_B(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_BLUE, LOG_TAG, __LINE__,##arg)
#define LOG_M(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_MAGENTA, LOG_TAG, __LINE__,##arg)
#define LOG_C(fmt, arg...) LOG("%s[%s][%d] "fmt LOG_COLOR_CLR"\n\r", LOG_COLOR_CYAN, LOG_TAG, __LINE__,##arg)

#endif /* End of #if LOG_USE_TIME */

#define LOG_HEX(info, buffer, size)                                            \
    do {                                                                       \
        LOG_I("%s, %d bytes -->", info, size);                                 \
        for (uint32_t i = 0; i < size; i++)                                    \
            LOG("%02X ", *((uint8_t *)((uint32_t)buffer + i)));                \
        LOG("\r\n");                                                           \
    } while(0)
void log_hex(const char *tag, const char *comment, const u8 *buffer, u32 size);
void log_has_key(void (*callback)(int key));


#ifdef USE_LOG_ASSERT

#define LOG_ASSERT(expr) ((expr) ? (void)0 : log_assert_failed(expr ,__FILE__ , __LINE__, __FUNCTION__))
void log_assert_failed(int _errno, const char *file, uint16_t line ,const char *func);
#else
#define LOG_ASSERT(expr) ((void)0)
#endif /* USE_FULL_ASSERT */


#else
#define LOG(...)
#define LOG_I(...)
#define LOG_W(...)
#define LOG_E(...)
#define LOG_G(...)
#define LOG_Y(...)
#define LOG_R(...)
#define LOG_B(...)
#define LOG_M(...)
#define LOG_C(...)
#endif /* end of defined(USING_LOG) && defined(USING_RTT) */

#endif /* end of #ifdef _LOG_H */



