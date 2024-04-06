// DRL: Begin
#ifndef DRL_DEFINES_H
#define DRL_DEFINES_H

#undef INSERT_IDLE
#define FAKE_ACK

#undef RESET_PREAMBLE_COUNT
#define ADD_IDLE_PACKET
// This may be a problem
#define ADD_MSGS
#define ADD_MSGS_EPS32

#define ADD_DRIVER
#define ADD_OLED

#define ADD_JOIN
#define INSERT_NMRADCC

#if defined(INSERT_NMRADCC)
#define MSG_MAX 16
#endif

// Works OK, based on limited testing
#define FORGETLOCO

#undef DEBUG

#endif
// DRL: End
