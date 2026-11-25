export module board;

import <vector>;

import link;
import types;


export class Board {
private:
    std::vector<Link *> grid; // flat 64 vector grid representing the 8x8 board

    // Each players server ports. P1 is the player on the top, P2 on the bottom
    std::vector<Position> p1_ports{{0, 3}, {0, 4}};
    std::vector<Position> p2_ports{{7, 3}, {7, 4}};

    std::vector<Position> p1_firewalls{};
    std::vector<Position> p2_firewalls{};

    // Returns true if the position has an enemy firewall
    bool has_enemy_firewall(Position pos, PlayerID player) const;

public:
    Board(); // init all positions to nullptr 

    // moves the link in direction dir
    // downloaded points to a link if a link got downloaded during the move 
    // downloader is the player who downloaded that link
    // returns true if the user entered valid input
    bool move_link(
        Link *link, Direction dir, Link *&downloaded, PlayerID &downloader
    );

    // Removes a link from the board by turning its position on the board to nullptr
    void remove_link(Link *link);

    void place_link(Link *link, Position position);

    // Getters
    // return nullptr if out of bounds or not link at the position
    Link *link_at(int row, int col);
    const Link *link_at(int row, int col) const;

    bool place_firewall(Position pos, PlayerID owner);
};
