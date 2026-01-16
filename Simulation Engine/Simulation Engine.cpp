// Simulation Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Cell.h"
#include "World.h"
#include <thread>
#include <chrono>
#include "Actor.h"

using namespace std;

int main()
{
    cout << "Hello World!\n";
    cout << "=== FIRE SIMULATION ENGINE ===." << endl;

    cout << "Please enter how the width you would like the world grind to be: ";

    string answer;
    int width;
    int height;

    cin >> answer;
    width = stoi(answer);

    cout << "Now please enter the height: ";

    cin >> answer;
    height = stoi(answer);
    
    World world(width, height);

    //Note to marker/tester: Fire's represent F on the grid, Trees T, water sources W and firefighters U
    
    cout << "How many forest cells would you like there to be here to be?: ";

    cin >> answer;
    world.addForest(stoi(answer));
 

    cout << "How many water pools would you like there to be here to be?: "; 
    cin >> answer;

    world.addWater(stoi(answer));
    world.printGrid();

    cout << "How many fires would you like there to be here to be?: ";
    cin >> answer;

    world.startRandomFires(stoi(answer));
    world.printGrid();


    cout << "How many firefighters would you like there to be?";
    cin >> answer;

    world.addFirefighters(stoi(answer));
    world.printGrid();


    int maxTurns = 50;

    for (int i = 0; i < maxTurns; i++) {
        // Update the world (process one turn)
        world.update();

        // Print grid every 3 turns or when something interesting happens
        world.printGrid();

        // Optional: Check for end condition
        bool firesExist = false;
        for (Actor* actor : world.liveActors) {
            if (dynamic_cast<Fire*>(actor) != nullptr && actor->IsActive()) {
                firesExist = true;
                break;
            }
        }

        if (!firesExist) {
            cout << "\n=== ALL FIRES EXTINGUISHED! ===" << endl;
            world.printGrid();
            break;
        }

        // Pause briefly (adjust timing as needed)
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    cout << "\n=== SIMULATION COMPLETE ===" << endl;
    cout << "Final turn: " << world.getCurrentTurn() << endl;

    return 0;
}
/*    while (true) {
        for (Actor* actor : world.liveActors) {  //Some testing to see if my fire algorithm works 
            actor->takeTurn(world); //Fire algo works but fails after 3 iterations which I found is due to liveActors having to resize which breaks iteration
            this_thread::sleep_for(chrono::seconds(1)); 
            cout << "\n";
            world.printGrid();
        }
    }*/


    /*
    while (true) {
        // SAFE: Capture size before loop
        size_t actorsToProcess = world.liveActors.size();

        for (size_t i = 0; i < actorsToProcess; i++) {
            if (i < world.liveActors.size()) {  // Safety check
                Actor* actor = world.liveActors[i];
                if (actor->IsActive()) {
                    actor->takeTurn(world);
                }
            }
        }

        world.cleanupDeadActors();
        this_thread::sleep_for(chrono::seconds(2));
        world.printGrid();
    }*/




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
