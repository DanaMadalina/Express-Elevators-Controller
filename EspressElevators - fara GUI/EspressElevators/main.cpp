#include <iostream>
#include "Controler.h"
#include "fstream"

using namespace std;

typedef struct Comm{
    int time;
    int start;
    int destination;
    Comm *next;
    }Command;

int main()
{
    int levels;
    int elevators;

    ifstream file("input.txt");

    file>>levels;
    file>>elevators;
    CControler PC(levels + 1,elevators);

    int T, S, D;
    Command *first = NULL;
    Command *last = NULL;

    while(file>>T && file>>S && file>>D)
    {
        Command *newNode = new Command();
        newNode->time = T;
        newNode->start = S;
        newNode->destination = D;
        newNode->next = NULL;

        if(first == NULL)
        {
            first = newNode;
            last = newNode;
        }
        else
        {
            last->next = newNode;
            last = newNode;
        }
    }

    int assignedElevator;
    int currentTime = 0;
    cout<<"t = "<<currentTime<<endl;
    PC.display();

    while(first != NULL || PC.isExecutionFinished()== false)
    {
        currentTime++;
        cout<<"t = "<<currentTime<<endl;

        while(first != NULL && first->time == currentTime)
        {
            assignedElevator = PC.setCommand(first->start, first->destination);
            cout<<"Lift cerut la etajul " <<first->start<<" pentru etajul "<<first->destination<<" gasit lift "<<assignedElevator<<"."<<endl;

            Command *aux;
            aux = first;
            first = first->next;
            delete aux;
        }
        PC.passUnit();
        PC.display();

    }

    return 0;
}
