#include "Player.h"

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

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
    return m_row;
}

int Player::col() const {
    return m_col;
}

int Player::age() const {
    return m_age;
}

string Player::takeComputerChosenTurn() {
    m_age++;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            shoot(i);
            m_age--;
        }
    }
    return "Player used special skill, shot 3 times in each direction";
}

void Player::stand() {
    m_age++;
}

void Player::move(int dir) {
    m_age++;
    switch (dir) {
        case UP:
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

bool Player::shoot(int dir) {
    m_age++;
    int col = m_col;
    int row = m_row;
    if (TESTrand() % 3 == 0) {// miss with 1/3 probability
        return false;
    }
    
    // Damage the nearest robot in direction dir, returning
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
    return false;   // return false if no robots are in that direction.
}

bool Player::isDead() const {
    return m_dead;
}

void Player::setDead() {
    m_dead = true;
}
