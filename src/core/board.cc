export module board;

import <vector>;

import link;
import types;


export class Board {
private:
    std::vector<Link *> grid; // flat 64 vector grid representing the 8x8 board

    std::vector<Position> p1_ports{{0, 3}, {0, 4}};
    std::vector<Position> p2_ports{{7, 3}, {7, 4}};

public:
    Board(); // init all positions to nullptr 

    // moves the link in direction dir. downloaded points to a link if a link got downloaded during
    // the move. downloader is the player who downloaded that link
    bool move_link(
        Link *link, Direction dir, Link *&downloaded, PlayerID &downloader
    );

    void remove_link(Link *link);
    void place_link(Link *link, Position position);
    Link *link_at(int row, int col);
    const Link *link_at(int row, int col) const;
};
