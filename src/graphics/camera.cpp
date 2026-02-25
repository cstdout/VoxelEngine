#include "camera.h"

Camera::Camera()
{

}
void Camera::init(Mat4* viewMatrix,
                  Vec3 position,
                  float upX,
                  float upY,
                  float upZ,
                  float yaw,
                  float pitch,
                  float movementSpeed,
                  float mouseSensitivity)
{
    this->viewMatrix = viewMatrix;
    Position = position;
    WorldUp = Vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
    Front = Vec3(0.0f, 0.0f, -1.0f);

    Speed = movementSpeed;
    Sensitivity = mouseSensitivity;
}
void Camera::updateCameraVectors()
{
    Front = Vec3(cosf(Vec3::radians(Yaw)) * cosf(Vec3::radians(Pitch)),
                 sinf(Vec3::radians(Pitch)),
                 sinf(Vec3::radians(Yaw)) * cosf(Vec3::radians(Pitch)));
    Front.normalize();

    Vec3::cross(Front, WorldUp, Right);
    Right.normalize();

    Vec3::cross(Right, Front, Up);
    Up.normalize();
}
void Camera::updateViewMatrix()
{
    Vec3::add(Position, Front, centerVec);
    Mat4::lookAt(Position, centerVec, Up, *viewMatrix, f, s, u);
}
void Camera::onKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = Speed * deltaTime;
    if (direction == FORWARD)
    {
        Vec3::multiply(Front, velocity, positionDelta);
        Position += positionDelta;
    }
    if (direction == BACKWARD)
    {
        Vec3::multiply(Front, velocity, positionDelta);
        Position -= positionDelta;
    }
    if (direction == LEFT)
    {
        Vec3::multiply(Right, velocity, positionDelta);
        Position -= positionDelta;
    }
    if (direction == RIGHT)
    {
        Vec3::multiply(Right, velocity, positionDelta);
        Position += positionDelta;
    }
}
