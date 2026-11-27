module player;

import <stdexcept>;


Player::~Player() = default;

Player::Player(
    PlayerID id,
    const std::vector<LinkSetup> &link_setup,
    const std::string &ability_setup
): id{id}, 
   links{std::vector<std::unique_ptr<Link>>(num_links)}, 
   abilities{std::vector<std::unique_ptr<Ability>>(num_abilities)}
{   
    if (link_setup.size() != num_links|| ability_setup.size() != num_abilities) {
        throw std::invalid_argument("Error in main or controller, did not catch invalid player configurations");
    }

    const int back_row{id == PlayerID::P1 ? 0 : 7}; 
    const int front_row{id == PlayerID::P1 ? 1 : 6};

    const std::vector<Position> starting_positions{
        {back_row, 0},
        {back_row, 1},
        {back_row, 2},
        {front_row, 3}, // Port 
        {front_row, 4}, // Port
        {back_row, 5},
        {back_row, 6},
        {back_row, 7}
    };

    char link_char{0};
    if (id == PlayerID::P1) link_char = 'a';
    else link_char = 'A';

    for (int i{0}; i < num_links; ++i) {
        LinkSetup link_info{link_setup[i]};
        links[i] = std::make_unique<Link>(
            link_char, 
            link_info.type, 
            link_info.strength, 
            starting_positions[i]
        );

        ++link_char;
    }

    for (int i{0}; i < num_abilities; ++i) {
        char ability{ability_setup[i]};

        switch (ability) {
            case 'L':
                abilities[i] = std::make_unique<LinkBoost>();
                break;
            case 'F':
                abilities[i] = std::make_unique<Firewall>();
                break;
            case 'D':
                abilities[i] = std::make_unique<Download>();
                break;
            case 'S':
                abilities[i] = std::make_unique<Scan>();
                break;
            case 'P':
                abilities[i] = std::make_unique<Polarize>();
                break;
            case 'H':
                abilities[i] = std::make_unique<Shield>();
                break;
            case 'I':
                abilities[i] = std::make_unique<Disguise>();
                break;
            case 'R':
                abilities[i] = std::make_unique<Strengthen>();
                break;
            default:
                throw std::invalid_argument("Invalid ability, error in main or controller");
        }
    }
}

Link *Player::get_link(char link_id) {
    char first{id == PlayerID::P1 ? 'a' : 'A'};

    if (link_id < first || link_id >= first + num_links) {
        return nullptr;
    }

    return links[link_id - first].get();
}

Ability *Player::get_ability(int ability_id) {
    if (ability_id < 1 || ability_id > num_abilities) {
        return nullptr;
    }

    return abilities[ability_id - 1].get();
}

const Ability *Player::get_ability(int ability_id) const {
    if (ability_id < 1 || ability_id > num_abilities) {
        return nullptr;
    }

    return abilities[ability_id - 1].get();
}

std::vector<Link *> Player::get_links() {
    std::vector<Link *> result;
    result.reserve(links.size());
    for (const auto &link : links) {
        result.push_back(link.get());
    }
    return result;
}

std::vector<const Link *> Player::get_links() const {
    std::vector<const Link *> result;
    result.reserve(links.size());
    for (const auto &link : links) {
        result.push_back(link.get());
    }
    return result;
}

bool Player::has_won() const {
    const int data_to_win{4};
    return downloaded_data == data_to_win;
}

bool Player::has_lost() const {
    const int viruses_to_lose{4};
    return downloaded_viruses == viruses_to_lose;
}

void Player::download(Link *link) {
    if (link == nullptr) return;

    if (link->get_type() == LinkType::DATA) {
        ++downloaded_data;
    } else {
        ++downloaded_viruses;
    }
}

int Player::get_downloaded_data() const {
    return downloaded_data;
}

int Player::get_downloaded_viruses() const {
    return downloaded_viruses;
}
