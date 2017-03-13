#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "graph.h"
#include <queue>

using namespace std;

const int ROWS = 3;
const int COLS = 3;
const int goalState[ROWS][COLS] = { { 1, 2, 3 }, { 8, 0, 4 }, { 7, 6, 5 } };

struct myComparator {
    bool operator()(const vertex& v1, const vertex& v2)
    {
        return v1.heuristic > v2.heuristic;
    }
};


void printState(int state[3][3])
{
    cout << "_______" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "|";
        for (int j = 0; j < COLS; j++) {
            cout << state[i][j] << "|";
        }
        cout << endl
             << "-------" << endl;
    }
}

bool isGoalState(vertex stateToCheck)
{
    //cout << "State is " << stateToCheck.index << endl;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (goalState[i][j] != stateToCheck.tileState[i][j])
                return false;
        }
    }
    return true;
}

void printPath(vertex foundState, vector<vertex> fullList)
{

    if (foundState.index == 0) {
        cout << "Child#:" << foundState.index << " at level:" << foundState.depth << endl;
        printState(foundState.tileState);
        return;
    }

    cout << "Child#:" << foundState.index << " at level:" << foundState.depth << endl;
    printState(foundState.tileState);
    cout << "^" << endl;
    cout << "|" << endl;
    cout << "|" << endl;


    int i=0; 

    while (fullList[i].index != foundState.parentIndex)
    {
        i++; 
    }


    printPath(fullList[i], fullList);
    return;
}

void initializeChild(vertex parent, vertex& child, int a, int b)
{
    for (int i = 0; i < ROWS; i++) //straight up copying parent state to child
        for (int j = 0; j < COLS; j++) {
            child.tileState[i][j] = parent.tileState[i][j];
        }
    //updating child's empty tile place using calculations that can be made from parent's empty space
    //added all the variables to make it easier to read and understand what I'm doing
    int parentI = parent.posOfEmptyTile[0];
    int parentJ = parent.posOfEmptyTile[1];

    child.posOfEmptyTile[0] = parentI + a; //old empty tile pos + row value
    child.posOfEmptyTile[1] = parentJ + b; //old empty tile pos + col value

    int childI = child.posOfEmptyTile[0];
    int childJ = child.posOfEmptyTile[1];

    //this is the number that will move in the direction that it was intended to
    //In the parent, it's where the child's empty tile is going to be
    int temp = parent.tileState[childI][childJ];

    //It will go where the parent's empty space would've been
    child.tileState[parentI][parentJ] = temp;

    //Update empty tile of child
    child.tileState[childI][childJ] = 0;

    //  printState(child->tileState); //If you want to see each child
}

void generateMoves(vertex& parentState)
{
    if (parentState.posOfEmptyTile[0] == 0 && parentState.posOfEmptyTile[1] == 0) {
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
    }
    else if (parentState.posOfEmptyTile[0] == 0 && parentState.posOfEmptyTile[1] == 1) {
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
    }
    else if (parentState.posOfEmptyTile[0] == 0 && parentState.posOfEmptyTile[1] == 2) {
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
    }
    else if (parentState.posOfEmptyTile[0] == 1 && parentState.posOfEmptyTile[1] == 0) {
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
    }
    else if (parentState.posOfEmptyTile[0] == 1 && parentState.posOfEmptyTile[1] == 1) {
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
    }
    else if (parentState.posOfEmptyTile[0] == 1 && parentState.posOfEmptyTile[1] == 2) {
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
    }
    else if (parentState.posOfEmptyTile[0] == 2 && parentState.posOfEmptyTile[1] == 0) {
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
    }
    else if (parentState.posOfEmptyTile[0] == 2 && parentState.posOfEmptyTile[1] == 1) {
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
    }
    else if (parentState.posOfEmptyTile[0] == 2 && parentState.posOfEmptyTile[1] == 2) {
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
    }
}

vector<vertex> generateChildren(vertex& parentState)
{
    generateMoves(parentState);
    parentState.numOfChildren = parentState.movesToGenerateChildren.size();

    int count = 0;
    vector<vertex> children;

    while (count != parentState.numOfChildren) {

        vertex tempChild; //create temp child

        if (parentState.movesToGenerateChildren[count] == 'l') //left
        {  
            tempChild.moveToMakeMe = 'l';
            initializeChild(parentState, tempChild, 0, 1);
        }
        else if (parentState.movesToGenerateChildren[count] == 'r') //right
        {   
            tempChild.moveToMakeMe = 'r';
            initializeChild(parentState, tempChild, -0, -1);
        }
        else if (parentState.movesToGenerateChildren[count] == 'u') //up
        {
            tempChild.moveToMakeMe = 'u';
            initializeChild(parentState, tempChild, 1, 0);
        }
        else if (parentState.movesToGenerateChildren[count] == 'd') //down
        {  
            tempChild.moveToMakeMe = 'd';
            initializeChild(parentState, tempChild, -1, -0);
        }

        tempChild.depth = parentState.depth + 1;
        tempChild.numOfChildren = 0;

        count++;

        children.push_back(tempChild);
    }

    return children;
}

bool isSameNode(vertex node1, vertex node2)
{
    //first, checking if the space is in the same position else no need to compare each tile
    if (node1.posOfEmptyTile[0] == node2.posOfEmptyTile[0] && node1.posOfEmptyTile[1] == node2.posOfEmptyTile[1])
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++) 
            {
                if (node1.tileState[i][j] != node2.tileState[i][j])
                    return false;
            }
    else
        return false;

    return true;
}

int inOpenList(vertex& checkState, vector<vertex> nodeList)
{
    for (int i = 0; i < nodeList.size(); i++)
        if (nodeList[i].discovered == true)
            if (isSameNode(nodeList[i], checkState))
             {
                return nodeList[i].index;
            }
    return -1;
}

int inClosedList(vertex& checkState, vector<vertex> closedList)
{
    for (int i = 0; i < closedList.size(); i++)
        if (isSameNode(closedList[i], checkState)) 
        {
            return closedList[i].index;
        }
    return -1;
}

int manhattanDistance(int compareState[3][3])
{
    int manhattanDist = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++) 
        {
            int tile = compareState[i][j];

            if (tile != goalState[i][j])
             {
                int row = 0;
                int col = 0;
                do 
                {
                    do 
                    {
                        col++;
                    } while (tile == goalState[row][col] || col > 3);
                   
                    row++;
                
                } while (tile == goalState[row][col] || row > 3);
                manhattanDist = manhattanDist + abs(row - i) + abs(col - j);
            }
        }
    return manhattanDist;
}

int heuristicH(int compareState[3][3])
{
    int H = manhattanDistance(compareState);

    return H;
}

int tilesOutOfPlace(int compareState[3][3])
{
    int outOfPlaceCount = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (goalState[i][j] != compareState[i][j])
                outOfPlaceCount++;
    return outOfPlaceCount - 1; //to account for the middle tile
}

void bestFirstSearch(char heurChoice, vertex& initialVertex)
{
    cout << "This is will bestFirstSearch" << endl;

    priority_queue<vertex, vector<vertex>, myComparator> openBestFSList;

    vector<vertex> nodeList; //holds all nodes- needed for depth

    vector<vertex> closedList; //closed:= []
    vector<vertex> childList; //holds children once generated

    int heurValue = 0;
    if (heurChoice == 't')
        heurValue = initialVertex.depth + tilesOutOfPlace(initialVertex.tileState);
    else if (heurChoice == 'm')
        heurValue = initialVertex.depth + manhattanDistance(initialVertex.tileState);
    else
        heurValue = initialVertex.depth + heuristicH(initialVertex.tileState);

    initialVertex.heuristic = heurValue;

    initialVertex.discovered = true;

    openBestFSList.push(initialVertex); //open:= [Start]
    nodeList.push_back(initialVertex);

    while (!openBestFSList.empty()) //while open != [] do
    { //begin
        //remove the leftmost state from open, call it X

        vertex topVertex = openBestFSList.top();
        openBestFSList.pop();

        // if X = goal, then return the path from Start to X
        //else begin

        if (isGoalState(topVertex)) 
        {
            printPath(topVertex, nodeList);
            return;
        }
        else 
        {
            int parentIndex = topVertex.index;

            // generate children of X;
            childList = generateChildren(topVertex);

            int numberOfChildren = topVertex.numOfChildren;

            vertex currentChild;

            int duplicateOpenIndex = -1; //saves the return value from open list duplicate checks
            int duplicateClosedIndex = -1;

            while (numberOfChildren > 0) 
            {

                currentChild = childList[numberOfChildren - 1];
                currentChild.index = nodeList.size() + 1;

                currentChild.parentIndex = parentIndex;

                duplicateOpenIndex = inOpenList(currentChild, nodeList);
                duplicateClosedIndex = inClosedList(currentChild, closedList);

                if (duplicateOpenIndex == -1 && duplicateClosedIndex == -1) 
                {

                    if (heurChoice == 't')
                        heurValue = currentChild.depth + tilesOutOfPlace(currentChild.tileState);
                    else if (heurChoice == 'm')
                        heurValue = currentChild.depth + manhattanDistance(currentChild.tileState);
                    else
                        heurValue = currentChild.depth + heuristicH(currentChild.tileState);

                    currentChild.heuristic = heurValue;

                    currentChild.discovered = true;

                   
                    openBestFSList.push(currentChild); //child added to right end of open queue
                    nodeList.push_back(currentChild);
                }

                if (duplicateOpenIndex > -1) 
                { //if new child was reached by a shorter path
                    if (currentChild.heuristic < nodeList[duplicateOpenIndex].heuristic)
                     { //          openBestFSList.push(nodeList[indexHolder]);

                        openBestFSList.push(currentChild);
                        nodeList[duplicateOpenIndex].heuristic = currentChild.heuristic;
                    }
                }

                if (duplicateClosedIndex > -1) 
                {
                    //if new child was reached by a shorter path
                    if (currentChild.heuristic < closedList[duplicateClosedIndex].heuristic)
                     {
                        //DEV - REMOVE STATE FROM CLOSED LIST - NOT SURE HOW TO DO THIS YET.....
                        openBestFSList.push(currentChild);
                    }
                }

                numberOfChildren--;
            }

            closedList.push_back(topVertex);
        }
    }
}

void depthFirstSearch(vertex& initialVertex)
{
    cout << "This is will depthFirstSearch" << endl;
}

void breadthFirstSearch(vertex& initialVertex)
{
    cout << "This is will breadthFirstSearch" << endl;
}

#endif