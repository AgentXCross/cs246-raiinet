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
    int x;
    int y;

public:
    explicit Position(int x, int y): x{x}, y{y}
    {
        if (x < 0 || x > 7 || y < 0 || y > 7) {
            throw std::out_of_range("Invalid board position");
        }
    }

    int get_x() const { return x; };
    int get_y() const { return y; };
};
