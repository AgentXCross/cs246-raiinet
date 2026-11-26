module setup;

import <fstream>;
import <iostream>;
import <cstdlib>;


bool make_link_setup(const std::string &filename, std::vector<LinkSetup> &links) {
    links.clear();

    const int num_links{8};
    std::vector<std::string> link_strs{};

    if (filename.empty()) {
        link_strs = {
            "D1", "D2", "D3", "D4", "V1", "V2", "V3", "V4"
        };

        // Shuffle the links.
        for (int i{0}; i < num_links; ++i) {
            int j{std::rand() % num_links};

            std::string temp{link_strs[i]};
            link_strs[i] = link_strs[j];
            link_strs[j] = temp;
        }
    } else {
        std::ifstream ifs{filename};

        if (!ifs) {
            std::cerr << "Cannot open link file: " << filename << "\n";
            return false;
        }

        std::string token{};

        while (ifs >> token) {
            link_strs.push_back(token);
        }
    }

    if (link_strs.size() != num_links) {
        std::cerr << "Expected exactly 8 links\n";
        return false;
    }

    std::vector<bool> seen(8, false);

    const char data{'D'};
    const char virus{'V'};
    const char min_strength{'1'};
    const char max_strength{'4'};

    for (const std::string &s : link_strs) {
        if (s.size() != 2 ||
            (s[0] != data && s[0] != virus) ||
            s[1] < min_strength || s[1] > max_strength) {
            std::cerr << "Invalid link: " << s << "\n";
            links.clear();
            return false;
        }

        LinkType type{
            s[0] == data ? LinkType::DATA : LinkType::VIRUS
        };

        int strength{s[1] - '0'};
        int index{(type == LinkType::DATA ? 0 : 4) + strength - 1};

        if (seen[index]) {
            std::cerr << "Duplicate link: " << s << "\n";
            links.clear();
            return false;
        }

        seen[index] = true;
        links.push_back({type, strength});
    }

    return true;
}

bool valid_ability_setup(const std::string &setup) {
    const int num_abilities{5};
    if (setup.size() != num_abilities) return false;

    const std::string allowed{"LFDSPHIR"};
    const int max_ability_count{2};

    for (char ability : setup) {
        if (allowed.find(ability) == std::string::npos) {
            return false;
        }

        int count{0}; 

        for (char c : setup) {
            if (c == ability) ++count;
        }

        if (count > max_ability_count) return false;
    }

    return true;
}
