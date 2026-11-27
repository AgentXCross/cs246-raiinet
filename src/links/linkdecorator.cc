export module linkdecorator;

import <memory>;

import types;
import link;


// Decorator ABC
export class LinkDecorator : public Link {
protected:
    std::unique_ptr<Link> component;

public:
    virtual ~LinkDecorator() = 0;
    explicit LinkDecorator(std::unique_ptr<Link> component);

    virtual char get_id() const;
    virtual LinkType get_visible_type() const;
    virtual LinkType get_type() const;
    virtual int get_strength() const;
    virtual Position get_position() const;
    virtual bool is_revealed() const;
    virtual bool is_shielded() const;
    virtual void consume_shield();

    virtual int movement_distance() const;
    virtual void move_to(Position p);
    virtual void reveal();
    virtual void set_type(LinkType t);
};

LinkDecorator::~LinkDecorator() = default;

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

export class ShieldedLink : public LinkDecorator {
private:
    bool shield_active{true};

public:
    explicit ShieldedLink(std::unique_ptr<Link> component);
    bool is_shielded() const override;
    void consume_shield() override;
};

export class DisguisedLink : public LinkDecorator {
public:
    explicit DisguisedLink(std::unique_ptr<Link> component);
    LinkType get_visible_type() const override;
};



