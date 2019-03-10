#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
//#include <list>
#include <set>
#include <vector>

std::vector <std::set<int>> pids;

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

void create_tree(){

	pids.resize(4194304);

	std::string process = exec("ps -e -o ppid,pid");
	std::istringstream pass(process);

	std::string ppid, pid;

	pass >> ppid >> pid;
	//std::cout << ppid << " " << pid;
	while(pass >> ppid >> pid){
		int ppid_index = atoi(ppid.c_str());
		int pid_value = atoi(pid.c_str());

		pids[ppid_index].insert(pid_value);

	}

}

void print_node(int node, int p, bool comma){
	if (pids[node].empty()){
		std::cout << std::setfill('\t') << std::setw(p) 
	          << "\"" << node << "\" : { }";

	} else {
		std::cout << std::setfill('\t') << std::setw(p) 
	          	  << "\"" << node << "\" : {\n";

	    /*for (auto &i : pids[node]) {

	    	if (i == *pids[node].end()-1)
	    		print_node(i, p+1, false);
	    	else
	    		print_node(i, p+1, true);
	    }*/
	    for (auto it=pids[node].begin(); it != pids[node].end(); ++it){
	    	if (*it == *pids[node].rbegin())
	    		print_node(*it, p+1, false);
	    	else
	    		print_node(*it, p+1, true);
	    }

		std::cout << std::setfill('\t') << std::setw(p) 
	         	  << "}";
	}

	if (comma)
		std::cout << ",\n";
	else
		std::cout << "\n";
	
}

void print_tree(int pid){
	std::cout << "{\n";
	print_node(pid, 2, false);
	std::cout << "}\n";
}


int main(int argc, char* argv[]){
	std::string amount,user;

	if (argc == 1){

		while (1){
			std::string process = exec("ps -e -o user| sort |uniq -c");
			std::istringstream pass(process);

			int total = 0;

			std::cout << "Process:" << std::endl;
			while(pass >> amount >> user){
				total += atoi(amount.c_str());
				std::cout << " > " << user << ": " << amount << std::endl;
			}

			std::cout << " > TOTAL: " << total << std::endl;
			sleep(1);
			std::cout << std::endl;
		}

	} else if ( argc == 2) {

		int pid = atoi(argv[1]);
		create_tree();
		print_tree(pid);

	}

	return 0;
	
}