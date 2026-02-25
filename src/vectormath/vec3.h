#ifndef VEC3_H
#define VEC3_H

#include <cmath>
class Vec3
{
public:
    static constexpr float EPS = 1e-5f;
    static constexpr float PI_OVER_180 = M_PIf / 180.0f;
    float v[3] = {0.0f, 0.0f, 0.0f};

    Vec3(float x = 0, float y = 0, float z = 0);
    Vec3(const Vec3& other);
    ~Vec3();

    void operator+=(float alpha);
    void operator-=(float alpha);
    void operator*=(float alpha);
    bool operator/=(float alpha);
    void operator=(const Vec3& other);

    void operator+=(const Vec3& other);
    void operator-=(const Vec3& other);
    float operator*(const Vec3& other) const;

    float squaredDistance() const;
    bool normalize();

    static float dot(const Vec3& a, const Vec3& b);
    static void cross(const Vec3& a, const Vec3& b, Vec3& res);

    static float radians(float degrees);

    static void add(const Vec3& a, const Vec3& b, Vec3& res);
    static void subtract(const Vec3& a, const Vec3& b, Vec3& res);
    static void multiply(const Vec3& a, float alpha, Vec3& res);

};

#endif // VEC3_H
