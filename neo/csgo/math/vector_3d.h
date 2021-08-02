#pragma once
#include <sstream>
#define deg(a)a * 57.295779513082
class vec3_t {
public:
    vec3_t(void)
    {
        invalidate();
    }
    vec3_t(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
    }
    vec3_t(const float* clr)
    {
        x = clr[0];
        y = clr[1];
        z = clr[2];
    }
    void init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
    {
        x = ix; y = iy; z = iz;
    }
    bool is_valid() const
    {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }
    void invalidate()
    {
        x = y = z = std::numeric_limits<float>::infinity();
    }
    vec3_t cross(const vec3_t& vOther) const
    {
        return vec3_t(y * z - z * vOther.y, z * vOther.x - x * vOther.z, x * vOther.y - y * vOther.x);
    }
    inline vec3_t angle(vec3_t* up = 0) {
        if (!x && !y)
            return vec3_t(0, 0, 0);
        double roll = 0;
        if (up) {
            vec3_t left = (*up).cross(*this);
            roll = deg(atan2f(left.z, (left.y * x) - (left.x * y)));
        }
        return vec3_t((float)(deg(atan2f(-z, sqrtf(x * x + y * y)))), (float)(deg(atan2f(y, x))), (float)roll);
    }
    float& operator[](int i)
    {
        return ((float*)this)[i];
    }
    float operator[](int i) const
    {
        return ((float*)this)[i];
    }
    void zero()
    {
        x = y = z = 0.0f;
    }
    bool operator==(const vec3_t& src) const
    {
        return (src.x == x) && (src.y == y) && (src.z == z);
    }
    bool operator!=(const vec3_t& src) const
    {
        return (src.x != x) || (src.y != y) || (src.z != z);
    }
    vec3_t& operator+=(const vec3_t& v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    vec3_t& operator-=(const vec3_t& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    vec3_t& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }
    vec3_t& operator*=(const vec3_t& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    vec3_t& operator/=(const vec3_t& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    vec3_t& operator+=(float fl)
    {
        x += fl;
        y += fl;
        z += fl;
        return *this;
    }
    vec3_t& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        z /= fl;
        return *this;
    }
    vec3_t& operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        z -= fl;
        return *this;
    }
    void normalize_in_place()
    {
        *this = normalized();
    }
    vec3_t normalized() const
    {
        vec3_t res = *this;
        float l = res.length();
        if (l != 0.0f) {
            res /= l;
        }
        else {
            res.x = res.y = res.z = 0.0f;
        }
        return res;
    }
    inline vec3_t clamp() {
        if (this->x < -89.0f)
            this->x = -89.0f;
        if (this->x > 89.0f)
            this->x = 89.0f;
        while (this->y < -180.0f)
            this->y += 360.0f;
        while (this->y > 180.0f)
            this->y -= 360.0f;
        this->z = 0.0f;
        return *this;
    }
    float dist_to(const vec3_t& vOther) const {
        vec3_t delta;
        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;
        return delta.length();
    }
    float dist_to_sqr(const vec3_t& vOther) const {
        vec3_t delta;
        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;
        return delta.length_sqr();
    }
    float dot_o(const vec3_t& vOther) const
    {
        return (x * vOther.x + y * vOther.y + z * vOther.z);
    }
    float length() const
    {
        return sqrt(x * x + y * y + z * z);
    }
    float length_sqr(void) const
    {
        return (x * x + y * y + z * z);
    }
    float length_2d() const
    {
        return sqrt(x * x + y * y);
    }
    vec3_t& operator=(const vec3_t& vOther)
    {
        x = vOther.x; y = vOther.y; z = vOther.z;
        return *this;
    }
    vec3_t vec3_t::operator-(void) const
    {
        return vec3_t(-x, -y, -z);
    }
    vec3_t vec3_t::operator+(const vec3_t& v) const
    {
        return vec3_t(x + v.x, y + v.y, z + v.z);
    }
    vec3_t vec3_t::operator-(const vec3_t& v) const
    {
        return vec3_t(x - v.x, y - v.y, z - v.z);
    }
    vec3_t vec3_t::operator*(float fl) const
    {
        return vec3_t(x * fl, y * fl, z * fl);
    }
    vec3_t vec3_t::operator*(const vec3_t& v) const
    {
        return vec3_t(x * v.x, y * v.y, z * v.z);
    }
    vec3_t vec3_t::operator/(float fl) const
    {
        return vec3_t(x / fl, y / fl, z / fl);
    }
    vec3_t vec3_t::operator/(const vec3_t& v) const
    {
        return vec3_t(x / v.x, y / v.y, z / v.z);
    }
    void vec3_t::mul_add(const vec3_t& a, const vec3_t& b, float scalar) {
        x = a.x + b.x * scalar;
        y = a.y + b.y * scalar;
        z = a.z + b.z * scalar;
    }
    void vec3_t::mul(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }
    float vec3_t::dot(const vec3_t& other) const {
        return (x * other.x + y * other.y + z * other.z);
    }
    float x, y, z;
};

inline vec3_t operator*(float lhs, const vec3_t& rhs)
{
    return rhs * lhs;
}
inline vec3_t operator/(float lhs, const vec3_t& rhs)
{
    return rhs / lhs;
}

class __declspec(align(16)) vec3_tAligned : public vec3_t
{
public:
    inline vec3_tAligned(void) {};
    inline vec3_tAligned(float X, float Y, float Z)
    {
        init(X, Y, Z);
    }
public:
    explicit vec3_tAligned(const vec3_t& vOther)
    {
        init(vOther.x, vOther.y, vOther.z);
    }
    vec3_tAligned& operator=(const vec3_t& vOther)
    {
        init(vOther.x, vOther.y, vOther.z);
        return *this;
    }
    vec3_tAligned& operator=(const vec3_tAligned& vOther)
    {
        init(vOther.x, vOther.y, vOther.z);
        return *this;
    }
    float w;
};