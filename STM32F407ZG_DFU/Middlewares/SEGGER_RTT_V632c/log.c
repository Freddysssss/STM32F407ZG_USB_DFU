#include "log.h"

#ifdef USING_LOG
void log_hex(const char *tag, const char *comment, const u8 *buffer, u32 size)
{
    u32 i;
    SEGGER_RTT_printf(0, "\n[%s] %s, length: %d bytes\n", tag, comment, size);
	for (i = 0; i < size; i++)
	{
		SEGGER_RTT_printf(0, "%02X ", buffer[i]);
	}
	SEGGER_RTT_printf(0, "\n\n");
}

void log_has_key(void (*callback)(int key))
{
    if (SEGGER_RTT_HasKey())
    {
        int key = SEGGER_RTT_WaitKey();
        // LOG_I("key: %d", key);
        if (0 != callback)
        {
            callback(key);
        }
    }
}


#if LOG_USE_TIME
volatile uint32_t log_tick = 0;

#if 1
char* log_time(void)
{
    static char time[] = {"000000.00"};
    uint32_t tick_10ms = log_tick;
    
    sprintf(time, "%06d.%02d", tick_10ms / 100, tick_10ms % 100);
    
    return time;
}
#else
char* log_time(void)
{
    static char time[] = {"000 00:00:00.00"};
    uint32_t tick_10ms = log_tick;
    
    sprintf(time, "%03d %02d:%02d:%02d.%02d",
            tick_10ms / 100 / 60 / 60 / 24,
            tick_10ms / 100 / 60 /60 % 24,
            tick_10ms / 100 / 60 % 60,
            tick_10ms / 100 % 60, 
            tick_10ms % 100);
    
    return time;
}
#endif
#endif

#endif

