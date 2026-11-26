export module game;

import <vector>;
import <string>;

import board;
import player;
import link;
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

    // Flips current player, called at end of move
    void next_turn();

public:
    Game(
        const std::vector<LinkSetup> &p1_links,
        const std::vector<LinkSetup> &p2_links,
        const std::string &ability1,
        const std::string &ability2
    );
    
    ~Game() override = default;

    // Game logic

    // Validate and execute movement, return true if valid move
    // Handles any downloads if they occur, checks for game completion, advances turn
    bool move(char link_id, Direction dir);

    // Applies the players specified ability to the target 
    // Ensures the ability is available and no ability has been used this turn
    // Marks the ability used, checks for game completion
    // Returns true if successful
    bool use_ability(int ability_id, AbilityTarget target);

    // Game is over if either player has downloaded 4 viruses or 4 data links
    bool is_game_over() const;

    // Observer pattern
    void attach(GameDisplay *display) override;
    void notify_displays() override;

    // Subject: read-only queries for displays
    PlayerID get_current_player() const override;
    const Link *get_link_at(int row, int col) const override;
    std::vector<const Link *> get_player_links(PlayerID id) const override;

    int get_downloaded_data(PlayerID id) const override;
    int get_downloaded_viruses(PlayerID id) const override;

    std::string get_ability_name(PlayerID id, int ability_id) const override;
    bool is_ability_used(PlayerID id, int ability_id) const override;
    bool is_ability_used_this_turn() const override;

    // AbilityContext: operations abilities can request
    bool boost_link(AbilityTarget target) override;
    bool place_firewall(AbilityTarget target) override;
    bool download_opponent_link(AbilityTarget target) override;
    bool scan_link(AbilityTarget target) override;
    bool polarize_link(AbilityTarget target) override;
};
