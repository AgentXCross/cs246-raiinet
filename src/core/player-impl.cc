module player;

import <map>;

const 


Player(
    PlayerID id,
    const std::vector<LinkSetup> &link_setup,
    const std::string &ability_setup
): id{id}, 
   links{std::vector<std::unique_ptr<Link>>(num_links)}, 
   abilities{std::vector<std::unique_ptr<Ability>>(num_abilities)}
{   
    if (link_setup.size() != num_links) {
        throw std::invalid_argument("Invalid number of links in link_setup");
    }

    if (ability_setup.length() != num_abilities) {
        throw std::invalid_argument("Invalid number of abilities in ability_setup")
    }

    char link_char{0};
    if (id == PlayerID::P1) link_char = 'a';
    else link_char = 'A';

    for (int i{0}; i < num_links; ++i) {
        LinkSetup link_info{link_setup[i]};
        links[i] = std::make_unique(link_char, link_info.type, link_info);
    }
}

std::vector<const Link *> Player::get_links() const {
    std::vector<const Link *> result;
    result.reserve(links.size());
    for (const auto &link : links) {
        result.push_back(link.get());
    }
    return result;
}
