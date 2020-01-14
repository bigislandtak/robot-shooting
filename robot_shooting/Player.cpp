#include "Player.h"

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

// A Player is created at some position (using the Arena coordinate system, where row 1, column 1 is the upper-left-most position, etc.).
// You may tell a Player to stand, move in a direction, or shoot in a direction.
// You may tell a Player to take an action of its choice.
// You may tell a Player it has died.
// You may ask a Player for its position, alive/dead status, and age. (The age is the count of how many turns the player has survived.)

Player::Player(Arena* ap, int r, int c) {
    if (ap == nullptr) {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols()) {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const {
    // TODO: TRIVIAL:  Return what row the player is at.
    // Delete the following line and replace it with the correct code.
    return m_row;  // This implementation compiles, but is incorrect.
}

int Player::col() const {
    // TODO: TRIVIAL:  Return what column the player is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

int Player::age() const {
    // TODO:  TRIVIAL:  Return the player's age.
    return m_age;  // This implementation compiles, but is incorrect.
}

string Player::takeComputerChosenTurn() {
    // TODO:  Replace this implementation:
    m_age++;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            shoot(i);
            m_age--;
        }
    }
    return "Player used special skill, shot 3 times in each direction";
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."
    
    // Here's one possible strategy:
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest robot I can hit.
    
    // A more aggressive strategy is possible, where you hunt down robots.
}

void Player::stand() {
    m_age++;
}

void Player::move(int dir) {
    m_age++;
    switch (dir) {
        case UP:
            // TODO:  Move the player up one row if possible.
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
            // TODO:  Implement the other movements.
            if (m_col < m_arena->cols())
                m_col++;
            break;
        default:
            break;
    }
}

bool Player::shoot(int dir) {
    m_age++;
    int col = m_col;
    int row = m_row;
    //cout << "inside shoot()" << endl;
    if (TESTrand() % 3 == 0) {// miss with 1/3 probability
        //cout << "Unlucky!" << endl;
        return false;
    }
    
    // TODO:  Damage the nearest robot in direction dir, returning
    // true if a robot is hit and damaged, false if not hit.
    switch (dir) {
        case UP:
            while (row >= 1 && row >= m_row-5) {
                if (m_arena->nRobotsAt(row, col) > 0) {
                    m_arena->damageRobotAt(row, col);
                    return true;
                }
                row--;
            }
            break;
        case DOWN:
            while (row <= m_arena->rows() && row <= m_row+5) {
                if (m_arena->nRobotsAt(row, col) > 0) {
                    m_arena->damageRobotAt(row, col);
                    return true;
                }
                row++;
            }
            break;
        case LEFT:
            while (col >= 1 && col >= m_col-5) {
                if (m_arena->nRobotsAt(row, col) > 0) {
                    m_arena->damageRobotAt(row, col);
                    return true;
                }
                col--;
            }
            break;
        case RIGHT:
            while (col <= m_arena->cols() && col <= m_col+5) {
                if (m_arena->nRobotsAt(row, col) > 0) {
                    m_arena->damageRobotAt(row, col);
                    return true;
                }
                col++;
            }
            break;
        default:
            break;
    }
    //cout << "No robots in that direction!" << endl;
    return false;   // return false if no robots are in that direction.
}

bool Player::isDead() const {
    // TODO:  TRIVIAL:  Return whether the player is dead.
    return m_dead;
}

void Player::setDead() {
    m_dead = true;
}
