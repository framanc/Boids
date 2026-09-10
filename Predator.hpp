#include "Boid.hpp"
#include "Vector.hpp"  //Serve vero?
#ifndef PREDATOR_HPP
#define PREDATOR_HPP

namespace pred {
class Predator : public boid::Boid {
 public:
  Predator(vec::Vector position, vec::Vector velocity);
  ~Predator() override = default;
  void run(sf::RenderWindow& window, sf::Time dt, float maxSpeedPred,
           const std::vector<std::unique_ptr<pred::Predator>>& predators,
           float d_s, float maxForce_pred);
  void render(sf::RenderWindow& window, const sf::Texture& texture);

 private:
  sf::Sprite Predator_Sprite;
  vec::Vector separate(
      const std::vector<std::unique_ptr<pred::Predator>>& predators, float d_s,
      float maxForce_pred);
};
}  // namespace pred
#endif
