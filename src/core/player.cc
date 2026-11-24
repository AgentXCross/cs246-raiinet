export module player;

import <memory>;
import <vector>;

import types;
import link;
import ability;


export class Player {
private:
    PlayerID id;
    std::vector<std::unique_ptr<Link>> links;
    std::vector<std::unique_ptr<Ability>> abilities;
    int downloaded_data{0};
    int downloaded_viruses{0};

public:
    Player(PlayerID id);
    ~Player();

    bool has_won();
    bool has_lost();
    void download(Link *link);
};  
