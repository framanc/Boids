#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <vector>

#include "Fish.hpp"
#include "Flock.hpp"
#include "Predator.hpp"

int main() {
  unsigned int N_fish;
  unsigned int N_Predators;
  std::cout << "Set number of fish (max 200):";
  std::cin >> N_fish;
  std::cout << "Set number of Predators (max 5):";
  std::cin >> N_Predators;
  flock::Flock flock(&N_fish, &N_Predators);

  tgui::Gui gui(*(flock.GetWindow()));

  tgui::Theme theme{"TGUI/themes/Black.txt"};

  // create panel
  auto panel = tgui::Panel::create({300, 500});
  panel->setRenderer(theme.getRenderer("Panel"));
  panel->setPosition({10, 10});
  auto name = tgui::Label::create();
  name->setRenderer(theme.getRenderer("Label"));
  name->setText("Parameters");
  name->setPosition(110, 25);
  name->setTextSize(16);
  gui.add(panel);
  gui.add(name);

  auto createWidget = [&](std::string title, float min, float max, float& par,
                          int yPos, float step) {
    auto label = tgui::Label::create(title);
    label->setRenderer(theme.getRenderer("Label"));
    label->setPosition(10, yPos);
    panel->add(label);

    auto valLabel = tgui::Label::create(std::to_string(static_cast<int>(par)));
    valLabel->setRenderer(theme.getRenderer("Label"));
    valLabel->setPosition(180, yPos);
    panel->add(valLabel);

    auto slider = tgui::Slider::create();
    slider->setRenderer(theme.getRenderer("Slider"));
    slider->setPosition(25, yPos + 25);
    slider->setSize(240, 18);
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setValue(par);
    slider->setStep(step);

    slider->onValueChange([&par, valLabel](float val) {
      par = val;

      char buffer[10];
      snprintf(buffer, sizeof(buffer), "%.1f", val);
      valLabel->setText(buffer);
    });

    panel->add(slider);
    return slider;
  };

  createWidget("Cohesion", 0.f, 3.f, flock.c, 50, 0.5f);
  createWidget("Separation", 0.f, 5.f, flock.s, 110, 1.f);
  createWidget("Alignment", 0.f, 0.9f, flock.a, 170, 0.1f);
  createWidget("Max fish velocity", 0.f, 500.f, flock.maxSpeed, 230, 5.f);
  createWidget("Max predator velocity", 0.f, 500.f, flock.maxSpeedPred, 290,
               5.f);

  auto sliderRange =
      createWidget("Visual Range", 0.f, 500.f, flock.d, 350, 5.f);
  auto sliderSepDist =
      createWidget("Separation distance", 0.f, 300.f, flock.d_s, 410, 5.f);

  sliderRange->onValueChange([&flock, sliderSepDist](float val) {
    flock.d = val;
    if (val > 100) {
      sliderSepDist->setMaximum(val - 100);
    } else {
      sliderSepDist->setMaximum(0);
    }
  });

  bool pause = false;

  sf::Clock deltaClock;

  sf::Event event;

  bool was_space_key_pressed = false;

  // SPRITE BACKGROUND
  sf::Texture TextureBackground;
  TextureBackground.loadFromFile("aquarium.jpeg");
  sf::Sprite SpriteBackground(TextureBackground);
  SpriteBackground.setPosition(0, 0);
  SpriteBackground.setScale(1.35f, 1.1f);

  // SPRITE ALGAE
  sf::Texture Texture_Algae;
  Texture_Algae.loadFromFile("algae.png");
  sf::Sprite Sprite_Algae(Texture_Algae);
  Sprite_Algae.setPosition(350, 367);
  Sprite_Algae.setScale(2, 2);

  while (flock.GetWindow()->isOpen()) {
    sf::Time dt = deltaClock.restart();
    while (flock.GetWindow()->pollEvent(event)) {
      gui.handleEvent(event);
      if (event.type == sf::Event::Closed) {
        flock.GetWindow()->close();
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      if (!was_space_key_pressed) {
        pause = !pause;
      }
      was_space_key_pressed = true;
    } else {
      was_space_key_pressed = false;
    }
    flock.GetWindow()->clear();
    flock.GetWindow()->draw(SpriteBackground);

    if (!pause) {
      gui.draw();
      flock.Update(dt);
      dt = deltaClock.restart();
    }
    flock.GetWindow()->draw(Sprite_Algae);
    flock.GetWindow()->display();
  }
}