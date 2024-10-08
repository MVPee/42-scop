# include "../../includes/math/Math.hpp"

namespace ft_math {

    /* VEC3 */
    vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3::vec3(float nbr) : x(nbr), y(nbr), z(nbr) {}
    vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    vec3::vec3(const vec3 &vec3) : x(vec3.x), y(vec3.y), z(vec3.z) {}
    vec3 &vec3::operator=(const vec3 &vec3) {
        if (this != &vec3) {
            x = vec3.x;
            y = vec3.y;
            z = vec3.z;
        }
        return *this;
    }
    vec3 vec3::operator-(const vec3 &v) const { return vec3(x - v.x, y - v.y, z - v.z); }
    vec3 vec3::operator+(const vec3 &v) const { return vec3(x + v.x, y + v.y, z + v.z); }
    vec3 vec3::operator*(float scalar) const { return vec3(x * scalar, y * scalar, z * scalar); }
    vec3 &vec3::operator+=(const vec3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    vec3 &vec3::operator-=(const vec3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    /* MAT4 */
    mat4::mat4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                _data[i][j] = (i == j) ? 1.0f : 0.0f;
    }
    mat4::mat4(float data[4][4]) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                _data[i][j] = data[i][j];
    }
    mat4 mat4::operator*(const mat4 &mat) const {
        mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result._data[i][j] = 0;
                for (int k = 0; k < 4; ++k)
                    result._data[i][j] += _data[i][k] * mat._data[k][j];
            }
        }
        return result;
    }
    float* mat4::value_ptr() {
        return &(_data[0][0]);
    }



    float radians (float degrees) {
        return degrees * 0.01745329251994329576923690768489f;
    }

    vec3 normalize(const vec3 &v) {
        float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length == 0)
            return vec3(0.0f, 0.0f, 0.0f);
        return vec3(v.x / length, v.y / length, v.z / length);
    }

    vec3 cross(const vec3 &vec1, const vec3 &vec2) {
        return vec3(
            vec1.y * vec2.z - vec1.z * vec2.y,
            vec1.z * vec2.x - vec1.x * vec2.z,
            vec1.x * vec2.y - vec1.y * vec2.x
        );
    }

    float dot(const vec3 &vec1, const vec3 &vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }
    
    mat4 lookAt(const vec3 &cameraPos, const vec3 &target, const vec3 &up) {
        vec3 zAxis = normalize(target - cameraPos);
        vec3 xAxis = normalize(cross(up, zAxis));
        vec3 yAxis = cross(zAxis, xAxis);

        mat4 result;
        
        result._data[0][0] = xAxis.x;
        result._data[0][1] = yAxis.x;
        result._data[0][2] = zAxis.x;
        result._data[0][3] = 0.0f;

        result._data[1][0] = xAxis.y;
        result._data[1][1] = yAxis.y;
        result._data[1][2] = zAxis.y;
        result._data[1][3] = 0.0f;

        result._data[2][0] = xAxis.z;
        result._data[2][1] = yAxis.z;
        result._data[2][2] = zAxis.z;
        result._data[2][3] = 0.0f;

        result._data[3][0] = -dot(xAxis, cameraPos);
        result._data[3][1] = -dot(yAxis, cameraPos);
        result._data[3][2] = dot(zAxis, cameraPos);
        result._data[3][3] = 1.0f;

        return result;
    }


    mat4 perspective(float fovy, float aspect, float zNear, float zFar) {
        float tanHalfFovy = std::tan(radians(fovy) / 2.0f);

        mat4 result;
        
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