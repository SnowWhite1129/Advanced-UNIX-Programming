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
#include <regex>

#define MAX_LINE 1024
using namespace std;
struct Address{
#define local 0
#define remote 1
    char IP[16];
    uint32_t port;
    string Message();
};
struct Connection{
    string protocol;
    Address address[2];
    int pid;
    unsigned int inode;
    char program[MAX_LINE];
    void Print();
    void Read(string line);
    string Message();
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
string Address::Message() {
    string m = IP;
    m += ":";
    if (port != 0){
        m += to_string(port);
    } else {
        m += "*";
    }
    return m;
}
string Connection::Message() {
    string m = protocol;
    m += ' ';
    m += address[local].Message();
    m += ' ';
    m += address[remote].Message();
    m += ' ';
    m += to_string(pid);
    m += ' ';
    m += program;
    return m;
}
void Connection::Print() {
    printf("%-5s %-23s %-23s %d/%s\n", protocol.c_str(), address[local].Message().c_str(), address[remote].Message().c_str(), pid, program);
}
void Connection::Read(string line) {
    istringstream iss(line);
    string tmp;
    iss >> tmp;
    for (int i = 0; i < 9; ++i) {
        if (iss >> tmp){
            if (i == 0 || i == 1) {
                if (protocol.find('6')==string::npos){
                    string IP = tmp.substr(0, 8);
                    string port = tmp.substr(9, 13);

                    struct in_addr ip_addr;
                    ip_addr.s_addr = (uint32_t) strtoul(IP.c_str(), nullptr, 16);
                    strcpy(address[i].IP, inet_ntoa(ip_addr));
                    address[i].port = (uint32_t) strtoul(port.c_str(), nullptr, 16);
                } else {
                    int pos=0;
                    string IP[4];
                        for (int j=0 ;j<4; ++j, pos+=8){
                        IP[j] = tmp.substr(pos, 8);
                    }
                    string port = tmp.substr(pos+1);

                    struct in6_addr ip_addr;
                    for (int j=0;j<4;++j){
                        ip_addr.__in6_u.__u6_addr32[j] = (uint32_t) strtoul(IP[j].c_str(), nullptr, 16);
                    }
                    inet_ntop(AF_INET6, &ip_addr.__in6_u, address[i].IP, 16);
                    address[i].port = (uint32_t) strtoul(port.c_str(), nullptr, 16);
		        }
            }
            if (i == 8){
                inode = stoi(tmp);
            }
        }
    }
//    printf("IP Address = %s %u Inode: %u\n", address[0].IP, address[0].port, inode);
}
void ReadConnection(string protocol) {
    FILE *input;
    string filename = "/proc/net/" + protocol;
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
	    connection.protocol = protocol;
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
    bool split = false;
    for(int i=0; i<MAX_LINE;++i){
        if(!split && program[i]=='\0'){
            program[i] = ' ';
            split = true;
        } else if (program[i] != '\0'){
            split = false;
        }
    }
//    printf("program: %s\n", program);

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
                string dir = filename;
                dir += name;

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
		connections.at(i).pid = 0;
		strcpy(connections.at(i).program, "permission denied");
		for(int j=0; j<processes.size();++j){
			for(int k=0;k<processes.at(j).inode.size();++k){
				if(connections.at(i).inode == processes.at(j).inode.at(k)){
					connections.at(i).pid = processes.at(j).pid;
					strcpy(connections.at(i).program, processes.at(j).program);
					break;
				} 
			}
		}
	}
}
void Display(string filter){
    int pos=0;
    if (connections.at(0).protocol.find("tcp")!=string::npos){
        printf("List of TCP connections:\n");
        printf("%s %-23s %-23s %s", "Proto", "Local Address", "Foreign Address", "PID/Program name and arguments\n");
	
        if (!filter.empty()){
            regex cmd_regex(filter);
            smatch sm;
            for (; pos < connections.size(); ++pos) {
                if (regex_search(connections.at(pos).Message(), sm, cmd_regex)){
                    connections.at(pos).Print();
                }
            }
        }
        else{
            for (; pos < connections.size(); ++pos) {
                connections.at(pos).Print();
            }
        }
    }
    if (pos != connections.size()){
        printf("List of UDP connections:\n");
        printf("%s %-23s %-23s %s", "Proto", "Local Address", "Foreign Address", "PID/Program name and arguments\n");
        for (; pos < connections.size(); ++pos) {
            connections.at(pos).Print();
        }
    }
}


int main(int argc, char **argv)
{
	bool TCP = false, UDP = false;
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
            ReadConnection("tcp");
            ReadConnection("tcp6");
		    TCP = true;
            break;
        case 'u':
            ReadConnection("udp");
            ReadConnection("udp6");
		    UDP = true;
            break;
        }
    }
	if (!TCP && !UDP){
		ReadConnection("tcp");
		ReadConnection("tcp6");
		ReadConnection("udp");
		ReadConnection("udp6");
	}
	string filter;
	for (int i=0; i<argc;++i){
		if(argv[i][0] != '-'){
			filter = argv[i];
		}
	}

	DIR *dirp = opendir("/proc");
	if (dirp){
	    Connection connection;

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
			    process.pid = atoi(name);

		        string fdname = dir + "fd/";
		        process.Readinode(fdname);
		        processes.push_back(process);
		    }
		}
		closedir(dirp);
	}
	Compare();
	Display(filter);
}
