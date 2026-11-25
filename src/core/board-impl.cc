module board;


Board::Board():
    grid{std::vector<Link *>(64, nullptr)} {}

int Board::index(Position pos) const {
    return pos.get_row() * cols + pos.get_col();
}

bool Board::in_bounds(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

const std::vector<Position> &Board::ports_of(PlayerID player) const {
    return player == PlayerID::P1 ? p1_ports : p2_ports;
}

bool Board::has_enemy_firewall(Position pos, PlayerID player) const {
    const std::vector<Position> &firewalls{
        player == PlayerID::P1 ? p2_firewalls : p1_firewalls
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
    downloaded = nullptr;
    if (link == nullptr) return false;

    Position old_pos{link->get_position()};
    int old_row{old_pos.get_row()};
    int old_col{old_pos.get_col()};
    if (!in_bounds(old_row, old_col) || link_at(old_row, old_col) != link) {
        return false;
    }

    PlayerID owner;
    if (!owner_of(link->get_id(), owner)) return false;

    int new_row{old_row};
    int new_col{old_col};
    int dist{link->movement_distance()};
    if (dist <= 0) return false;

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

    // Links may only leave through the opponent's edge, never a side or their
    // own edge.
    if (new_col < 0 || new_col >= cols) return false;
    bool exits_opponent_edge{
        owner == PlayerID::P1 ? new_row >= rows : new_row < 0
    };
    bool exits_own_edge{
        owner == PlayerID::P1 ? new_row < 0 : new_row >= rows
    };
    if (exits_own_edge) return false;

    if (exits_opponent_edge) {
        remove_link(link);
        downloaded = link;
        downloader = owner;
        return true;
    }

    Position new_pos{new_row, new_col};
    for (const Position &port : ports_of(owner)) {
        if (port == new_pos) return false;
    }
    if (has_enemy_firewall(new_pos, owner)) return false;

    Link *occupant{link_at(new_row, new_col)};
    if (occupant != nullptr) {
        PlayerID occupant_owner;
        if (!owner_of(occupant->get_id(), occupant_owner) ||
            occupant_owner == owner ||
            link->get_strength() <= occupant->get_strength()) {
            return false;
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
