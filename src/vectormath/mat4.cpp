#include "mat4.h"
#include <iostream>
#include <typeinfo>
Mat4::Mat4(float diagVal)
{
    setDiagVal(diagVal);
}
Mat4::~Mat4()
{
}
const float* Mat4::valuePtr() const
{
    return &mat[0][0];
}
void Mat4::setDiagVal(float diagVal)
{
    mat[0][0] = diagVal;
    mat[1][1] = diagVal;
    mat[2][2] = diagVal;
    mat[3][3] = diagVal;
}
void Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up, Mat4& result, Vec3& f, Vec3& s, Vec3& u)
{
    result.setDiagVal(1.0f);

    Vec3::subtract(center, eye, f);
    f.normalize();

    Vec3::cross(f, up, s);
    s.normalize();

    Vec3::cross(s, f, u);

    result.mat[0][0] = s.v[0];
    result.mat[1][0] = s.v[1];
    result.mat[2][0] = s.v[2];

    result.mat[0][1] = u.v[0];
    result.mat[1][1] = u.v[1];
    result.mat[2][1] = u.v[2];

    result.mat[0][2] = -f.v[0];
    result.mat[1][2] = -f.v[1];
    result.mat[2][2] = -f.v[2];

    result.mat[3][0] = -Vec3::dot(s, eye);
    result.mat[3][1] = -Vec3::dot(u, eye);
    result.mat[3][2] =  Vec3::dot(f, eye);

}
void Mat4::perspective(float fovy, float aspect, float zNear, float zFar, Mat4& result)
{
    result.setDiagVal(0.0f);
    if (fabsf(aspect) <= Vec3::EPS)
    {
        std::cerr << "Mat4::perspective() division by zero" << std::endl;
        return;
    }
    float tanHalfFovy = tanf(fovy / 2.0f);

    result.mat[0][0] = 1.0f / (aspect * tanHalfFovy);
    result.mat[1][1] = 1.0f / (tanHalfFovy);
    result.mat[2][2] = -(zFar + zNear) / (zFar - zNear);
    result.mat[2][3] = -1.0f;
    result.mat[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
}
void Mat4::operator=(const Mat4& other)
{
    mat[0][0] = other.mat[0][0];
    mat[0][1] = other.mat[0][1];
    mat[0][2] = other.mat[0][2];
    mat[0][3] = other.mat[0][3];

    mat[1][0] = other.mat[1][0];
    mat[1][1] = other.mat[1][1];
    mat[1][2] = other.mat[1][2];
    mat[1][3] = other.mat[1][3];

    mat[2][0] = other.mat[2][0];
    mat[2][1] = other.mat[2][1];
    mat[2][2] = other.mat[2][2];
    mat[2][3] = other.mat[2][3];

    mat[3][0] = other.mat[3][0];
    mat[3][1] = other.mat[3][1];
    mat[3][2] = other.mat[3][2];
    mat[3][3] = other.mat[3][3];
}

