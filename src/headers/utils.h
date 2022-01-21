#ifndef UTIL_H
#define UTIL_H
#include <cstdint>

constexpr float pi = 3.14159265f;

#define ut_clamp(val, min, max) ((val) > (max)) ? (max) : ((val) < (min)) ? (min) : (val)

static float Q_rsqrt(float number )
{
    int32_t i;
    float x2, y;
    const float threehalfs = 1.5f;
    x2 = number * 0.5f;
    y  = number;
    i  = *(int32_t*) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = *(float*)&i;
    y  = y * (threehalfs - (x2 * y * y));   // 1st iteration
    //  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    return y;
}

template <typename T>
struct __vec2 {
    T x, y;
    __vec2() {x = 0; y = 0;};
    __vec2(T vx, T vy) {x = vx; y = vy;};
    __vec2 operator +(const __vec2 &op) const {return {x + op.x, y + op.y};}
    __vec2 operator -(const __vec2 &op) const {return {x - op.x, y - op.y};}
    __vec2 operator *(const __vec2 &op) const {return {x * op.x, y * op.y};}
    __vec2 operator /(const __vec2 &op) const {return {x / op.x, y / op.y};}
    void operator +=(const __vec2 &op) {x += op.x; y += op.y;}
    void operator -=(const __vec2 &op) {x -= op.x; y -= op.y;}
    void operator *=(const __vec2 &op) {x *= op.x; y *= op.y;}
    void operator /=(const __vec2 &op) {x /= op.x; y /= op.y;}
    __vec2 operator *(const T &op) const {return {x * op, y * op};}
    __vec2 operator /(const T &op) const {return {x / op, y / op};}
    void operator *=(const T &op) {x *= op; y *= op;}
    void operator /=(const T &op) {x /= op; y /= op;}
    __vec2 perpendicular() const {return {-y, x};};
    void zero() {x = 0; y = 0;};
    float dot(const __vec2 &op) const {return x * op.y + y * op.x;}
    float magnitude() const {
        float sqr = (x * x + y * y);
        return Q_rsqrt(sqr) * sqr;
    }
    __vec2 normalized() {
        float invmag = Q_rsqrt(x * x + y * y);
        return {x * invmag, y * invmag};
    }
};

typedef __vec2<float> Vec2f;
typedef __vec2<int> Vec2i;

#endif
