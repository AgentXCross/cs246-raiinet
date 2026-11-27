module game;

import <stdexcept>;
import <iostream>;
import <variant>;

import linkdecorator;


Game::Game(
    const std::vector<LinkSetup> &p1_links,
    const std::vector<LinkSetup> &p2_links,
    const std::string &ability1,
    const std::string &ability2
): 
    board{Board()}, 
    player_1{PlayerID::P1, p1_links, ability1},
    player_2{PlayerID::P2, p2_links, ability2},
    displays{std::vector<GameDisplay *>()} // attached after
{
    // link positions have already been set, they must be placed onto the board
    for (Link *l : player_1.get_links()) {
        board.place_link(l, l->get_position());
    }

    for (Link *l : player_2.get_links()) {
        board.place_link(l, l->get_position());
    }
}

void Game::next_turn() {
    if (current_player == PlayerID::P1) current_player = PlayerID::P2;
    else current_player = PlayerID::P1;

    ability_used_this_turn = false;
}

bool Game::move(char link_id, Direction dir) {
    if (is_game_over()) return false;
    if (!is_own_link(current_player, link_id)) return false;

    Link *move_link{nullptr};

    if (current_player == PlayerID::P1) move_link = player_1.get_link(link_id);
    else move_link = player_2.get_link(link_id);

    Link *downloaded_link{nullptr};
    PlayerID downloader;

    if (!board.move_link(move_link, dir, downloaded_link, downloader)) {
        return false;
    }

    // A link was downloaded, it has already been taken off the board
    if (downloaded_link != nullptr) {
        if (downloader == PlayerID::P1) {
            player_1.download(downloaded_link);
        } else {
            player_2.download(downloaded_link);
        }
    }

    if (!is_game_over()) {
        next_turn();
    }

    // game is over notify displays
    notify_displays();
    return true;
}

bool Game::use_ability(int ability_id, AbilityTarget target) {
    if (is_game_over()) return false;

    if (ability_used_this_turn) {
        std::cerr << "Ability has already been used this turn\n";
        return false;
    }

    Ability *using_ability{nullptr};

    if (current_player == PlayerID::P1) using_ability = player_1.get_ability(ability_id);
    else using_ability = player_2.get_ability(ability_id);

    if (using_ability == nullptr || using_ability->is_used()) {
        std::cerr << "This ability has already been used\n";
        return false;
    }

    if (!using_ability->apply(*this, target)) { // ability application
        return false;
    }

    using_ability->mark_used();
    ability_used_this_turn = true;

    notify_displays(); // might not be necessary
    return true;
}

bool Game::is_game_over() const {
    return player_1.has_won() || player_1.has_lost() ||
        player_2.has_won() || player_2.has_lost();
}

PlayerID Game::winner() const {
    if (!is_game_over()) {
        throw std::runtime_error("Game::winner() called before the game is over. This shouldn't happen.");
    }

    if (player_1.has_won() || player_2.has_lost()) {
        return PlayerID::P1;
    }

    return PlayerID::P2;
}

// Observer Design Pattern

void Game::attach(GameDisplay *display) {
    for (GameDisplay *d : displays) {
        if (d == display) return;
    }

    displays.push_back(display);
}

void Game::notify_displays() {
    for (GameDisplay *d : displays) {
        d->notify();
    }
}

// Subject read-only queries
PlayerID Game::get_current_player() const {
    return current_player;
}

const Link *Game::get_link_at(int row, int col) const {
    return board.link_at(row, col);
}

std::vector<const Link *> Game::get_player_links(PlayerID id) const {
    if (id == PlayerID::P1) return player_1.get_links();
    else return player_2.get_links();
}

int Game::get_downloaded_data(PlayerID id) const {
    if (id == PlayerID::P1) return player_1.get_downloaded_data();
    else return player_2.get_downloaded_data();
};

int Game::get_downloaded_viruses(PlayerID id) const {
    if (id == PlayerID::P1) return player_1.get_downloaded_viruses();
    else return player_2.get_downloaded_viruses();
}

std::string Game::get_ability_name(PlayerID id, int ability_id) const {
    if (id == PlayerID::P1) return player_1.get_ability(ability_id)->get_name();
    else return player_2.get_ability(ability_id)->get_name();
}

bool Game::is_ability_used(PlayerID id, int ability_id) const {
    if (id == PlayerID::P1) return player_1.get_ability(ability_id)->is_used();
    else return player_2.get_ability(ability_id)->is_used();
}

bool Game::is_ability_used_this_turn() const {
    return ability_used_this_turn;
}


// Ability Context operations

bool Game::is_link_on_board(const Link *link) const {
    if (link == nullptr) return false;

    Position pos{link->get_position()};

    return board.link_at(pos.get_row(), pos.get_col()) == link;
}

Link *Game::get_link_by_id(char id) {
    if (id >= 'a' && id <= 'h') {
        return player_1.get_link(id);
    }

    if (id >= 'A' && id <= 'H') {
        return player_2.get_link(id);
    }

    return nullptr;
}

bool Game::boost_link(AbilityTarget target) {
    char *id{std::get_if<char>(&target)};
    if (id == nullptr) return false; // wasn't the correct type

    Link *target_link{get_link_by_id(*id)};
    if (target_link == nullptr) return false;

    if (!is_link_on_board(target_link)) {
        std::cerr << "Can't apply an ability to a link that is no longer on the board\n";
        return false;
    }

    Position pos{target_link->get_position()};

    Link *decorated{nullptr};

    if (*id >= 'a' && *id <= 'h') {
        decorated = player_1.boost_link(*id);
    } else if (*id >= 'A' && *id <= 'H') {
        decorated = player_2.boost_link(*id);
    }

    if (decorated == nullptr) return false;

    board.place_link(decorated, pos);
    return true;
}

bool Game::place_firewall(AbilityTarget target) {
    Position *pos{std::get_if<Position>(&target)};

    if (pos == nullptr) return false;

    // board itself checks that 
    // - the Position has no links
    // - the Position doesn't already have a Firewall
    // - the Position isn't a server port
    return board.place_firewall(*pos, current_player);
}

bool Game::download_opponent_link(AbilityTarget target) {
    char *id{std::get_if<char>(&target)};
    if (id == nullptr) return false; // wasn't the correct type

    // Already know that the link is an opponents
    PlayerID curr_player{current_player};

    Link *link_to_download{get_link_by_id(*id)};
    if (link_to_download == nullptr) return false;

    if (!is_link_on_board(link_to_download)) {
        std::cerr << "Can't download a link thats not on the board\n";
        return false;
    }

    if (curr_player == PlayerID::P1) {
        player_1.download(link_to_download);
    } else {
        player_2.download(link_to_download);
    }

    board.remove_link(link_to_download);

    return true;
}

bool Game::scan_link(AbilityTarget target) {
    char *id{std::get_if<char>(&target)};
    if (id == nullptr) return false; // wasn't the correct type

    Link *link_to_reveal{get_link_by_id(*id)};
    if (link_to_reveal == nullptr) return false;

    if (!is_link_on_board(link_to_reveal)) {
        std::cerr << "Can't scan a link that's no longer on the board\n";
        return false;
    }

    link_to_reveal->reveal();

    return true;
}

bool Game::polarize_link(AbilityTarget target) {
    char *id{std::get_if<char>(&target)};
    if (id == nullptr) return false; // wasn't the correct type

    Link *link_to_flip{get_link_by_id(*id)};
    if (link_to_flip == nullptr) return false;

    if (!is_link_on_board(link_to_flip)) {
        std::cerr << "Can't polarize a link that's no longer on the board\n";
        return false;
    }

    LinkType curr_type{link_to_flip->get_type()};

    if (curr_type == LinkType::DATA) {
        link_to_flip->set_type(LinkType::VIRUS);
    } else {
        link_to_flip->set_type(LinkType::DATA);
    }

    return true;
}

bool Game::shield_link(AbilityTarget target) {
    char *id{std::get_if<char>(&target)};
    if (id == nullptr) return false; // wasn't the correct type

    Link *target_link{get_link_by_id(*id)};
    if (target_link == nullptr) return false;

    if (!is_link_on_board(target_link)) {
        std::cerr << "Can't apply an ability to a link that is no longer on the board\n";
        return false;
    }

    Position pos{target_link->get_position()};

    Link *decorated{nullptr};

    if (*id >= 'a' && *id <= 'h') {
        decorated = player_1.shield_link(*id);
    } else if (*id >= 'A' && *id <= 'H') {
        decorated = player_2.shield_link(*id);
    }

    if (decorated == nullptr) return false;

    board.place_link(decorated, pos);
    return true;
}

bool Game::disguise_link(AbilityTarget target) {
    char *id{std::get_if<char>(&target)};
    if (id == nullptr) return false; // wasn't the correct type

    Link *target_link{get_link_by_id(*id)};
    if (target_link == nullptr) return false;

    if (!is_link_on_board(target_link)) {
        std::cerr << "Can't apply an ability to a link that is no longer on the board\n";
        return false;
    }

    Position pos{target_link->get_position()};

    Link *decorated{nullptr};

    if (*id >= 'a' && *id <= 'h') {
        decorated = player_1.disguise_link(*id);
    } else if (*id >= 'A' && *id <= 'H') {
        decorated = player_2.disguise_link(*id);
    }

    if (decorated == nullptr) return false;

    board.place_link(decorated, pos);
    return true;
}

bool Game::strengthen_link(AbilityTarget target) {
    char *id{std::get_if<char>(&target)};
    if (id == nullptr) return false; // wasn't the correct type

    Link *target_link{get_link_by_id(*id)};
    if (target_link == nullptr) return false;

    if (!is_link_on_board(target_link)) {
        std::cerr << "Can't apply an ability to a link that is no longer on the board\n";
        return false;
    }

    Position pos{target_link->get_position()};

    Link *decorated{nullptr};

    if (*id >= 'a' && *id <= 'h') {
        decorated = player_1.strengthen_link(*id);
    } else if (*id >= 'A' && *id <= 'H') {
        decorated = player_2.strengthen_link(*id);
    }

    if (decorated == nullptr) return false;

    board.place_link(decorated, pos);
    return true;
}

