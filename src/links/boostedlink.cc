export module boostedlink;
import <memory>;
import link;
import linkdecorator;

export class BoostedLink : public LinkDecorator {
  public:
    explicit BoostedLink(std::unique_ptr<Link> component);
    int movement_distance() const override;
};