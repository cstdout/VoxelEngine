#ifndef MAT4_H
#define MAT4_H


#include <cstdint>
#include "vec3.h"
class Mat4
{
public:
    Mat4(float diagVal = 0.0f);
    ~Mat4();

    float mat[4][4] =
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };
    void setDiagVal(float diagVal);
    const float* valuePtr() const;
    static constexpr uint32_t sizeInBytes = sizeof(float) * 16;

    static void lookAt(const Vec3& eye,
                       const Vec3& center,
                       const Vec3& up,
                       Mat4& result,
                       Vec3& f,
                       Vec3& s,
                       Vec3& u);
    static void perspective(float fovy, float aspect, float zNear, float zFar, Mat4& result);
    void operator=(const Mat4& other);

};


#endif // MAT4_H
