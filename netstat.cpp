#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <dirent.h>
int main()
{
	struct in_addr ip_addr;
	ip_addr.s_addr = 0x0100007F;
	uint32_t port = 0x18EB;
	printf("IP Address = %s %u\n", inet_ntoa(ip_addr), port);

	DIR *dirp = opendir("/proc/net");
	if (dirp){
		printf("Entry\n");
		struct dirent *direntp;
		while( (direntp = readdir(dirp)) != NULL ){
			printf("%s\n", direntp->d_name);
		}
		closedir(dirp);
	}
	exit(0);
}
