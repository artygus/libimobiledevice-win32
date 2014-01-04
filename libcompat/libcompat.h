#ifndef LIBCOMPAT_H
#define LIBCOMPAT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <crtdefs.h>
#include <stdint.h>
#ifndef _WINSOCKAPI_
#include <winsock.h>
#include <windows.h>
#endif
#include "endianess.h"

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 
#ifdef WIN32
#define __func__ __FUNCTION__
#endif

// time
struct timezone
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};

#ifndef snprintf
#define snprintf _snprintf
#endif

int gettimeofday(struct timeval *tv, struct timezone *tz);

// inet
typedef uint32_t tcp_seq; 

/*
 * TCP header.
 * Per RFC 793, September, 1981.
 */
struct tcphdr {
    u_short th_sport;               /* source port */
    u_short th_dport;               /* destination port */
    tcp_seq th_seq;                 /* sequence number */
    tcp_seq th_ack;                 /* acknowledgement number */
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u_int   th_x2:4,                /* (unused) */
            th_off:4;               /* data offset */
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
    u_int   th_off:4,               /* data offset */
            th_x2:4;                /* (unused) */
#endif
    u_char  th_flags;
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG)

    u_short th_win;                 /* window */
    u_short th_sum;                 /* checksum */
    u_short th_urp;                 /* urgent pointer */
};

// threads
struct timespec {
        long tv_sec;
        long tv_nsec;
};

#ifdef __cplusplus
}
#endif

#endif LIBCOMPAT_H
