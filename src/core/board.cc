export module board;

import <vector>;

import link;
import types;


export class Board {
private:
    static const int rows{8};
    static const int cols{8};

    std::vector<Link *> grid; // flat rows * cols grid of non-owning pointers

    // P1 is the player on the top, P2 on the bottom
    std::vector<Position> p1_ports{{0, 3}, {0, 4}};
    std::vector<Position> p2_ports{{7, 3}, {7, 4}};

    std::vector<Position> p1_firewalls{};
    std::vector<Position> p2_firewalls{};

    int index(Position pos) const;
    const std::vector<Position> &ports_of(PlayerID player) const;

    // Returns true if the position has a firewall not owned by player
    bool has_enemy_firewall(Position pos, PlayerID player) const;

public:
    Board();

    bool in_bounds(int row, int col) const;

    // Moves the link in direction dir.
    // Returns false (and changes nothing) if the move is illegal.
    // On success, downloaded points to the link that was downloaded during the move
    // (nullptr if none) and downloader is the player who downloaded it.
    bool move_link(
        Link *link, Direction dir, Link *&downloaded, PlayerID &downloader
    );

    // Clears the link's cell on the board
    void remove_link(Link *link);

    // Puts link on the board at position (also used to re-point a cell after a decoration)
    void place_link(Link *link, Position position);

    // Places a firewall; false if the square is a port, occupied, or already has one
    bool place_firewall(Position pos, PlayerID owner);

    // Getters return nullptr / false when out of bounds or empty.
    Link *link_at(int row, int col);
    const Link *link_at(int row, int col) const;
    bool firewall_at(int row, int col, PlayerID &owner) const;
    bool is_server_port(int row, int col) const;
};
