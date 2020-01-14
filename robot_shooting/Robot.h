#ifndef Robot_h
#define Robot_h
#pragma once

#include "globals.h"
#include "Arena.h"

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Robot declaration.

class Robot {
public:
    // Constructor
    Robot(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool takeDamageAndLive();
    
    // Add function to change damaged statas.
    //void takeDamage();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    // TODO: You'll probably find that a robot object needs an additional
    // data member to support your implementation of the behavior affected
    // by being hit and taking damage.
    bool damaged;   // Keeps track if robot has been hit before
};

#endif /* Robot_h */
