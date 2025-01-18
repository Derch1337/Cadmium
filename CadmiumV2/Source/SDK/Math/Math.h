#pragma once
#include <Imgui/imgui.h>
#include <corecrt_math.h>

constexpr float PI = 3.14159265358979323846f;





class Vector2
{
public:
    float x, y;

public:
    Vector2(float X, float Y) : x(X), y(Y) {}

    Vector2(float value) : x(value), y(value) {}

    Vector2() : x(0), y(0) {}

    static Vector2 Vector2Zero() {
        return Vector2(0.0f, 0.0f);
    }


    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator/(const Vector2& other) const {
        return Vector2(x / other.x, y / other.y);
    }

    Vector2& operator=(const Vector2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2& operator/=(const Vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

class Vector3
{
public:
    float x, y, z;

public:
    Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

    Vector3(float value) : x(value), y(value), z(value) {}

    Vector3() : x(0), y(0), z(0) {}

    static Vector3 Vector3Zero() {
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(const Vector3& other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }


    Vector3 operator/(const Vector3& other) const {
        return Vector3(x / other.x, y / other.y, z / other.z);
    }


    Vector3& operator=(const Vector3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }


    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }


    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }


    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3& operator*=(const Vector3& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3& operator/=(const Vector3& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
};

class Vector4
{
public:
    float x, y, z, w;

public:
    Vector4(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

    Vector4(float value) : x(value), y(value), z(value), w(value) {}

    Vector4() : x(0), y(0), z(0), w(0) {}

    static Vector4 Vector4Zero() {
        return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 operator*(const Vector4& other) const {
        return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    Vector4 operator/(const Vector4& other) const {
        return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    Vector4& operator=(const Vector4& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
        }
        return *this;
    }

    bool operator==(const Vector4& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool operator!=(const Vector4& other) const {
        return !(*this == other);
    }

    Vector4 operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Vector4 operator/(float scalar) const {
        return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    Vector4 operator-() const {
        return Vector4(-x, -y, -z, -w);
    }

    Vector4& operator+=(const Vector4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Vector4& operator-=(const Vector4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Vector4& operator*=(const Vector4& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    Vector4& operator/=(const Vector4& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    Vector4& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    Vector4& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }
};

static Vector2 ImVec2ToVector2(const ImVec2& imVec) {
    return Vector2(imVec.x, imVec.y);
}

static ImVec2 Vector2ToImVec2(const Vector2& vec) {
    return ImVec2(vec.x, vec.y);
}

static Vector4 ImVec4ToVector4(const ImVec4& imVec) {
    return Vector4(imVec.x, imVec.y, imVec.z, imVec.w);
}

static ImVec4 Vector4ToImVec4(const Vector4& vec) {
    return ImVec4(vec.x, vec.y, vec.z, vec.w);
}

class Matrix3x4_t {
private:
    float matrix[3][4];

public:
    float* operator[ ](int index) {
        return matrix[index];
    }
    const Vector3 GetPosition() {
        return { matrix[0][3], matrix[1][3], matrix[2][3] };
    }
    const Vector3 GetAngle() {
        return { matrix[0][3], matrix[1][3], matrix[2][3] };
    }
};


class ViewMatrix {
private:
    float matrix[4][4];


public:
    Vector2 screen_size;
    Vector2 screen_center;

    ViewMatrix() {
        screen_size = { 0, 0 };
    }

    float* operator[ ](int index) {
        return matrix[index];
    }

    void SetScreenData(Vector2 screenSize) {
        screen_size = screenSize;
        screen_center = {screen_size.x / 2.f, screen_size.y / 2.f};
    }

    bool WorldToScreen(Vector3 position, Vector2& out_position)
    {
        out_position.x = matrix[0][0] * position.x + matrix[0][1] * position.y + matrix[0][2] * position.z + matrix[0][3];
        out_position.y = matrix[1][0] * position.x + matrix[1][1] * position.y + matrix[1][2] * position.z + matrix[1][3];

        float w = matrix[3][0] * position.x + matrix[3][1] * position.y + matrix[3][2] * position.z + matrix[3][3];

        if (w < 0.01f)
            return false;

        float inv_w = 1.f / w;
        out_position.x *= inv_w;
        out_position.y *= inv_w;

        float x = screen_size.x * .5f;
        float y = screen_size.y * .5f;

        x += 0.5f * out_position.x * screen_size.x + 0.5f;
        y -= 0.5f * out_position.y * screen_size.y + 0.5f;

        out_position.x = x;
        out_position.y = y;
        return true;
    }
};


static float Clamp(float value, float min, float max)
{
    float result = (value < min) ? min : value;

    if (result > max) result = max;

    return result;
}

static float Lerp(float start, float end, float amount)
{
    float result = start + amount * (end - start);

    return result;
}

static float Vector2Distance(Vector2 v1, Vector2 v2)
{
    float result = sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));

    return result;
}

static float Vector3Distance(Vector3 v1, Vector3 v2)
{
    float result = 0.0f;

    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    result = sqrtf(dx * dx + dy * dy + dz * dz);

    return result;
}
static Vector3 Vector3MoveTowards(Vector3 v, Vector3 target, float maxDistance)
{
    Vector3 result = { 0 };

    float dx = target.x - v.x;
    float dy = target.y - v.y;
    float dz = target.z - v.z;
    float value = (dx * dx) + (dy * dy) + (dz * dz);

    if ((value == 0) || ((maxDistance >= 0) && (value <= maxDistance * maxDistance))) return target;

    float dist = sqrtf(value);

    result.x = v.x + dx / dist * maxDistance;
    result.y = v.y + dy / dist * maxDistance;
    result.z = v.z + dz / dist * maxDistance;

    return result;
}
