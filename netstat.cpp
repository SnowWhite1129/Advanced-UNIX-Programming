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
#include <vector>
#include <string>
#include <ctype.h>

#define MAX_LINE 1024
using namespace std;
struct Address{
    char IP[16];
    uint32_t port;
};
struct Connection{
    string protocol;
    Address local, remote;
    int pid;
    unsigned int inode;
    char program[MAX_LINE];
    void Print();
};
struct Process{
    int pid;
    char program[MAX_LINE];
    vector <unsigned int > inode;
    void ReadProgram(string filename);
    void Readinode
};
void Connection::Print() {
    printf("%-6s %-8s:%-4u %-8s:%-4u %d/%s\n", protocol.c_str(), local.IP, local.port, remote.IP, remote.port, pid, program);
}
void ReadAddress(const char filename[]){
    FILE *input;
    input = fopen(filename, "r");

    char line[MAX_LINE];

    while (!feof(input)){
        fgets(line, MAX_LINE, input);

    }

    fclose(input);
}
void Process::ReadProgram(string filename){
    filename += "cmd_line";

    FILE *input;
    input = fopen(filename.c_str(), "r");

    fgets(program, MAX_LINE, input);

    fclose(input);
}

vector <Connection> connections;
vector <Process> processes;

int main()
{
	struct in_addr ip_addr;
	ip_addr.s_addr = 0x0100007F;
	uint32_t port = 0x18EB;
	printf("IP Address = %s %u\n", inet_ntoa(ip_addr), port);

	DIR *dirp = opendir("/proc");
	if (dirp){
		struct dirent *direntp;
		while( (direntp = readdir(dirp)) != NULL ){
		    char name[MAX_LINE];
		    strcpy(name, direntp->d_name);
		    if (isdigit(name[0])){
		        printf("%s\n", direntp->d_name);

                string dir = "/proc/" + name + "/";
		        Process process;
		        process.ReadProgram(dir);

		        string fdname = dir + "fd/";
		    }
		}
		closedir(dirp);
	}

}
