export module ability;

import <string>;

import abilitycontext;

export class Ability {
private:
    bool used{false};

public:
    // Applies the ability to the specified target using the game context
    // True if applied successfully
    virtual bool apply(AbilityContext &ctx, const AbilityTarget &target) = 0;

    bool is_used() const;

    // Marks as used
    // Only called by Game::use_ability not by apply()
    void mark_used();

    virtual std::string get_name() const = 0;

    virtual ~Ability() = default;
};


// Concrete abilities
export class LinkBoost : public Ability {
public:
    bool apply(AbilityContext &ctx, const AbilityTarget &target) override;
    std::string get_name() const override;
};

export class Firewall : public Ability {
public:
    bool apply(AbilityContext &ctx, const AbilityTarget &target) override;
    std::string get_name() const override;
};

export class Download : public Ability {
public:
    bool apply(AbilityContext &ctx, const AbilityTarget &target) override;
    std::string get_name() const override;
};

export class Scan : public Ability {
public:
    bool apply(AbilityContext &ctx, const AbilityTarget &target) override;
    std::string get_name() const override;
};

export class Polarize : public Ability {
public:
    bool apply(AbilityContext &ctx, const AbilityTarget &target) override;
    std::string get_name() const override;
};

export class Shield : public Ability {
public:
    bool apply(AbilityContext &ctx, const AbilityTarget &target) override;
    std::string get_name() const override;
};

export class Disguise : public Ability {
public:
    bool apply(AbilityContext &ctx, const AbilityTarget &target) override;
    std::string get_name() const override;
};

export class Strengthen : public Ability {
public:
    bool apply(AbilityContext &ctx, const AbilityTarget &target) override;
    std::string get_name() const override;
};
