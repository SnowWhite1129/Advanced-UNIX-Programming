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
#include <sstream>
#include <iostream>

#define MAX_LINE 1024
using namespace std;
struct Address{
#define local 0
#define remote 1
    char IP[16];
    uint32_t port;
};
struct Connection{
    string protocol;
    Address address[2];
    int pid;
    unsigned int inode;
    char program[MAX_LINE];
    void Print();
    void Read(string line);
};
struct Process{
    int pid;
    char program[MAX_LINE];
    vector <unsigned int > inode;
    void ReadProgram(string filename);
    void Readinode();
};

vector <Connection> connections;
vector <Process> processes;

void Connection::Print() {
    printf("%-6s %-8s:%-4u %-8s:%-4u %d/%s\n", protocol.c_str(), address[0].IP, address[0].port, address[1].IP, address[1].port, pid, program);
}
void Connection::Read(string line) {
    istringstream iss(line);
    string tmp;
    iss >> tmp;
    for (int i = 0; i < 12; ++i) {
        iss >> tmp;
        if (i == 0 || i == 1) {
            string IP = tmp.substr(0, 8);
            string port = tmp.substr(9, 13);
            struct in_addr ip_addr;
            ip_addr.s_addr = (uint32_t) strtoul(IP.c_str(), nullptr, 16);
            strcpy(address[i].IP, inet_ntoa(ip_addr));
            address[i].port = (uint32_t) strtoul(port.c_str(), nullptr, 16);
            printf("IP Address = %s %u\n", address[0].IP, address[0].port);
        }
        if (i == 11){
            inode = stoi(tmp);
        }
    }
}
void ReadConnetcion(string filename) {
    FILE *input;
    filename = "/proc/net/" + filename;
    input = fopen(filename.c_str(), "r");

    if (!input){
        printf("Error\n");
        exit(1);
    }
    char line[MAX_LINE];
    fgets(line, MAX_LINE, input);

    while (!feof(input)){
        fgets(line, MAX_LINE, input);

        Connection connection;
        connection.Read(line);
        connections.push_back(connection);
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
void Display(){
    printf("List of TCP connections:\n");
    printf("%s %-20s %-20s %s", "Proto", "Local Address", "Foreign Address", "PID/Program name and arguments\n");
    for (int i = 0; i < connections.size(); ++i) {
        connections.at(i).Print();
    }
}


int main()
{
	DIR *dirp = opendir("/proc");
	if (dirp){
	    Connection connection;
	    ReadConnetcion("tcp");

	    exit(0);
	    Display();

		struct dirent *direntp;
		while( (direntp = readdir(dirp)) != NULL ){
		    char name[MAX_LINE];
		    strcpy(name, direntp->d_name);
		    if (isdigit(name[0])){
		        printf("%s\n", direntp->d_name);

                string dir = "/proc/";
                dir += name;
                dir += "/";

		        Process process;
		        process.ReadProgram(dir);

		        string fdname = dir + "fd/";
		    }
		}
		closedir(dirp);
	}

}
