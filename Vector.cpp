#include "Vector.hpp"

#include <cmath>

namespace vec {
Vector::Vector(float x, float y) {
  x_ = x;
  y_ = y;
}

Vector Vector::operator-(const Vector& v) const {
  return Vector(x_ - v.x_, y_ - v.y_);
}

Vector Vector::operator+=(const Vector& v) {
  x_ += v.x_;
  y_ += v.y_;
  return *this;       
}

Vector Vector::operator*(
    float a) const {  
  return Vector(a * x_, a * y_);
}

float Vector::magnitude() const {
  float length = std::sqrt(
      x_ * x_ + y_ * y_);  
  return length;
}

Vector Vector::operator+(const Vector& v) const {
  return Vector(x_ + v.x_, y_ + v.y_);
}

Vector Vector::operator/(float a) const { return Vector(x_ / a, y_ / a); }

Vector Vector::operator*=(const float a) {
  x_ *= a;
  y_ *= a;
  return *this;  // va messo perché restituisce non il vec passato
                 // nell'argomento ma l'altro (funzione uguale a pg 59 del pdf)
}
Vector Vector::normalize() {
  float magn = magnitude();
  x_ /= magn;
  y_ /= magn;
  return *this;
}

Vector Vector::limit_max(float max) {
  if (magnitude() > max) {
    setMag(max);
  }
  return *this;
}

Vector Vector::limit_min(float min) {
  if (magnitude() < min) {
    setMag(min);
  }
  return *this;
}

Vector Vector::setMag(float a) {
  normalize();
  *this *= a;
  return *this;
}
} // namespace vec