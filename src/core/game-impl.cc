module game;


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

std::vector<const Link *> Game::get_player_links(PlayerID id) const {
    return id == PlayerID::P1 ? player_1.get_links() : player_2.get_links();
}

bool Game::move(char link_id, Direction dir) {
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

    if (!using_ability->apply(*this, target)) {
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
    if (player_1.has_won() || player_2.has_lost()) {
        return PlayerID::P1;
    }

    return PlayerID::P2;
}

