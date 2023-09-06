#include "process.hpp"

class OpenAddr {
    public:
    OpenAddr(int memSize, int pageSize){
        size = memSize/pageSize;
        _pageSize = pageSize;
        _memSize = memSize;
        table = new Process[size];
        currentSize = 0;
        availablePages = new int[size];
        int currentPage = 0;
        for (int i{0}; i < size; i++) {
            availablePages[i] = currentPage;
            currentPage += _pageSize;
        }
    }

    ~OpenAddr() {
        delete[] table;
        table = nullptr;
        delete[] availablePages;
        availablePages = nullptr;
    }

    std::string insert(unsigned int PID) {
        int checkIndex{0};
        if(currentSize > size-1) return "failure";
        else {
            for(int i{0}; i<size; i++) {
                if(((PID/size)%size)%2 == 0) {
                    checkIndex = (PID%size + i*(((PID/size)%size)+1))%size;
            }
            else {
                    checkIndex = (PID%size + i*((PID/size)%size))%size;
            }
                if(table[checkIndex].getHasBeenFilled() == 0) {
                    table[checkIndex].setPID(PID);
                    table[checkIndex].setHasBeenFilled(1);
                    int assignPage{0};
                    for(int i{0}; i<size; i++){
                        if(availablePages[i] != -1) {
                            assignPage = availablePages[i];
                            availablePages[i] = -1;
                            break;
                        }
                    }
                table[checkIndex].setPStart(assignPage);
                currentSize++;
                return "success";
                }
                if(table[checkIndex].getPID() == PID) return "failure";
            }
        }
        checkIndex = PID%size;
        int i{0};
        while((table[checkIndex].getPID() != 0) && (i<size)) {
            if(((PID/size)%size)%2 == 0) {
                    checkIndex = (PID%size + i*(((PID/size)%size)+1))%size;
            }
            else {
                    checkIndex = (PID%size + i*((PID/size)%size))%size;
            }
            i++;
        }
        table[checkIndex].setPID(PID);
        table[checkIndex].setHasBeenFilled(1);
        int assignPage{0};
        for(int i{0}; i<size; i++){
            if(availablePages[i] != -1) {
                assignPage = availablePages[i];
                availablePages[i] = -1;
                break;
            }
        }
        table[checkIndex].setPStart(assignPage);
        currentSize++;
        return "success";
    }   

    std::string search(unsigned int PID) {
        for(int i{0}; i<size; i++) {
            int checkIndex{0};
            if(((PID/size)%size)%2 == 0) {
                checkIndex = (PID%size + i*(((PID/size)%size)+1))%size;
            }
            else {
                checkIndex = (PID%size + i*((PID/size)%size))%size;
            }
            if(table[checkIndex].getHasBeenFilled() == 0) break;
            if(table[checkIndex].getPID() == PID) return "found " + std::to_string(PID) + " in " + std::to_string(checkIndex);
        }
        return "not found";
    }

    std::string deletePID(unsigned int PID) {
         for(int i{0}; i<size; i++) {
                int checkIndex{0};
                if(((PID/size)%size)%2 == 0) {
                    checkIndex = (PID%size + i*(((PID/size)%size)+1))%size;
                }
                else {
                    checkIndex = (PID%size + i*((PID/size)%size))%size;
                }
                if(table[checkIndex].getHasBeenFilled() == 0) break;
                if(table[checkIndex].getPID() == PID){
                    table[checkIndex].setPID(0);
                    int assignPage{table[checkIndex].getPStart()};
                    table[checkIndex].setPStart(0);
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
        for(int i{0}; i<size; i++) {
            int checkIndex{0};
            if(((PID/size)%size)%2 == 0) {
                checkIndex = (PID%size + i*(((PID/size)%size)+1))%size;
            }
            else {
                checkIndex = (PID%size + i*((PID/size)%size))%size;
            }
            if(table[checkIndex].getHasBeenFilled() == 0) break;
            if(table[checkIndex].getPID() == PID) {
                physicalAddr = table[checkIndex].getPStart() + virtAddr;
                if(physicalAddr >= (table[checkIndex].getPStart())+_pageSize) {
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
        for(int i{0}; i<size; i++) {
        int checkIndex{0};
            if(((PID/size)%size)%2 == 0) {
                checkIndex = (PID%size + i*(((PID/size)%size)+1))%size;
            }
            else {
                checkIndex = (PID%size + i*((PID/size)%size))%size;
            }
            if(table[checkIndex].getHasBeenFilled() == 0) break;
            if(table[checkIndex].getPID() == PID) {
                physicalAddr = table[checkIndex].getPStart() + virtAddr;
                if(physicalAddr >= (table[checkIndex].getPStart())+_pageSize) {
                    return "failure";
                }
                int x = memory[physicalAddr];
                return std::to_string(virtAddr) + " " + std::to_string(x);
            }
        }
        return "failure";
    }

    private:
    Process* table;
    int size;
    int currentSize;
    int* availablePages;
    int _pageSize;
    int _memSize;
};