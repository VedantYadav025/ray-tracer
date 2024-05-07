#include <cmath>
#include <iostream>

#include "equal.h"

class Tuple {
 private:
  float x_, y_, z_;
  bool is_point_;

 public:
  Tuple() { ; }

  constexpr Tuple(float x, float y, float z, bool is_point)
      : x_{x}, y_{y}, z_{z}, is_point_{is_point} {
    ;
  }

  Tuple point(float x, float y, float z) {
    Tuple p(x, y, z, 1);
    return p;
  }

  Tuple vector(float x, float y, float z) {
    Tuple v(x, y, z, 0);
    return v;
  }

  bool isPoint() { return (this->is_point_); }

  bool isVector() { return !(this->is_point_); }

  friend Tuple operator+(const Tuple& t1, const Tuple& t2) {
    if (t1.is_point_ && t2.is_point_)
      throw std::invalid_argument("Two points cannot be added together\n");
    Tuple add;
    add.x_ = t1.x_ + t2.x_;
    add.y_ = t1.y_ + t2.y_;
    add.z_ = t1.z_ + t2.z_;
    add.is_point_ = t1.is_point_ + t2.is_point_;

    return add;
  }

  friend Tuple operator-(const Tuple& t1, const Tuple& t2) {
    int is_point = t1.is_point_ - t2.is_point_;
    if (is_point < 0)
      throw std::invalid_argument(
          "A point cannot be substracted from a vector\n");
    float x = t1.x_ - t2.x_;
    float y = t1.y_ - t2.y_;
    float z = t1.z_ - t2.z_;
    Tuple subs(x, y, z, (bool)is_point);
    return subs;
  }

  Tuple operator-() const {
    Tuple negation(-this->x_, -this->y_, -this->z_, this->is_point_);
    return negation;
  }

  friend Tuple operator*(const float& scalar, const Tuple& t) {
    Tuple mult;
    mult.x_ = scalar * t.x_;
    mult.y_ = scalar * t.y_;
    mult.z_ = scalar * t.z_;
    mult.is_point_ = t.is_point_;
    return mult;
  }

  friend bool operator==(const Tuple& t1, const Tuple& t2) {
    if (isEqual(t1.x_, t2.x_) && isEqual(t1.y_, t2.y_) &&
        isEqual(t1.z_, t2.z_) && (t1.is_point_ == t2.is_point_))
      return true;
    else
      return false;
  }

  float magnitude() const {
    return sqrt(pow(this->x_ , 2) + pow(this->y_, 2) + pow(this->z_ , 2));
  }

  Tuple normalize() const {
    Tuple normalized_tuple;
    float magnitude = this->magnitude();
    normalized_tuple = (1 / magnitude) * (*this);
    return normalized_tuple;
  }

  float dot(Tuple& t) const {
    if ((this->is_point_) || (t.is_point_))
      throw std::invalid_argument(
          "Dot product is valid only for two vectors\n");
    float dot = (this->x_ * t.x_) + (this->y_ * t.y_) + (this->z_ * t.z_);
    return dot;
  }

  Tuple cross(Tuple& t) const {
    if ((this->is_point_) || (t.is_point_))
      throw std::invalid_argument(
          "Dot product is valid only for two vectors\n");
    Tuple crs;
    crs.x_ = this->y_ * t.z_ - this->z_ * t.y_;
    crs.y_ = this->z_ * t.x_ - this->x_ * t.z_;
    crs.z_ = this->x_ * t.y_ - this->y_ * t.x_;
    return crs;
  }
};