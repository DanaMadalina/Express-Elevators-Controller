#include "Elevator.h"
#include "iostream"

using namespace std;

CElevator::CElevator(int numberLevels):
    stopped(true),
    directionUp(true),
    currentLevel(0),
    totalLevels(numberLevels),
    pendingCommand(false),
    pendingStart(0),
    pendingDestination(0)
{
    levels = new char[numberLevels];
    for(int i = 0; i < numberLevels; i++)
    {
        levels[i] = '-';
    }
    levels[currentLevel] = 'S';
}

CElevator::~CElevator()
{
    delete levels;
}

void CElevator::setCommand(int start, int destination)
{
    pendingCommand = true;
    pendingStart = start;
    pendingDestination = destination;
}

void CElevator::executeCommand(int start, int destination)
{
    pendingCommand = false;
    levels[destination] = 'l';
    if((levels[start]=='-') || (levels[start] == 'l'))
    {
        levels[start] = 'l';
        if(stopped)
        {
            if(currentLevel < start)
                levels[currentLevel] = '>';
            else
                levels[currentLevel] = '<';
        }
        else
            passUnit();
    }
    else
    {
        levels[currentLevel] = '*';
    }
    if(destination > start)
        directionUp = true;
    else
        directionUp = false;
    stopped = false;
}

void CElevator::passUnit()
{
    if(pendingCommand)
    {
        executeCommand(pendingStart, pendingDestination);
    }
    else if (stopped == false)
    {
        switch(levels[currentLevel])
        {
        case '>':
            {
                levels[currentLevel] = '-';
                currentLevel++;
                if (levels[currentLevel] != '-')
                {
                    if(directionUp || (hasHigherLevel(currentLevel) == false))
                        levels[currentLevel] = '*';
                    else
                        levels[currentLevel] = 'u';
                }
                else
                    levels[currentLevel] = '>';
                break;
            }
        case '<':
            {
                levels[currentLevel] = '-';
                currentLevel--;
                if (levels[currentLevel] != '-')
                {
                    if(directionUp && hasLowerLevel(currentLevel))
                        levels[currentLevel] = 'd';
                    else
                        levels[currentLevel] = '*';
                }
                else
                    levels[currentLevel] = '<';
                break;
            }
        case '*':
            {
                bool destAvailable = false;
                for(int i=0; i < totalLevels; i++)
                    if(levels[i] == 'l')
                    {
                        destAvailable = true;
                        break;
                    }

                if(destAvailable)
                {
                    if(directionUp)
                        levels[currentLevel] = '>';
                    else
                        levels[currentLevel] = '<';
                }
                else
                {
                    levels[currentLevel] = 'S';
                    stopped = true;
                }
                break;
            }
        case 'u':
            {
                levels[currentLevel] = 'l';
                currentLevel++;
                if(levels[currentLevel] == 'l')
                {
                    if(hasHigherLevel(currentLevel))
                        levels[currentLevel] = 'u';
                    else
                        levels[currentLevel] = '*';
                }
                else
                    levels[currentLevel] = '>';
                break;
            }
        case 'd':
            {
                levels[currentLevel] = 'l';
                currentLevel--;
                if(levels[currentLevel] == 'l')
                {
                    if(hasLowerLevel(currentLevel))
                        levels[currentLevel] = 'u';
                    else
                        levels[currentLevel] = '*';
                }
                else
                    levels[currentLevel] = '>';
                break;
            }

        default :
            break;
        }
    }
}

void CElevator::display()
{
    for(int i = 0; i < totalLevels; i++)
    {
        switch(levels[i])
        {
        case 'l':
            cout<<i<<" ";
            break;
        case 'u':
            cout<<'>'<<" ";
            break;
        case 'd':
            cout<<'<'<<" ";
            break;
        default:
            cout<<levels[i]<<" ";
            break;
        }
    }
    cout<<endl;
}

bool CElevator::isStopped()
{
    return stopped;
}

bool CElevator::isDirectionUp()
{
    return directionUp;
}

int CElevator::getCurrentLevel()
{
    return currentLevel;
}

bool CElevator::hasHigherLevel(int level)
{
    bool retVal = false;
    for (int i = level + 1; i < totalLevels; i++)
        if(levels[i] == 'l')
        {
            retVal = true;
            break;
        }
    return retVal;
}

bool CElevator::hasLowerLevel(int level)
{
    bool retVal = false;
    for (int i = level - 1; i > 0; i--)
        if(levels[i] == 'l')
        {
            retVal = true;
            break;
        }
    return retVal;
}
