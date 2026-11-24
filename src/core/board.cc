export module board;

import <vector>;

import link;
import types;


export class Board {
private:
    std::vector<Link *> grid; // flat 64 vector grid representing the 8x8 board

public:
    Board(); // init all positions to nullptr 
    ~Board() {}

    bool move_link(Link *link, Direction dir);
    Link *link_at(int row, int col); 
};
