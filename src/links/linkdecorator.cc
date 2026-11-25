export module linkdecorator;

import <memory>;

import types;
import link;


// Decorator ABC
export class LinkDecorator : public Link {
protected:
    std::unique_ptr<Link> component;

public:
    explicit LinkDecorator(std::unique_ptr<Link> component);

    char get_id() const override;
    LinkType get_visible_type() const override;
    LinkType get_type() const override;
    int get_strength() const override;
    Position get_position() const override;
    bool is_revealed() const override;
    bool is_fireproof() const override;

    int movement_distance() const override;
    void move_to(Position p) override;
    void reveal() override;
    void set_type(LinkType t) override;
};


// Concrete Decorators
export class BoostedLink : public LinkDecorator {
  public:
    explicit BoostedLink(std::unique_ptr<Link> component);
    int movement_distance() const override;
};

export class StrengthenedLink : public LinkDecorator {
  public:
    explicit StrengthenedLink(std::unique_ptr<Link> component);
    int get_strength() const override;
};

export class FireproofLink : public LinkDecorator {
  public:
    explicit FireproofLink(std::unique_ptr<Link> component);
    bool is_fireproof() const override;
};

export class DisguisedLink : public LinkDecorator {
  public:
    explicit DisguisedLink(std::unique_ptr<Link> component);
    LinkType get_visible_type() const override;
};



