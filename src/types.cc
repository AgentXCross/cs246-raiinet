export module types;

import <stdexcept>;

export enum class PlayerID {
    P1,
    P2
};

export enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

export enum class LinkType {
    DATA,
    VIRUS
};

export struct Position {
private:
    int row;
    int col;

public:
    explicit Position(int row, int col): row{row}, col{col}
    {
        if (row < 0 || row > 7 || col < 0 || col > 7) {
            throw std::out_of_range("Invalid board position");
        }
    }

    int get_row() const { return row; };
    int get_col() const { return col; };

    bool operator==(const Position &other) const {
        return row == other.row && col == other.col;
    }
};


// Some shared helpers
export bool is_opponent_link(PlayerID player, char link_id) {
    if (player == PlayerID::P1) {
        return link_id >= 'A' && link_id <= 'H';
    }

    return link_id >= 'a' && link_id <= 'h';
}

export bool is_own_link(PlayerID player, char link_id) {
    return !is_opponent_link(player, link_id);
}

export PlayerID opponent_of(PlayerID player) {
    return player == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1;
}

// Returns by reference who owns link_id, false if invalid link_id
export bool owner_of(char link_id, PlayerID &owner) {
    if (link_id >= 'a' && link_id <= 'h') {
        owner = PlayerID::P1;
        return true;
    }

    if (link_id >= 'A' && link_id <= 'H') {
        owner = PlayerID::P2;
        return true;
    }

    return false;
}
