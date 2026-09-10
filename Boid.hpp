
#include <SFML/Graphics.hpp>

#include "Vector.hpp"
#ifndef BOID_HPP
#define BOID_HPP

namespace boid {
struct Boid {
  vec::Vector position_;  
  vec::Vector velocity_;  

  Boid(vec::Vector position, vec::Vector velocity);
  virtual ~Boid() = 0;

};
inline Boid::~Boid() = default;
}  // namespace boid
#endif
