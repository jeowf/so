#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(){
	int ppid;
	/*
	while(ppid != 1){ 
		ppid = getppid();
		std::cout << ppid << std::endl;
	}*/

	//while(std::cin >> system("pstree /proc/"))
	std::string line;
	std::istringstream ina(exec("ps ax | perl -nle 'print $1 if /^ *([0-9]+)/'"));

	while ( std::getline(ina, line)){
		std::cout << line << std::endl;
	}

	//std::cout << 


}