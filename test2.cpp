#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

#define MAX_LINE 1024
struct Address{
#define local 0
#define remote 1
    char IP[16];
    uint32_t port;
};
int main(){
	//struct sockaddr_in sa;
	//char str[MAX_LINE];
	//printf("%s", inet_ntop(AF_INET, &(sa.sin_addr), str, MAX_LINE));
	//
	string tmp = "BACD0120000000000000000052965732:0CEA";	
	int pos=0;
	string IP[4];
	Address address;
	cout << tmp << endl;
	for (int i=0 ;i<4; ++i, pos+=8){
	        IP[i] = tmp.substr(pos, 8);
		cout << IP[i] << " ";
	}
	cout << endl;
	string port = tmp.substr(pos+1, 4);
	cout << port << endl;
	
	struct in6_addr ip_addr;
	for (int i=0;i<4;++i){
	        ip_addr.__in6_u.__u6_addr32[i] = (uint32_t) strtoul(IP[i].c_str(), nullptr, 16);
	}
	address.port = (uint32_t) strtoul(port.c_str(), nullptr, 16);
	printf("%u %u\n", address.port, (uint32_t) strtoul(port.c_str(), nullptr, 16));
	inet_ntop(AF_INET6, &ip_addr.__in6_u, address.IP, 16);
	printf("IP:%s port:%u\n", address.IP, address.port);
}
