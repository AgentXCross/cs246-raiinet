export module abilitycontext;

import <variant>;

import types;

export using ability_target = std::variant<char, Position>;

export class ability_context {
  public:
    virtual bool boostLink(char id) = 0;
    virtual bool placeFirewall(Position pos) = 0;
    virtual bool downloadOpponentLink(char id) = 0;
    virtual bool scanLink(char id) = 0;
    virtual bool polarizeLink(char id) = 0;
    virtual ~ability_context() = default;
};
