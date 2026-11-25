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

    Link *get_link(char id);
    Ability *get_ability(int id);

    
    bool has_won() const; // true if downloaded_data == 4
    bool has_lost() const; // true if downloaded_viruses == 4

    // Records a downloaded link by incrementing one of the downloaded fields
    void download(Link *link);
};  
