
#include "Fish.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Boid.hpp"
#include "Vector.hpp"

namespace fish {
Fish::Fish(vec::Vector position, vec::Vector velocity)
    : boid::Boid(position, velocity) {}

void Fish::run(const std::vector<std::unique_ptr<fish::Fish>>& fishes_,
               const std::vector<std::unique_ptr<pred::Predator>>& predators,
               sf::Time dt, float c, float s, float d, float a, float d_s,
               float maxSpeed, float maxForce, float maxTurnForce,
               sf::RenderWindow& window) {
  auto ali = align(fishes_, d, maxForce, a);
  auto cohes = cohesion(fishes_, d, maxForce, c);
  auto sep = separation(fishes_, d_s, maxForce, s);
  vec::Vector bord = borders(window, maxTurnForce);
  vec::Vector esc = escape(predators, maxForce, d);

  velocity_ = velocity_ + ali + sep + cohes + bord + esc;

  velocity_.limit_max(maxSpeed);

  position_ += velocity_ * dt.asSeconds();
}

vec::Vector Fish::align(const std::vector<std::unique_ptr<fish::Fish>>& fishes,
                        float d, float maxForce, float a) {
  vec::Vector steering(0, 0);
  int count = 0;
  for (auto& other_fish : fishes) {
    auto distance = (position_ - other_fish->position_).magnitude();
    if (this != other_fish.get() && distance < d) {
      steering = steering + other_fish->velocity_;
      count++;
    }
  }
  if (count > 0) {
    steering = (steering / static_cast<float>(count));

    steering = steering - velocity_;

    steering.limit_max(maxForce);

    steering = steering * a;
  }
  return steering;
}

vec::Vector Fish::cohesion(
    const std::vector<std::unique_ptr<fish::Fish>>& fishes, float d,
    float maxForce, float c) {
  vec::Vector steering(0, 0);
  int count = 0;
  for (auto& other_fish : fishes) {
    auto distance = (position_ - other_fish->position_).magnitude();
    if (this != other_fish.get() && distance < d) {
      steering = steering + other_fish->position_;
      count++;
    }
  }
  if (count > 0) {
    steering = (steering / static_cast<float>(count));
    steering = steering - position_;
    steering.limit_max(maxForce);
    steering = steering * c;
  }
  return steering;
}

vec::Vector Fish::separation(
    const std::vector<std::unique_ptr<fish::Fish>>& fishes, float d_s,
    float maxForce, float s) {
  vec::Vector steering(0, 0);
  int count = 0;
  for (auto& other_fish : fishes) {
    float distance = (position_ - other_fish->position_).magnitude();
    if (this != other_fish.get() && distance < d_s) {
      steering += (position_ - other_fish->position_);
      count++;
    }
  }

  steering.limit_max(maxForce);

  steering *= s;

  return steering;
}

vec::Vector Fish::borders(sf::RenderWindow& window, float maxTurnForce) {
  const float margin = 200;
  vec::Vector turn(0, 0);
  const float turnfactor = 100;
  // const float maxTurnForce = 0.5;
  float width = static_cast<float>(window.getSize().x);
  float height = static_cast<float>(window.getSize().y);

  if (position_.x_ < margin) {
    if (position_.x_ < 0) {
      position_.x_ = 0;
      velocity_.x_ = 0;
    }
    turn.x_ += turnfactor;
  } else if (position_.x_ > width - margin) {
    if (position_.x_ > width) {
      position_.x_ = width;
    }
    turn.x_ -= turnfactor;
  }

  if (position_.y_ > height - margin) {
    if (position_.y_ > height) {
      position_.y_ = height;
    }
    turn.y_ -= turnfactor;

  } else if (position_.y_ < margin) {
    if (position_.y_ < 0) {
      position_.y_ = 0;
    }
    turn.y_ += turnfactor;
  }
  turn.limit_max(maxTurnForce);
  return turn;
}

vec::Vector Fish::escape(
    const std::vector<std::unique_ptr<pred::Predator>>& predators,
    float maxForce, float d_pred) {
  vec::Vector escape_v(0, 0);

  for (auto& pred : predators) {
    vec::Vector distance = position_ - pred->position_;
    if (distance.magnitude() < d_pred) {
      escape_v += distance;
    }
  }
  escape_v.limit_max(maxForce);
  return escape_v;
}

void Fish::render(sf::RenderWindow& window, const sf::Texture& texture) {
  Sprite_Fish = sf::Sprite(texture);
  sf::Vector2u size = texture.getSize();
  Sprite_Fish.setOrigin(static_cast<float>(size.x) / 2.0f,
                        static_cast<float>(size.y) / 2.0f);
  if (velocity_.x_ > 0) {
    Sprite_Fish.setScale(-0.3f, 0.3f);
  } else {
    Sprite_Fish.setScale(0.3f, 0.3f);
  }
  Sprite_Fish.setPosition(position_.x_, position_.y_);
  window.draw(Sprite_Fish);
}
}  // namespace fish
