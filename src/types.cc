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
