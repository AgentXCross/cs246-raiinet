export module game;

import <vector>;

import board;
import player;
import gamedisplay;
import types;
import subject;
import abilitycontext;


export class Game : public Subject, public AbilityContext {
private:
    Board board;
    Player player_1;
    Player player_2;
    PlayerID current_player{PlayerID::P1};
    bool ability_used_this_turn{false};
    std::vector<GameDisplay *> displays;

    void next_turn();

public:
    Game();
    ~Game() override = default;

    // Game logic
    bool move(char link_id, Direction dir);
    bool use_ability(int ability_id, AbilityTarget target);
    bool is_game_over();

    // Observer pattern
    void attach(GameDisplay *display);
    void notify_displays();

    // Subject: read-only queries for displays
    PlayerID get_current_player() const override;
    const Link *get_link_at(int row, int col) const override;

    int get_downloaded_data(PlayerID id) const override;
    int get_downloaded_viruses(PlayerID id) const override;

    const char *get_ability_name(PlayerID id, int ability_id) const override;
    bool is_ability_used(PlayerID id, int ability_id) const override;
    bool is_ability_used_this_turn() const override;

    // AbilityContext: operations abilities can request
    bool boost_link(AbilityTarget target) override;
    bool place_firewall(AbilityTarget target) override;
    bool download_opponent_link(AbilityTarget target) override;
    bool scan_link(AbilityTarget target) override;
    bool polarize_link(AbilityTarget target) override;
};
