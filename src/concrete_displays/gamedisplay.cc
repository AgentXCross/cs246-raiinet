export module gamedisplay;
import types;
import link;
import board;


export class GameDisplay {
  public:
    virtual ~GameDisplay() = default;
    virtual void notify() = 0;
};

export PlayerID owner_of(char link_id);
export bool is_visible(const Link &l, PlayerID viewer);
export char cell_symbol(const Board &b, Position p);
