export module setup;

import <string>;
import <vector>;
import types;


export bool make_link_setup(
    const std::string &filename,
    std::vector<LinkSetup> &links
);

export bool valid_ability_setup(const std::string &setup);
