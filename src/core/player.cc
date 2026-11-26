export module player;

import <memory>;
import <vector>;
import <stdexcept>;

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

    static const int num_links{8};
    static const int num_abilities{5};

public:
    Player(
        PlayerID id,
        const std::vector<LinkSetup> &link_setup,
        const std::string &ability_setup
    );
    ~Player();

    Link *get_link(char id);
    Ability *get_ability(int id);
    std::vector<const Link *> get_links() const;
    
    bool has_won() const; // true if downloaded_data == 4
    bool has_lost() const; // true if downloaded_viruses == 4

    // Records a downloaded link by incrementing one of the downloaded fields
    void download(Link *link);
};  
