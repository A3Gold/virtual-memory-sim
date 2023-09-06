#include <iostream>
#include "openAddr.hpp"
#include "chaining.hpp"

int main();

int main(){
    std::string initialCommand = " ";
    std::string command = " ";
    std::cin>>initialCommand;
        std::cin>>command;
        if(command == "M") {
            int N{0};
            int P{0};
            std::cin>>N;
            std::cin>>P;
            int M=N/P;
            int *memory = new int[N]{0};
            if(initialCommand == "OPEN") {
                OpenAddr myHash =  OpenAddr(N, P);
                std::cout<<"success"<<std::endl;
                while(command != "END") {
                if(command == "INSERT") {
                    unsigned int PID{0};
                    std::cin>>PID;
                    std::cout<<myHash.insert(PID)<<std::endl;
                }
                if(command == "SEARCH") {
                    unsigned int PID{0};
                    std::cin>>PID;
                    std::cout<<myHash.search(PID)<<std::endl;
                }
                if(command == "WRITE") {
                unsigned int PID{0};
                int virtAddr{0};
                int x{0};
                std::cin>>PID;
                std::cin>>virtAddr;
                std::cin>>x;
                std::cout<<myHash.write(PID, virtAddr, x, memory)<<std::endl;
                }
                if(command == "READ") {
                    unsigned int PID{0};
                    int virtAddr{0};
                    std::cin>>PID;
                    std::cin>>virtAddr;
                    std::cout<<myHash.read(PID, virtAddr, memory)<<std::endl;
                }
                if(command == "DELETE") {
                    unsigned int PID{0};
                    std::cin>>PID;
                    std::cout<<myHash.deletePID(PID)<<std::endl;
                }
                std::cin>>command;
            }
            delete[] memory;
            memory = nullptr;
            }
            if(initialCommand == "ORDERED") {
                Chaining myHash = Chaining(N, P);
                std::cout<<"success"<<std::endl;
            while(command != "END") {
                if(command == "INSERT") {
                    unsigned int PID{0};
                    std::cin>>PID;
                    std::cout<<myHash.insert(PID)<<std::endl;
                }
                if(command == "SEARCH") {
                    unsigned int PID{0};
                    std::cin>>PID;
                    std::cout<<myHash.search(PID)<<std::endl;
                }
                if(command == "WRITE") {
                unsigned int PID{0};
                int virtAddr{0};
                int x{0};
                std::cin>>PID;
                std::cin>>virtAddr;
                std::cin>>x;
                std::cout<<myHash.write(PID, virtAddr, x, memory)<<std::endl;
                }
                if(command == "READ") {
                    unsigned int PID{0};
                    int virtAddr{0};
                    std::cin>>PID;
                    std::cin>>virtAddr;
                    std::cout<<myHash.read(PID, virtAddr, memory)<<std::endl;
                }
                if(command == "DELETE") {
                    unsigned int PID{0};
                    std::cin>>PID;
                    std::cout<<myHash.deletePID(PID)<<std::endl;
                }
                if(command == "PRINT") {
                    unsigned int position{0};
                    std::cin>>position;
                    myHash.print(position);
                }
                std::cin>>command;
            }
            delete[] memory;
            memory = nullptr;
        }
    }
}