export module gamedisplay;

import types;
import link;
import board;


// Abstract observer
export class GameDisplay {
protected:
    // Returns whether the specified link is visible to the viewer.
    static bool is_visible(const Link &link, PlayerID viewer);

    // Returns the character used to represent a board cell.
    static char cell_symbol(const Board &board, Position pos);
    
public:
    virtual ~GameDisplay() = default;
    virtual void notify() = 0;
};

