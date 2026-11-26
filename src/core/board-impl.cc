module board;


Board::Board():
    grid{std::vector<Link *>(64, nullptr)} {}

int Board::index(Position pos) const {
    return pos.get_row() * cols + pos.get_col();
}

bool Board::in_bounds(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

const std::vector<Position> &Board::ports_of(PlayerID player_id) const {
    if (player_id == PlayerID::P1) {
        return p1_ports;
    } else {
        return p2_ports;
    }
}

bool Board::has_enemy_firewall(Position pos, PlayerID player_id) const {
    const std::vector<Position> &firewalls{
        player_id == PlayerID::P1 ? p2_firewalls : p1_firewalls
    };

    for (const Position &firewall : firewalls) {
        if (firewall == pos) return true;
    }

    return false;
}

Link *Board::link_at(int row, int col) {
    if (!in_bounds(row, col)) {
        return nullptr;
    }

    return grid[row * cols + col];
}

const Link *Board::link_at(int row, int col) const {
    if (!in_bounds(row, col)) {
        return nullptr;
    }

    return grid[row * cols + col];
}

bool Board::move_link(
    Link *link, Direction dir, Link *&downloaded, PlayerID &downloader
) {
    // ================= General Checks ======================
    downloaded = nullptr;
    if (link == nullptr) return false;

    Position old_pos{link->get_position()};

    int old_row{old_pos.get_row()};
    int old_col{old_pos.get_col()};

    // verify the link is still active
    if (link_at(old_row, old_col) != link) return false;

    PlayerID owner; // owner is the PlayerID of the player who is currently moving
    if (!owner_of(link->get_id(), owner)) return false;

    int new_row{old_row};
    int new_col{old_col};

    int dist{link->movement_distance()};

    switch (dir) {
        case Direction::NORTH:
            new_row -= dist;
            break;
        case Direction::EAST:
            new_col += dist;
            break;
        case Direction::SOUTH:
            new_row += dist;
            break;
        case Direction::WEST:
            new_col -= dist;
            break;
    }

    // ================= Leaving Board Checks ======================

    // Links may only leave through the opponent's edge
    if (new_col < 0 || new_col >= cols) return false; // can't exit the left or right

    bool exits_opponent_edge{
        owner == PlayerID::P1 ? new_row >= rows : new_row < 0
    };

    bool exits_own_edge{
        owner == PlayerID::P1 ? new_row < 0 : new_row >= rows
    };

    if (exits_own_edge) return false;

    if (exits_opponent_edge) {
        remove_link(link); // remove from the board
        downloaded = link;
        downloader = owner;
        return true;
    }

    // ================= Port Checks ======================

    Position new_pos{new_row, new_col};
    for (const Position &port : ports_of(owner)) {
        if (port == new_pos) return false; // can't enter your own port
    }

    for (const Position &port : ports_of(opponent_of(owner))) {
        if (port == new_pos) { // opponent will download the link
            remove_link(link);
            downloaded = link;
            downloader = opponent_of(owner);
            return true;
        }
    }

    // When entering an enemy firewall, the link is revealed unless its fireproof
    if (has_enemy_firewall(new_pos, owner) && !(link->is_fireproof())) {
        link->reveal();

        // If the link is a virus, the owner instantly downloads it
        if (link->get_type() == LinkType::VIRUS) {
            downloaded = link;
            downloader = owner;
            remove_link(link);
            return true;
        }
    }

    Link *occupant{link_at(new_row, new_col)}; // Does a link currently occupy the new pos
    if (occupant != nullptr) {
        PlayerID occupant_owner{};

        if (!owner_of(occupant->get_id(), occupant_owner)) {
            return false;
        }

        // Cannot move onto your own link
        if (occupant_owner == owner) {
            return false;
        }

        // Both links are revealed upon a battle
        link->reveal();
        occupant->reveal();

        // Attacker loses
        if (link->get_strength() < occupant->get_strength()) {
            if (link->absorb_defeat()) {
                return true; // shield consumed, no movement
            }

            remove_link(link);
            downloaded = link;
            downloader = occupant_owner;
            return true;
        } 

        // Attacker wins (also wins on strength ties)
        if (occupant->absorb_defeat()) {
            return true; // shield consumed, no movement
        }
        remove_link(occupant);
        downloaded = occupant;
        downloader = owner;
    }

    grid[index(old_pos)] = nullptr;
    grid[index(new_pos)] = link;
    link->move_to(new_pos);

    return true;
}

void Board::remove_link(Link *link) {
    if (link == nullptr) return;

    Position pos{link->get_position()};

    if (in_bounds(pos.get_row(), pos.get_col()) &&
        grid[index(pos)] == link) {
        grid[index(pos)] = nullptr;
    }
}

void Board::place_link(Link *link, Position position) {
    if (link == nullptr || !in_bounds(position.get_row(), position.get_col())) {
        return;
    }

    Position old_pos{link->get_position()};
    if (in_bounds(old_pos.get_row(), old_pos.get_col()) &&
        grid[index(old_pos)] == link) {
        grid[index(old_pos)] = nullptr;
    }
    grid[index(position)] = link;
    link->move_to(position);
}

bool Board::place_firewall(Position pos, PlayerID owner) {
    int row{pos.get_row()};
    int col{pos.get_col()};
    if (!in_bounds(row, col) || link_at(row, col) != nullptr ||
        is_server_port(row, col)) {
        return false;
    }

    PlayerID existing_owner;
    if (firewall_at(row, col, existing_owner)) return false;
    std::vector<Position> &firewalls{
        owner == PlayerID::P1 ? p1_firewalls : p2_firewalls
    };
    firewalls.push_back(pos);
    return true;
}

bool Board::firewall_at(int row, int col, PlayerID &owner) const {
    if (!in_bounds(row, col)) return false;
    Position pos{row, col};
    for (const Position &firewall : p1_firewalls) {
        if (firewall == pos) {
            owner = PlayerID::P1;
            return true;
        }
    }
    for (const Position &firewall : p2_firewalls) {
        if (firewall == pos) {
            owner = PlayerID::P2;
            return true;
        }
    }
    return false;
}

bool Board::is_server_port(int row, int col) const {
    if (!in_bounds(row, col)) return false;

    Position pos{row, col};

    for (const Position &port : p1_ports) {
        if (port == pos) return true;
    }
    for (const Position &port : p2_ports) {
        if (port == pos) return true;
    }
    return false;
}
