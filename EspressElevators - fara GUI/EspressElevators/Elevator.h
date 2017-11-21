#ifndef ELEVATOR_H
#define ELEVATOR_H


class CElevator
{
    public:
        CElevator(int numberLevels);

        virtual ~CElevator();
        void setCommand(int start, int destination);
        void passUnit();
        void display();
        bool isStopped();
        bool isDirectionUp();
        int getCurrentLevel();


    protected:
    private:
        bool hasHigherLevel(int level);
        bool hasLowerLevel(int level);
        void executeCommand(int start, int destination);

        char *levels;
        bool stopped;
        bool directionUp;
        int currentLevel;
        int totalLevels;

        bool pendingCommand;
        int pendingStart;
        int pendingDestination;
};

#endif // ELEVATOR_H
