#include<stdio.h>
#include<getopt.h>
#include<stdlib.h>
int main(int argc, char **argv){
    const char optstring[] = "tu";
    struct option opts[] = {
            {"tcp", 0, nullptr, 't'},
            {"udp", 0, nullptr, 'u'},
            {0, 0, 0, 0}
    };
    int c;
    while((c = getopt_long(argc, argv, optstring, opts, nullptr)) != -1) {
        switch (c){
            case 't':
              	printf("-t --tcp\n");
                break;
            case 'u':
                printf("-u --udp\n");
                break;
            case '?':
                printf("?\n");
		break;
	    default:
		printf("skr\n");
                break;
        }
    }
    for(int i=0; i<argc; ++i){
	printf("[%d] %s\n",i, argv[i]);
    }
    return 0;
}
