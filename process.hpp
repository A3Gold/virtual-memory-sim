class Process{
    public:
    Process(){
        _PID = 0;
        _pStart = 0;
        _hasBeenFilled = 0;
    }

    Process(unsigned int PID, int pStart){
        _PID = PID;
        _pStart = pStart;
        _hasBeenFilled = 0;
    }

    unsigned int getPID(){
        return this->_PID;
    }
    
    void setPID(unsigned int PID){
        this->_PID = PID;
    }

    int getPStart(){
        return this->_pStart;
    }
    
    void setPStart(int pStart){
        this->_pStart = pStart;
    }

    bool getHasBeenFilled(){
        return this->_hasBeenFilled;
    }
    
    void setHasBeenFilled(bool hasBeenFilled){
        this->_hasBeenFilled = hasBeenFilled;
    }

    private:
    unsigned int _PID;
    int _pStart;
    bool _hasBeenFilled;
};