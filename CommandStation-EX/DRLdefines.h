// DRL: Begin
#ifndef DRL_DEFINES_H
#define DRL_DEFINES_H

#define TRANSMITTER
// #define RECEIVER
#if defined(TRANSMITTER) && defined(RECEIVER)
   #error "ERROR: TRANSMITTER and RECEIVER are both defined"
#endif
#if !defined(TRANSMITTER) && !defined(RECEIVER)
   #error "ERROR: Neither TRANSMITTER or RECEIVER are defined"
#endif
#if defined(TRANSMITTER)
   #pragma message "Compiling for PMA Tx/WCS"
#else
   #pragma message "Compiling for PMA Rx/WCS"
#endif

#undef INSERT_IDLE
#if defined(INSERT_IDLE)
#define ADD_IDLE_PACKET
#endif

#if defined(TRANSMITTER)
   #define FAKE_ACK
   #pragma message "Using FAKE_ACK"
#else
   #undef FAKE_ACK
   #pragma message "NOT using FAKE_ACK"
#endif

#undef RESET_PREAMBLE_COUNT
// This may be a problem
#define ADD_MSGS
#define ADD_MSGS_EPS32

#define ADD_DRIVER
#define ADD_OLED

#define ADD_JOIN
#if defined(ADD_JOIN)
   #pragma message "Joining Tracks"
#endif

#define INSERT_NMRADCC

#if defined(INSERT_NMRADCC)
   #define MSG_MAX 16
   #pragma message "Weaaving in raw DCC messages"
#endif

// Works OK, based on limited testing
#define FORGETLOCO
#if defined(FORGETLOCO)
   #pragma message "Forgetting locos with raw DCC insertion"
#endif

#undef DEBUG

#undef USE_DISCONNECT 
#define ADDSTARESET
#define USE_CONFIG
#define REPEAT_TRY
#undef QUERY_SERVICE
#define USE_REMOVE_ALL
#define USE_FREE
#define DELETE_SERVER

#endif
// DRL: End
