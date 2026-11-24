export module linkdecorator;
import <memory>;
import types;
import link;

export class LinkDecorator : public Link {
  protected:
    std::unique_ptr<Link> component;
  public:
    explicit LinkDecorator(std::unique_ptr<Link> component);

    char get_id() const override;
    LinkType get_type() const override;
    int get_strength() const override;
    Position get_position() const override;
    bool is_revealed() const override;

    int movement_distance() const override;
    void move_to(Position p) override;
    void reveal() override;
    void set_type(LinkType t) override;
};