#ifndef CONTROLER_H
#define CONTROLER_H
#include "Elevator.h"
#include "iostream"

using namespace std;

class CControler
{
    public:
        CControler(int lev, int elevat);
        virtual ~CControler();
        int setCommand(int start, int destination);
        void display();
        void passUnit();
        bool isExecutionFinished();
    protected:
    private:
        int levels;
        int elevators;
        CElevator **ElevatorList;
};

#endif // CONTROLER_H
