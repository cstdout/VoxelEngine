#include <iostream>
#include "vec3.h"

Vec3::Vec3(float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
Vec3::Vec3(const Vec3& other)
{
    v[0] = other.v[0];
    v[1] = other.v[1];
    v[2] = other.v[2];
}
Vec3::~Vec3()
{
}
void Vec3::operator+=(const Vec3& other)
{
    v[0] += other.v[0];
    v[1] += other.v[1];
    v[2] += other.v[2];
}
void Vec3::operator-=(const Vec3& other)
{
    v[0] -= other.v[0];
    v[1] -= other.v[1];
    v[2] -= other.v[2];
}
void Vec3::operator+=(float alpha)
{
    v[0] += alpha;
    v[1] += alpha;
    v[2] += alpha;
}
void Vec3::operator-=(float alpha)
{
    v[0] -= alpha;
    v[1] -= alpha;
    v[2] -= alpha;
}
void Vec3::operator*=(float alpha)
{
    v[0] *= alpha;
    v[1] *= alpha;
    v[2] *= alpha;
}
bool Vec3::operator/=(float alpha)
{
    if(fabsf(alpha) > EPS)
    {
        v[0] /= alpha;
        v[1] /= alpha;
        v[2] /= alpha;
        return true;
    }
    std::cerr << "Vec3 division by zero" << std::endl;
    return false;
}
void Vec3::operator=(const Vec3& other)
{
    v[0] = other.v[0];
    v[1] = other.v[1];
    v[2] = other.v[2];
}
float Vec3::squaredDistance() const
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}
bool Vec3::normalize()
{
    float d = squaredDistance();
    if(d > EPS)
    {
        d = 1.0f / sqrtf(d);
        operator*=(d);
        return true;
    }
    std::cerr << "Vec3::normalize() division by zero" << std::endl;
    return false;
}
float Vec3::dot(const Vec3& a, const Vec3& b)
{
    return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2];
}
float Vec3::operator*(const Vec3 &other) const
{
    return dot(*this, other);
}
void Vec3::cross(const Vec3 &a, const Vec3 &b, Vec3& res)
{
    res.v[0] = a.v[1] * b.v[2] - b.v[1] * a.v[2];
    res.v[1] = a.v[2] * b.v[0] - b.v[2] * a.v[0];
    res.v[2] = a.v[0] * b.v[1] - b.v[0] * a.v[1];
}
float Vec3::radians(float degrees)
{
    return degrees * PI_OVER_180;
}
void Vec3::add(const Vec3& a, const Vec3& b, Vec3& res)
{
    res.v[0] = a.v[0] + b.v[0];
    res.v[1] = a.v[1] + b.v[1];
    res.v[2] = a.v[2] + b.v[2];
}
void Vec3::subtract(const Vec3& a, const Vec3& b, Vec3& res)
{
    res.v[0] = a.v[0] - b.v[0];
    res.v[1] = a.v[1] - b.v[1];
    res.v[2] = a.v[2] - b.v[2];
}
void Vec3::multiply(const Vec3& a, float alpha, Vec3& res)
{
    res.v[0] = a.v[0] * alpha;
    res.v[1] = a.v[1] * alpha;
    res.v[2] = a.v[2] * alpha;
}
void Vec3::fill(float val)
{
    v[0] = val;
    v[1] = val;
    v[2] = val;
}
