export module board;

import <vector>;

import link;
import types;


export class Board {
private:
    std::vector<Link *> grid; // flat 64 vector grid representing the 8x8 board

public:
    Board(); // init all positions to nullptr 

    bool move_link(Link *link, Direction dir);
    void place_link(Link *link, Position position);
    Link *link_at(int row, int col);
    const Link *link_at(int row, int col) const;
};
