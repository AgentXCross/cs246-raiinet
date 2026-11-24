export module link;
import types;

export class Link {
protected:
    char id;
    LinkType type;
    int strength;
    Position position;
    bool revealed;
public:
    Link(char id, LinkType type, int strength, Position position);
    virtual ~Link() = default;

    virtual char get_id() const;
    virtual LinkType get_type() const;
    virtual int get_strength() const;
    virtual Position get_position() const;
    virtual bool is_revealed() const;

    virtual int movement_distance() const;
    virtual void move_to(Position p);
    virtual void reveal();
    virtual void set_type(LinkType t);
};
