
#include "Predator.hpp"

#include <SFML/Graphics.hpp>

namespace pred {
Predator::Predator(vec::Vector position, vec::Vector velocity)
    : Boid(position, velocity) {}

void Predator::run(
    sf::RenderWindow& window, sf::Time dt, float maxSpeedPred,
    const std::vector<std::unique_ptr<pred::Predator>>& predators, float d_s,
    float maxForce_pred) {
  vec::Vector sep = separate(predators, d_s, maxForce_pred);

  sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
  vec::Vector mousePosition_vec(static_cast<float>(mousePosition.x),
                                static_cast<float>(mousePosition.y));
  vec::Vector Follow_Mouse = mousePosition_vec - position_;

  Follow_Mouse.limit_max(2);

  velocity_ += Follow_Mouse + sep;
  velocity_.limit_max(maxSpeedPred);
  position_ += velocity_ * dt.asSeconds();
}
void Predator::render(sf::RenderWindow& window, const sf::Texture& texture) {
  Predator_Sprite = sf::Sprite(texture);
  sf::Vector2u size = texture.getSize();
  Predator_Sprite.setOrigin(static_cast<float>(size.x) / 2.0f,
                            static_cast<float>(size.y) / 2.0f);
  if (velocity_.x_ > 0) {
    Predator_Sprite.setScale(-0.3f, 0.3f);
  } else {
    Predator_Sprite.setScale(0.3f, 0.3f);
  }
  Predator_Sprite.setPosition(position_.x_, position_.y_);
  window.draw(Predator_Sprite);
}
vec::Vector Predator::separate(
    const std::vector<std::unique_ptr<pred::Predator>>& predators, float d_s,
    float maxForce_pred) {
  vec::Vector steering(0, 0);
  int count = 0;
  for (auto& other_pred : predators) {
    float distance = (position_ - other_pred->position_).magnitude();
    if (this != other_pred.get() && distance < d_s + 150) {
      steering += (position_ - other_pred->position_);
      count++;
    }
  }
  steering.limit_max(maxForce_pred);
  return steering;
}
}  // namespace pred