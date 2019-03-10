#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

int main(int argc, char* argv[]){
	std::string ppid,aux,pgid;
	int quantMax = atoi(argv[1]);
		while(true){
		std::string process = exec("ps -e -o ppid,pgid| sort |uniq -c");
		std::istringstream pass(process);
		while(pass >> aux){
			pass >> ppid;
			pass >> pgid;
			int pqnt = atoi(aux.c_str());
			if(pqnt > quantMax){
				std::cout << "Matando " + ppid + " Fork Bomb em potêncial..." << std::endl;
				aux = "pkill -9 -g " + pgid;
				system(aux.c_str());
				std::cout << "Obrigado por usar Baidu..." << std::endl;
			}
		}
	}
	// int ppid;
	/*
	while(ppid != 1){ 
		ppid = getppid();
		std::cout << ppid << std::endl;
	}*/

	//while(std::cin >> system("pstree /proc/"))
	// std::string line;
	// std::istringstream ina(exec("ps ax | perl -nle 'print $1 if /^ *([0-9]+)/'"));

	// while ( std::getline(ina, line)){
	// 	std::cout << line << std::endl;
	// }

	//std::cout << 

return 0;
}