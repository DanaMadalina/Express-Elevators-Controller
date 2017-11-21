#include "Controler.h"
#include "cstdlib"


CControler::CControler(int lev, int elevat):
    levels(lev),
    elevators(elevat)
{
    ElevatorList = new CElevator* [elevators];
    for(int i = 0; i < elevators; i++)
    {
        ElevatorList[i] = new CElevator(levels);
    }
}

CControler::~CControler()
{
    for(int i = 0; i < elevators; i++)
    {
        delete ElevatorList[i];
    }
    delete ElevatorList;
}

int CControler::setCommand(int start, int destination)
{
    int assignedElevator = elevators + 1;
    int minDifference = levels;
    bool directionUp = (destination > start);
    for(int i = 0; i < elevators; i++)
    {
        if(ElevatorList[i]->isStopped() ||
           ((ElevatorList[i]->isDirectionUp() == directionUp) &&
            ((directionUp == true && start > ElevatorList[i]->getCurrentLevel()) ||
             (directionUp == false && start < ElevatorList[i]->getCurrentLevel()))))
        {
            if(abs(start - ElevatorList[i]->getCurrentLevel()) < minDifference)
            {
                minDifference = abs(start - ElevatorList[i]->getCurrentLevel());
                assignedElevator = i;
            }
        }
    }
    if(assignedElevator < elevators)
    {
        ElevatorList[assignedElevator]->setCommand(start, destination);
    }
    return assignedElevator + 1;
}

void CControler::display()
{
    for(int i = 0; i < elevators; i++)
    {
        cout<<"L"<<i<<":";
        ElevatorList[i]->display();
    }
}

void CControler::passUnit()
{
    for(int i = 0; i < elevators; i++)
    {
        ElevatorList[i]->passUnit();
    }
}

bool CControler::isExecutionFinished()
{
    bool retVal = true;
    for(int i = 0; i < elevators; i++)
    {
        if(ElevatorList[i]->isStopped()== false)
        {
            retVal = false;
            break;
        }
    }

    return retVal;
}

