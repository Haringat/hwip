#ifndef HW_IP_H
#define HW_IP_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t version: 4;
    uint8_t ihl: 4;
    uint8_t tos: 6;
    uint8_t ECN: 2;
    uint16_t totalLength: 16;
    uint16_t identification: 16;
    uint8_t flags: 3;
    uint16_t fragmentOffset: 13;
    uint8_t ttl: 8;
    uint8_t protocol: 8;
    uint16_t checksum: 16;
    uint32_t source: 32;
    uint32_t destination: 32;
    uint32_t options[11];
} IPV4_HEADER;

typedef struct {
    IPV4_HEADER *header;
    char *payload;
} IPV4_PACKET;

char *hwipEncodeSchoolMode(IPV4_PACKET *);
IPV4_PACKET *hwipDecodeSchoolMode(const char *);
void hwipCalculateChecksum(IPV4_HEADER *);
void hwipCalculateHeaderLength(IPV4_HEADER *);
IPV4_PACKET *hwipDecapsulate(const char *);
char *hwipEncapsulate(IPV4_PACKET *, const char *);
IPV4_PACKET *hwipCreateSchoolModePacket(const char *);
void hwipCalculateIHL(IPV4_HEADER *);
bool hwipVerifyChecksum(IPV4_HEADER *);
void dumpIPv4Header(IPV4_HEADER *);
void dumpIPv4HeaderSchoolMode(IPV4_HEADER *);
void dumpIPv4HeaderSchoolModeBinary(IPV4_HEADER *header);
void printBits(const size_t, const void *);

static const char *hwipProtocols[143] = {
        "HOPOPT",
        "ICMP",
        "IGMP",
        "GGP",
        "IP",
        "STREAM",
        "TCP",
        "CBT",
        "EGP",
        "IGP",
        "BBN-RCC-MON",
        "NVP-II",
        "PUP",
        "ARGUS",
        "EMCON",
        "XNET",
        "CHAOS",
        "UDP",
        "MULTIPLEX",
        "DCN-MEAS",
        "HMP",
        "PRM",
        "XNS-IDP",
        "TRUNK-1",
        "TRUNK-2",
        "LEAF-1",
        "LEAF-2",
        "RDP",
        "IRTP",
        "ISO-TP4",
        "NETBLT",
        "MFE-NSP",
        "MERIT-INP",
        "DCCP",
        "3PC",
        "IDPR",
        "XTP",
        "DDP",
        "IDPR-CMTP",
        "TP++",
        "IL",
        "IPV6",
        "SDRP",
        "IPV6-ROUTE",
        "IPV6-FRAG",
        "IDRP",
        "RSVP",
        "GRE",
        "MHRP",
        "BNA",
        "ESP",
        "AH",
        "I-NLSP",
        "SWIPE",
        "NARP",
        "MOBILE",
        "TLSP",
        "SKIP",
        "IPV6-ICMP",
        "IPv6-NONXT",
        "IPv6-Opts",
        "INTERNAL",
        "CFTP",
        "LOCAL",
        "SAT-EXPAK",
        "KRYPTOLAN",
        "RVD",
        "IPPC",
        "DISTRIBUTED",
        "SAT-MON",
        "VISA",
        "IPCV",
        "CPNX",
        "CPHB",
        "WSN",
        "PVP",
        "BR-SAT-MON",
        "SUN-ND",
        "WB-MON",
        "WB-EXPAK",
        "ISO-IP",
        "VMTP",
        "SECURE-VMTP",
        "VINES",
        "TTP",
        "NSFNET-IGP",
        "DGP",
        "TCF",
        "EIGRP",
        "OSPF",
        "SPRITE-RPC",
        "LARP",
        "MTP",
        "AX.25",
        "IPIP",
        "MICP",
        "SCC-SP",
        "ETHERIP",
        "ENCAP",
        "PRIVATE-ENCRYPTION",
        "GMTP",
        "IFMP",
        "PNNI",
        "PIM",
        "ARIS",
        "SCPS",
        "QNX",
        "A/N",
        "IPCOMP",
        "SNP",
        "COMPAQ-PEER",
        "IPX-IN-IP",
        "VRRP",
        "PGM",
        "0-HOP",
        "L2TP",
        "DDX",
        "IATP",
        "STP",
        "SRP",
        "UTI",
        "SMP",
        "SM",
        "PTP",
        "ISIS",
        "FIRE",
        "CRTP",
        "CRUDP",
        "SSCOPMCE",
        "IPLT",
        "SPS",
        "PIPE",
        "SCTP",
        "FC",
        "RSVP-E2E-IGNORE",
        "MOBILITY HEADER",
        "UDPLITE",
        "MPLS-IN-IP",
        "MANET",
        "HIP",
        "SHIM6",
        "WESP",
        "ROHC"
};

#ifdef __cplusplus
};
#endif

#endif

