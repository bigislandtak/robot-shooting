#include "Arena.h"
#include "Player.h"
#include "Robot.h"
///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////

// When an Arena object of a particular size is created, it has no robots or player. In the Arena coordinate system, row 1, column 1 is the upper-left-most position that can be occupied by a Robot or Player. (If an Arena were created with 10 rows and 20 columns, then the lower-right-most position that could be occupied would be row 10, column 20.)
// You may tell the Arena object to create or destroy a Robot at a particular position.
// You may tell the Arena object to create a Player at a particular position.
// You may tell the Arena object to have all the robots in it make their move.
// You may ask the Arena object its size, how many robots are at a particular position, and how many robots altogether are in the Arena.
// You may ask the Arena object for access to its player.
// An Arena object may be displayed on the screen, showing the locations of the robots and player, along with other status information.

Arena::Arena(int nRows, int nCols) {
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS) {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
    for (int i = 0; i < MAXROBOTS; i++)
        m_robots[i] = nullptr;
}

Arena::~Arena() {
    // TODO:  Delete the player and all remaining dynamically allocated robots.
    delete m_player;
    for (int i = 0, j = 0; i < MAXROBOTS && j < m_nRobots; i++) { // To be confirmed
        if(m_robots[i] == nullptr)
            continue;
        else {
            delete m_robots[i];
            m_robots[i] = nullptr;
            j++;
        }
    }
}

int Arena::rows() const {
    // TODO:  TRIVIAL:  Return the number of rows in the arena.
    // Delete the following line and replace it with the correct code.
    return m_rows;
}

int Arena::cols() const {
    // TODO:  TRIVIAL:  Return the number of columns in the arena.
    // Delete the following line and replace it with the correct code.
    return m_cols;
}

Player* Arena::player() const {
    return m_player;
}

int Arena::robotCount() const {
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const {
    // TODO:  Return the number of robots at row r, column c.
    int count = 0;
    for (int i = 0, j = 0; i < MAXROBOTS && j < m_nRobots; i++) {   // i iterates through the array, j keeps track of the number of robots seen so far.
        if (m_robots[i] == nullptr)
            continue;
        else
            j++;
        if (m_robots[i]->row() == r && m_robots[i]->col() == c)
            count++;
    }
    return count;
}

void Arena::display(string msg) const {
    // Position (row,col) in the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each robot's position
    // TODO:  If one robot is at some grid point, set the char to 'R'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    for (r = 0; r < rows(); r++) {
        for (c = 0; c < cols(); c++) {
            int nRobots = nRobotsAt(r+1, c+1);
            if (nRobots == 1)
                grid[r][c] = 'R';
            else if(nRobots > 1 && nRobots < 9)
                grid[r][c] = '0' + nRobots;
            else if(nRobots >= 9)
                grid[r][c] = '9';
        }
    }
    
    // Indicate player's position
    if (m_player != nullptr) {
        // Set the char to '@', unless there's also a robot there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++) {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c) {
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.
    
    // TODO:  Implement this.
    if (m_nRobots >= MAXROBOTS)
        return false;
    for (int i = 0; i < MAXROBOTS; i++) {   // Create new Robot at r, c and assign pointer to first nullptr in m_robots.
        if (m_robots[i] == nullptr) {
            m_robots[i] = new Robot(this, r, c);
            m_nRobots++;
            return true;
        }
    }
    cout << "Error: Error in addRobot." << endl;
    exit(1);
}

bool Arena::addPlayer(int r, int c) {
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    //cout << "Player added" << endl;
    return true;
}

void Arena::damageRobotAt(int r, int c) {
    // TODO:  Damage one robot at row r, column c if at least one is there.
    // If the robot does not survive the damage, destroy it.
    /*
    const int targets = nRobotsAt(r, c);
    if (targets == 0)
        return;
    Robot* targetRobots[targets];
    for (int i = 0, j = 0; i < m_nRobots && j < targets; i++) {
        if (m_robots[i]->row() == r && m_robots[i]->col() == c)
            targetRobots[j++] = m_robots[i];
    }
    int unluckyRobot = rand() % targets;
    if(targetRobots[unluckyRobot]->takeDamageAndLive())
        targetRobots[unluckyRobot]->takeDamage();
    else
        delete targetRobots[unluckyRobot];
     */
    if (nRobotsAt(r, c) == 0)
        return;
    
    for (int i = 0, j = 0; i < MAXROBOTS && j < m_nRobots; i++) {
        //cout << "damageRobotAt() loop " << i+1 << endl;
        if (m_robots[i] == nullptr)
            continue;
        else
            j++;
        
        if (m_robots[i]->row() == r && m_robots[i]->col() == c) {
            if (m_robots[i]->takeDamageAndLive()) {
                //m_robots[i]->takeDamage();
                return;
            }
            else {
                delete m_robots[i];
                m_robots[i] = nullptr;
                m_nRobots--;
                return;
            }
        }
    }
    cout << "Error: damageRobotAt" << endl;
    exit(1);
}

bool Arena::moveRobots() {
    for (int i= 0, j = 0; i < MAXROBOTS && j < m_nRobots; i++) {
        // TODO:  Have the k-th robot in the arena make one move.
        //        If that move results in that robot being in the same
        //        position as the player, the player dies.
        if (m_robots[i] == nullptr)
            continue;
        else
            j++;
        m_robots[i]->move();
        if (m_robots[i]->row() == m_player->row() && m_robots[i]->col() == m_player->col()) {
            m_player->setDead();
        }
    }
    
    // return true if the player is still alive, false otherwise
    return !m_player->isDead();
}
