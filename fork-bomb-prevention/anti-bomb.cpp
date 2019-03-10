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
	int max_amount = 60;

	if (argc == 2)
		max_amount = atoi(argv[1]);

	std::cout << "Baidu is running with process limit: " << max_amount << std::endl;

	while(1){
		std::string process = exec("ps -e -o ppid,pgid| sort |uniq -c");
		std::istringstream pass(process);
		while(pass >> aux){
			pass >> ppid;
			int cur_ppid = atoi(ppid.c_str());
			pass >> pgid;
			int cur_amount = atoi(aux.c_str());
			if(cur_ppid>1 && cur_amount > max_amount){
				std::cout << " > Killing fork bomb [" + ppid + "]" << std::endl;
				aux = "kill -15 -" + pgid;
				system(aux.c_str());
				//std::cout << "Obrigado por usar Baidu..." << std::endl;
			}
		}
	}

return 0;
}