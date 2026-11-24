export module game;

import <vector>;

import board;
import player;
import display;
import types;


export class Game : public Subject, public AbilityContext {
private:
    Board board;
    Player player_1;
    Player player_2;
    PlayerID current_player{PlayerID::P1};
    bool ability_used_this_turn{false};
    std::vector<Display *> displays;

public:
    Game();
    ~Game() = default;

    bool move(char link_id, Direction dir);
    bool use_ability(int ability_id, ...);
    bool is_game_over();
    void next_turn;
};