#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>

#include "Flock.hpp"
#include "doctest.h"

TEST_CASE("Set Position and velocity for Fish and predators") {
  flock::Flock f;
  f.addFish(vec::Vector(100, 100), vec::Vector(200, 200));

  auto position1x = (f.Get_Fish_Vector()[0]->position_.x_);
  auto position1y = (f.Get_Fish_Vector()[0]->position_.y_);
  auto velocity1x = (f.Get_Fish_Vector()[0]->velocity_.x_);
  auto velocity1y = (f.Get_Fish_Vector()[0]->velocity_.y_);

  CHECK(position1x == doctest::Approx(100));
  CHECK(position1y == doctest::Approx(100));
  CHECK(velocity1x == doctest::Approx(200));
  CHECK(velocity1y == doctest::Approx(200));
}

TEST_CASE("Testing Number of fish in the program") {
  unsigned int N_fish{34};
  unsigned int N_Predators{0};
  flock::Flock flock(&N_fish, &N_Predators);
  auto size = flock.Get_Fish_Vector().size();
  CHECK(size == N_fish);
}

TEST_CASE("Testing Number of predators in the program") {
  unsigned int N_fish{0};
  unsigned int N_predators{4};
  flock::Flock flock(&N_fish, &N_predators);
  auto size = flock.Get_Predator_Vector().size();
  CHECK(size == 4);
}

TEST_CASE("Regole di volo") {
  flock::Flock f;
  f.addFish(vec::Vector(500, 500), vec::Vector(200, 200));
  f.addFish(vec::Vector(600, 600), vec::Vector(300, 300));

  sf::Time dt = sf::seconds(1.0f);

  SUBCASE("alignment") {
    f.s = 0;
    f.c = 0;
    f.a = 0.5;
    f.d = 300;
    f.d_s = 0;
    f.maxSpeed = 500;
    f.maxForce = 100;
    f.maxTurnForce = 0;
    f.Update(dt);

    auto vel = f.Get_Fish_Vector()[0]->velocity_;

    CHECK(vel.x_ == doctest::Approx(235.355));
    CHECK(vel.y_ == doctest::Approx(235.355));
  }

  SUBCASE("separation high d_s value") {
    f.s = 1;
    f.c = 0;
    f.a = 0;
    f.d = 300;
    f.d_s = 50;
    f.maxSpeed = 500;
    f.maxForce = 100;
    f.maxTurnForce = 0;
    f.Update(dt);

    auto vel = f.Get_Fish_Vector()[0]->velocity_;

    CHECK(vel.x_ == doctest::Approx(200));
    CHECK(vel.y_ == doctest::Approx(200));
  }

  SUBCASE("separation low d_s value") {
    f.s = 1;
    f.c = 0;
    f.a = 0;
    f.d = 300;
    f.d_s = 150;
    f.maxSpeed = 500;
    f.maxForce = 100;
    f.maxTurnForce = 0;
    f.Update(dt);

    auto vel = f.Get_Fish_Vector()[0]->velocity_;

    CHECK(vel.x_ == doctest::Approx(129.290));
    CHECK(vel.y_ == doctest::Approx(129.290));
  }

  SUBCASE("cohesion") {
    f.s = 0;
    f.c = 1;
    f.a = 0;
    f.d = 300;
    f.d_s = 50;
    f.maxSpeed = 500;
    f.maxForce = 100;
    f.maxTurnForce = 0;
    f.Update(dt);

    auto vel = f.Get_Fish_Vector()[0]->velocity_;

    CHECK(vel.x_ == doctest::Approx(270.710));
    CHECK(vel.y_ == doctest::Approx(270.710));
  }
}
