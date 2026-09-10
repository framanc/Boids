

#include <SFML/Graphics.hpp>

#include "Boid.hpp"
#include "Predator.hpp"

#ifndef FISH_HPP
#define FISH_HPP

namespace fish {
class Fish : public boid::Boid {
 public:
  Fish(vec::Vector position, vec::Vector velocity);
  ~Fish() override = default;

  void run(const std::vector<std::unique_ptr<fish::Fish>>& fishes,
           const std::vector<std::unique_ptr<pred::Predator>>& predators,
           sf::Time dt, float c, float s, float d, float a, float d_s,
           float maxSpeed, float maxForce, float maxTurnForce,
           sf::RenderWindow& window);
  void render(sf::RenderWindow& window, const sf::Texture& texture);

 private:
  sf::Sprite Sprite_Fish;
  vec::Vector borders(sf::RenderWindow& window, float maxTurnForce);
  vec::Vector separation(const std::vector<std::unique_ptr<fish::Fish>>& fishes,
                         float d, float maxForce, float s);
  vec::Vector align(const std::vector<std::unique_ptr<fish::Fish>>&, float d,
                    float maxForce, float a);
  vec::Vector cohesion(const std::vector<std::unique_ptr<fish::Fish>>& fishes_,
                       float d, float maxForce, float c);
  vec::Vector escape(
      const std::vector<std::unique_ptr<pred::Predator>>& predators,
      float maxForce, float d_pred);
};
}  // namespace fish
#endif
