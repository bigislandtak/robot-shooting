#include "Robot.h"

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

Robot::Robot(Arena* ap, int r, int c) {
    if (ap == nullptr) {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols()) {
        cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    damaged = false;    // Robot is healthy.
}

int Robot::row() const {
    return m_row;
}

int Robot::col() const {
    return m_col;
}

void Robot::move() {
    // Attempt to move in a random direction; if we can't move, don't move
    switch (TESTrand() % 4) {
        case UP:
            // Move the robot up one row if possible.
            if (m_row > 1)
                m_row--;
            break;
        case DOWN:
            if (m_row < m_arena->rows())
                m_row++;
            break;
        case LEFT:
            if (m_col > 1)
                m_col--;
            break;
        case RIGHT:
            if (m_col < m_arena->cols())
                m_col++;
            break;
        default:
            break;
    }
}

bool Robot::takeDamageAndLive() {
    if (damaged)
        return false;
    else {
        damaged = true;
        return true;
    }
}

void Robot::takeDamage() {
    if (damaged == false)
        damaged = true;
    else {
        cout << "Error: Robot was damaged for second time." << endl;
        exit(1);
    }    
}
