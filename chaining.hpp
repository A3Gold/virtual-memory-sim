#include <vector>
#include <iostream>


class Chaining {
    public:
    Chaining(int memSize, int pageSize){
        size = memSize/pageSize;
        _pageSize = pageSize;
        _memSize = memSize;
        table = new std::vector<Process>[size];
        currentSize = 0;
        for(int i{0}; i<size; i++) {
            table[i].push_back(Process(0, 0));
        }
        availablePages = new int[size];
        int currentPage = 0;
        for (int i{0}; i < size; i++) {
            availablePages[i] = currentPage;
            currentPage += _pageSize;
        }
    }

    ~Chaining() {
        delete[] table;
        table = nullptr;
        delete[] availablePages;
        availablePages = nullptr;
    }  

    std::string insert(unsigned int PID) {
        int index = PID%size;
        if(currentSize > size-1) return "failure";
        else {
            for(int j{0}; j < table[index].size(); j++) {
                if(table[index][j].getPID() == PID) return "failure";
            }
        }
        int assignPage{0};
        for(int i{0}; i<size; i++){
            if(availablePages[i] != -1) {
                assignPage = availablePages[i];
                availablePages[i] = -1;
                break;
            }
        }
        if(table[index][0].getPID()==0) {
            table[index][0].setPID(PID);
            table[index][0].setPStart(assignPage);
        }
        else{
            int chainIndex = table[index].size();
            for(int i{0}; i<table[index].size(); i++) {
              if(PID > table[index][i].getPID()) {
                chainIndex = i;
                break;
              }  
            }
            table[index].insert(table[index].begin() + chainIndex, Process(PID, assignPage));
        }
        currentSize++;
        return "success";
    }   

    std::string search(unsigned int PID) {
        int checkIndex = PID%size;
        for(int i{0}; i < table[checkIndex].size(); i++) {
            if(table[checkIndex][i].getPID() == PID) return "found " + std::to_string(PID) + " in " + std::to_string(checkIndex);
        }
        return "not found";
    }

    std::string deletePID(unsigned int PID) {
        int checkIndex = PID%size;
        int secondIndex{0};
        for(int i{0}; i < table[checkIndex].size(); i++) {
            if(table[checkIndex][i].getPID() == PID) { 
                secondIndex = i;
                int assignPage{table[checkIndex][secondIndex].getPStart()};
                if(table[checkIndex].size() > 1) {
                    table[checkIndex].erase(table[checkIndex].begin() + secondIndex);
                }
                else {
                    table[checkIndex][0].setPID(0);
                    table[checkIndex][0].setPStart(0);
                }                 
                for(int i{0}; i<size; i++) {
                    if(availablePages[i] == -1) {
                        availablePages[i] = assignPage;
                        currentSize--;
                        return "success";
                    }    
                }
            }
        }
        return "failure";
    }

    std::string write(unsigned int PID, int virtAddr, int x, int memory[]) {
        int physicalAddr{0};
        int checkIndex = PID%size;
        for(int i{0}; i < table[checkIndex].size(); i++) {
            if(table[checkIndex][i].getPID() == PID) {
                physicalAddr = table[checkIndex][i].getPStart() + virtAddr;
                if(physicalAddr >= (table[checkIndex][i].getPStart())+_pageSize) {
                    return "failure";
                }
                memory[physicalAddr] = x;
                return "success";
            }
        }
        return "failure";
    }

    std::string read(unsigned int PID, int virtAddr, int memory[]) {
        int physicalAddr{0};
        int checkIndex = PID%size;
        for(int i{0}; i < table[checkIndex].size(); i++) {
            if(table[checkIndex][i].getPID() == PID) {
                physicalAddr = table[checkIndex][i].getPStart() + virtAddr;
                if(physicalAddr >= (table[checkIndex][i].getPStart())+_pageSize) {
                    return "failure";
                }
                int x = memory[physicalAddr];
                return std::to_string(virtAddr) + " " + std::to_string(x);
            }
        }
        return "failure";
    }

    int print(unsigned int position) {
        if(position >= size || table[position][0].getPID() == 0){
        std::cout<<"chain is empty"<<std::endl;
        return 0;
        }
        else{
            for(int i{0}; i < table[position].size(); i++) {
                std::cout<<table[position][i].getPID();
                std::cout<<" ";
            }
            std::cout<<std::endl;
        }
        return 0;
    }

    private:
    std::vector<Process> *table;
    int size;
    int currentSize;
    int* availablePages;
    int _pageSize;
    int _memSize;
};