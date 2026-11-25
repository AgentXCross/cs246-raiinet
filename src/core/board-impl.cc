module board;


Board::Board():
    grid{std::vector<Link *>(64, nullptr)} {}


Link *Board::link_at(int row, int col) {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        return nullptr;
    }
    return grid[row * 8 + col];
}

const Link *Board::link_at(int row, int col) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        return nullptr;
    }
    return grid[row * 8 + col];
}


bool Board::move_link(Link *link, Direction dir) {
    if (link == nullptr) return false;

    Position old_pos{link->get_position()};

    int old_row{old_pos.get_row()};
    int old_col{old_pos.get_col()};

    Position new_pos{old_row, old_col};
    int dist{link->movement_distance()};

    if (dir == Direction::NORTH) {
        new_pos.row -= dist;
    } else if (dir == Direction::EAST) {
        new_pos.col += dist;
    } else if (dir == Direction::WEST) {
        new_pos.col -= dist;
    } else if (dir == Direction::SOUTH) {
        new_pos.row += dist;
    }

    bool player_1{link->get_id() >= 'a' && link->get_id() <= 'h'};

    // Cannot exit the left and right sides 
    if (col < 0 || col > 7) return false;

    // Cannot enter your own port
    if (player_1) {

    } else {
        
    }
}
