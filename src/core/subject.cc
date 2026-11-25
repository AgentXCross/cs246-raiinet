export module subject;

import <string>;
import <vector>;

import gamedisplay;
import types;
import link;

export class Subject {
public:
    virtual ~Subject() = default;

    virtual void attach(GameDisplay *display) = 0;
    virtual void notify_displays() = 0;

    virtual PlayerID get_current_player() const = 0;
    virtual const Link *get_link_at(int row, int col) const = 0;
    virtual std::vector<const Link *> get_player_links(PlayerID id) const = 0;

    virtual int get_downloaded_data(PlayerID id) const = 0;
    virtual int get_downloaded_viruses(PlayerID id) const = 0;

    virtual std::string get_ability_name(PlayerID id, int ability_id) const = 0;
    virtual bool is_ability_used(PlayerID id, int ability_id) const = 0;
    virtual bool is_ability_used_this_turn() const = 0;
};
