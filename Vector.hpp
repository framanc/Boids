#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace vec {
struct Vector {
 public:
  float x_;
  float y_;

  Vector() = default;  
  Vector(float x, float y);

  float magnitude() const;
  Vector operator-(const Vector& v) const;
  Vector operator+=(const Vector& v);
  Vector operator*(float a) const;
  Vector operator+(const Vector& v) const;
  Vector operator/(float a) const;
  Vector operator*=(const float a);
  Vector normalize();
  Vector limit_max(float max);
  Vector limit_min(float max);
  Vector setMag(float max);
};
}  // namespace vec
#endif