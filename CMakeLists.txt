# simple AVR library - any settings need to be done in the root cmake files
add_avr_library(
   can
   can_defs_mcp2515.h
   can_error_mcp2515.c
   can_filter_mcp2515.c
   can_init_mcp2515.c
   can_mcp2515.h
   can_receive_mcp2515.c
   can_send_mcp2515.c
   can_sleep_mcp2515.c
) 

