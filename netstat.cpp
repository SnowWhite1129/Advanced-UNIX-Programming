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
#include <sys/stat.h>
#include <getopt.h>

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
    void Readinode(string filename);
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
    for (int i = 0; i < 9; ++i) {
        if (iss >> tmp){
            if (i == 0 || i == 1) {
                string IP = tmp.substr(0, 8);
                string port = tmp.substr(9, 13);
                struct in_addr ip_addr;
                ip_addr.s_addr = (uint32_t) strtoul(IP.c_str(), nullptr, 16);
                strcpy(address[i].IP, inet_ntoa(ip_addr));
                address[i].port = (uint32_t) strtoul(port.c_str(), nullptr, 16);
            }
            if (i == 8){
                inode = stoi(tmp);
            }
        }
    }
    // printf("IP Address = %s %u Inode: %u\n", address[0].IP, address[0].port, inode);
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
        if (fgets(line, MAX_LINE, input) != nullptr){
            Connection connection;
            connection.Read(line);
            connections.push_back(connection);
        }
    }

    fclose(input);
}
void Process::ReadProgram(string filename){
    filename += "cmdline";

    FILE *input;
    input = fopen(filename.c_str(), "r");

    fgets(program, MAX_LINE, input);
    // printf("program: %s\n", program);

    fclose(input);
}
void Process::Readinode(string filename) {
    DIR *dirp = opendir(filename.c_str());
    if (dirp){
        struct dirent *direntp;
        while( (direntp = readdir(dirp)) != NULL ){
            char name[MAX_LINE];
            strcpy(name, direntp->d_name);
            if (isdigit(name[0])) {

                //printf("%s\n", direntp->d_name);

                string dir = filename;
                dir += name;

                //cout << dir << endl;

                pid = stoi(name);

                struct stat status;
                if (stat(dir.c_str(), &status) == 0){
                    if ((status.st_mode & S_IFMT) == S_IFSOCK){
                        char line[MAX_LINE];
                        readlink(dir.c_str(), line, MAX_LINE);
                        string number = line;
                        int start = number.find('['),
                            end = number.find(']');
                        number = number.substr(start+1, end-start-1);
                        inode.push_back(stoi(number));
                        //cout << number << endl;
                        //printf("%s\n", line);
                    }
                } else{
                    printf("ERROR\n");
                }
            }
        }
        closedir(dirp);
    }
}
void Compare(){
	for(int i=0; i<connections.size();++i){
		for(int j=0; j<processes.size();++j){
			for(int k=0;k<processes.at(j).inode.size();++k){
				if(connections.at(i).inode == processes.at(j).inode.at(k)){
					connections.at(i).pid - processes.at(j).pid;
					break;
				}
			}
		}
	}
}
void Display(){
    int pos=0;
    if (connections.at(0).protocol.find("tcp")!=string::npos){
        printf("List of TCP connections:\n");
        printf("%s %-20s %-20s %s", "Proto", "Local Address", "Foreign Address", "PID/Program name and arguments\n");
        for (; pos < connections.size(); ++pos) {
            connections.at(pos).Print();
        }
    }
    if (pos != connections.size()){
        printf("List of UDP connections:\n");
        printf("%s %-20s %-20s %s", "Proto", "Local Address", "Foreign Address", "PID/Program name and arguments\n");
        for (; pos < connections.size(); ++pos) {
            connections.at(pos).Print();
        }
    }
}


int main(int argc, char **argv)
{
    /*
    bool TCP=false, UDP=false;
    string filter;
    const char optstring[] = "tu";
    struct option opts[] = {
            {"tcp", 0, nullptr, 't'},
            {"udp", 0, nullptr, 'u'},
            {0, 0, 0, 0}
    };
    int c;
    while((c = getopt_long(argc, argv, optstring, opts, nullptr)) != -1) {
        Connection connection;
        switch (c){
            case 't':
                ReadConnetcion("/proc/net/tcp");
                ReadConnetcion("/proc/net/tcp6");
		TCP = true;
                break;
            case 'u':
                ReadConnetcion("/proc/net/udp");
                ReadConnetcion("/proc/net/udp6");
		UDP = true;
                break;
        }
    }
	if (!TCP && !UDP){
		ReadConnection("/proc/net/tcp");
		ReadConnection("/proc/net/tcp6");
		ReadConnection("/proc/net/udp");
		ReadConnection("/proc/net/udp6");
		TCP = true;
		UDP = true;
	}
    */

	DIR *dirp = opendir("/proc");
	if (dirp){
	    Connection connection;
	    ReadConnetcion("tcp");

		struct dirent *direntp;
		while( (direntp = readdir(dirp)) != nullptr ){
		    char name[MAX_LINE];
		    strcpy(name, direntp->d_name);
		    if (isdigit(name[0])){
		        // printf("%s\n", direntp->d_name);

                string dir = "/proc/";
                dir += name;
                dir += "/";

		        Process process;
		        process.ReadProgram(dir);

		        string fdname = dir + "fd/";
		        process.Readinode(fdname);
		        processes.push_back(process);
		    }
		}
		closedir(dirp);
	}
	Compare();
	Display();
}
