# include "../../includes/math/Math.hpp"

namespace math {
    float radians (float degrees) {
        return degrees * 0.01745329251994329576923690768489f;
    }

    Vec3 normalize(const Vec3 &vec3) {
        float length = std::sqrt(vec3._x * vec3._x + vec3._y * vec3._y + vec3._z * vec3._z);
        if (length == 0)
            return Vec3(0.0f, 0.0f, 0.0f);
        return Vec3(vec3._x / length, vec3._y / length, vec3._z / length);
    }

    Vec3 cross(const Vec3 &vec1, const Vec3 &vec2) {
        return Vec3(
            vec1._y * vec2._z - vec1._z * vec2._y,
            vec1._z * vec2._x - vec1._x * vec2._z,
            vec1._x * vec2._y - vec1._y * vec2._x
        );
    }

    float dot(const Vec3 &vec1, const Vec3 &vec2) {
        return vec1._x * vec2._x + vec1._y * vec2._y + vec1._z * vec2._z;
    }
    
    Mat4 lookAt(const Vec3 &cameraPos, const Vec3 &target, const Vec3 &up) {
        Vec3 zAxis = normalize(target - cameraPos);
        Vec3 xAxis = normalize(cross(up, zAxis));
        Vec3 yAxis = cross(zAxis, xAxis);

        Mat4 result;
        
        result._data[0][0] = xAxis._x;
        result._data[0][1] = yAxis._x;
        result._data[0][2] = zAxis._x;
        result._data[0][3] = 0.0f;

        result._data[1][0] = xAxis._y;
        result._data[1][1] = yAxis._y;
        result._data[1][2] = zAxis._y;
        result._data[1][3] = 0.0f;

        result._data[2][0] = xAxis._z;
        result._data[2][1] = yAxis._z;
        result._data[2][2] = zAxis._z;
        result._data[2][3] = 0.0f;

        result._data[3][0] = -dot(xAxis, cameraPos);
        result._data[3][1] = -dot(yAxis, cameraPos);
        result._data[3][2] = dot(zAxis, cameraPos);
        result._data[3][3] = 1.0f;

        return result;
    }


    Mat4 perspective(float fovy, float aspect, float zNear, float zFar) {
        float tanHalfFovy = std::tan(radians(fovy) / 2.0f);

        Mat4 result;
        
        result._data[0][0] = 1.0f / (aspect * tanHalfFovy);
        result._data[0][1] = 0.0f;
        result._data[0][2] = 0.0f;
        result._data[0][3] = 0.0f;

        result._data[1][0] = 0.0f;
        result._data[1][1] = 1.0f / tanHalfFovy;
        result._data[1][2] = 0.0f;
        result._data[1][3] = 0.0f;

        result._data[2][0] = 0.0f;
        result._data[2][1] = 0.0f;
        result._data[2][2] = (zFar + zNear) / (zNear - zFar);
        result._data[2][3] = -1.0f;

        result._data[3][0] = 0.0f;
        result._data[3][1] = 0.0f;
        result._data[3][2] = (2.0f * zFar * zNear) / (zNear - zFar);
        result._data[3][3] = 0.0f;

        return result;
    }

}