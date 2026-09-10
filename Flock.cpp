
#include "Flock.hpp"

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "Fish.hpp"
#include "Predator.hpp"
#include "Vector.hpp"

namespace flock {

Flock::Flock() {}

Flock::Flock(const unsigned int *Nfishes, const unsigned int *Npredators)
    : m_window(sf::VideoMode(1920, 1080), "Name") {
  Fish_Texure_.loadFromFile("Fish_Programmazione.png");
  Predator_Texture.loadFromFile("Predator.png");
  Initialize(*Nfishes, *Npredators);
  if (*Nfishes > 200 || *Npredators > 5) {
    throw std::runtime_error("Error: too many boids!");
  }
}

void Flock::Initialize(unsigned int Nfishes, unsigned int Npredators) {
  std::random_device r;
  std::default_random_engine eng(r());

  for (unsigned int i = 0; i < Nfishes; i++) {
    addFish(eng);
  }
  for (unsigned int i = 0; i < Npredators; i++) {
    addPredators();
  }
}

void Flock::addPredators() {
  std::uniform_real_distribution<float> distr(0, 1);
  float x_ = distr(eng) * static_cast<float>(m_window.getSize().x);
  float y_ = distr(eng) * static_cast<float>(m_window.getSize().x);

  predators.push_back(
      std::make_unique<pred::Predator>(vec::Vector(x_, y_), vec::Vector(0, 0)));
}
void Flock::addFish(std::default_random_engine &eng) {
  std::uniform_real_distribution<float> distr(0, 1);
  std::uniform_real_distribution<float> distr_r(0, 100);
  std::uniform_real_distribution<float> distr_theta(0, 2 * M_PI);
  float x_ = distr(eng) * static_cast<float>(m_window.getSize().x);
  float y_ = distr(eng) * static_cast<float>(m_window.getSize().y);

  float theta = distr_theta(eng);
  float r = distr_r(eng);

  float v_x = r * std::cos(theta);
  float v_y = r * std::sin(theta);

  fishes.push_back(
      std::make_unique<fish::Fish>(vec::Vector(x_, y_), vec::Vector(v_x, v_y)));
}
void Flock::addFish(vec::Vector vec1, vec::Vector vec2) {
  fishes.push_back(std::make_unique<fish::Fish>(vec1, vec2));
}

void Flock::Update(sf::Time dt) {
  for (auto &pred : predators) {
    pred->run(m_window, dt, maxSpeedPred, predators, d_s, maxForcePred);
    pred->render(m_window, Predator_Texture);
  }

  for (auto &fish : fishes) {
    fish->run(fishes, predators, dt, c, s, d, a, d_s, maxSpeed, maxForce,
              maxTurnForce, m_window);
    fish->render(m_window, Fish_Texure_);
  }
}

sf::RenderWindow *Flock::GetWindow() { return &m_window; }

const std::vector<std::unique_ptr<fish::Fish>> &Flock::Get_Fish_Vector() {
  return fishes;
}
const std::vector<std::unique_ptr<pred::Predator>> &
Flock::Get_Predator_Vector() {
  return predators;
}
}  // namespace flock