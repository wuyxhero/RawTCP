//
// Created by trojan52 on 25.02.19.
//

#ifndef RAWTCP_INCLUDES_H
#define RAWTCP_INCLUDES_H

#include <unistd.h>

#include <stdio.h>

#include <sys/socket.h>

#include <netinet/ip.h>

#include <netinet/tcp.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

enum tcp_flags {
    TCPFlag_FIN = 1,
    TCPFlag_SYN = 2,
    TCPFlag_RST = 4,
    TCPFlag_PSH = 8,
    TCPFlag_ACK = 16,
    TCPFlag_URG = 32,
    TCPFlag_ECE = 64,
    TCPFlag_CWR = 128
};

typedef enum tcp_flags TCP_Flags;

enum tcp_status {
    CLOSED,
    LISTEN,
    SYN_SENT,
    SYN_RECEIVED,
    ESTABLISHED,
    FIN_WAIT1,
    CLOSE_WAIT,
    FIN_WAIT2,
    LAST_ACK,
    TIME_WAIT,
    CLOSING
};

typedef enum tcp_status TCP_Status;

#define PCKT_LEN 8192


struct ipheader {
#if __BYTE_ORDER == BIG_ENDIAN

    u_int8_t           version:4;

    u_int8_t           IHL:4;

    u_int8_t           typeOfService;

    u_int16_t          totalLength;

    u_int16_t          identification;

    u_int16_t          fragmentOffset:13;

    u_int16_t          flags:3;

    u_int8_t           timeToLive;

    u_int8_t           protocol;

    u_int16_t          headerChecksum;

    u_int32_t          sourceIP;

    u_int32_t          destinationIP;
#elif __BYTE_ORDER == LITTLE_ENDIAN

    u_int8_t           IHL:4;

    u_int8_t           version:4;

    u_int8_t           typeOfService;

    u_int16_t          totalLength;

    u_int16_t          identification;

    u_int16_t          flags:3;

    u_int16_t          fragmentOffset:13;

    u_int8_t           timeToLive;

    u_int8_t           protocol;

    u_int16_t          headerChecksum;

    u_int32_t          sourceIP;

    u_int32_t          destinationIP;

#else
#error MIDDLE-ENDIAN SYSTEM PIZDEC
#endif

};

/* Structure of a Pseudo TCP header */
#pragma pack(push, 1)
struct pseudo_tcp {
    u_int32_t          sourceIP;
    u_int32_t          destIP;
    u_int8_t           res;
    u_int8_t           protocol;
    u_int16_t           tcpLength;
};
#pragma pack (pop)
/* Structure of a TCP header */

struct tcpheader {
    u_int16_t           sourcePort;
    u_int16_t           destinationPort;
    u_int32_t           sequenceNumber;
    u_int32_t           acknowledgeNumber;
#if __BYTE_ORDER == LITTLE_ENDIAN
    u_int16_t           ns:1;
    u_int16_t           reserved:3;
    u_int16_t           dataOffset:4;
#elif __BYTE_ORDER == BIG_ENDIAN
    u_int16_t           dataOffset:4;
    u_int16_t           reserved:3;
    u_int16_t           ns:1;
#else
#error MIDDLE-ENDIAN SYSTEM PIZDEC
#endif
    u_int16_t           controlBits:8;
    u_int16_t           window;
    u_int16_t           checkSum;
    u_int16_t           urgentPointer;
};

struct tcpheaderOptions
{

    u_int16_t
            tcph_mssOpt:8,
            tcph_mssLen:8;
    u_int16_t
            tcph_mss;
    u_int16_t
            tcph_sack:8,
            tcph_sackLen:8;
    u_int16_t
            tcph_winOpt:8,
            tcph_winLen:8;
    u_int32_t
            tcph_win:8,
            tcph_winNOP:8,
            tcph_timeOpt:8,
            tcph_timeLen:8;
    u_int32_t tcph_time;
    u_int32_t tcph_timeEcho;
};


#endif //RAWTCP_INCLUDES_H
