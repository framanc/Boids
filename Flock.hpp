#include <SFML/Graphics.hpp>
#include <vector>

#include "Fish.hpp"
#include "Predator.hpp"
#ifndef FLOCK_HPP
#define FLOCK_HPP

namespace flock {
class Flock {
 public:
  Flock();
  Flock(const unsigned int* Nfishes, const unsigned int* Npredators);

  void Initialize(unsigned int Nfishes, unsigned int Npredators);
  void addFish(vec::Vector, vec::Vector);
  void addPredators();
  void Update(sf::Time dt);
  sf::RenderWindow* GetWindow();

  // functions for test
  const std::vector<std::unique_ptr<fish::Fish>>& Get_Fish_Vector();
  const std::vector<std::unique_ptr<pred::Predator>>& Get_Predator_Vector();

  float c{0.f};
  float s{0.f};
  float d{400};
  float a{0.f};
  float d_s{100};
  float maxSpeed{100};
  float maxForce{2};
  float maxTurnForce{1};

  // PREDATORS PARAMETERS
  float maxSpeedPred{200};
  const float maxForcePred{2};
  float d_pred{150};

 private:
  void addFish(std::default_random_engine& eng);
  std::vector<std::unique_ptr<fish::Fish>> fishes;
  std::vector<std::unique_ptr<pred::Predator>> predators;
  sf::RenderWindow m_window;
  sf::Texture Fish_Texure_;
  sf::Texture Predator_Texture;
};
}  // namespace flock

#endif
