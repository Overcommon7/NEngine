#include "Precompiled.h"
#include "Matrix4.h"

namespace NEng
{
    Matrix4::Matrix4(const vector<float>& f)
    {
        if (f.size() < 16)
        {
            *this = Matrix4();
            return;
        }
        _11 = f[0];
        _12 = f[1];
        _13 = f[2];
        _14 = f[3];
        _21 = f[4];
        _22 = f[5];
        _23 = f[6];
        _24 = f[7];
        _31 = f[8];
        _32 = f[9];
        _33 = f[10];
        _34 = f[11];
        _41 = f[12];
        _42 = f[13];
        _43 = f[14];
        _44 = f[15];
    }
    Matrix4::Matrix4(const vector<vector<float>>& f)
    {
        if (f.size() < 4 || f[0].size() < 4 || f[1].size() < 4 || f[2].size() < 4 || f[3].size() < 4)
        {
            *this = Matrix4();
            return;
        }
        _11 = f[0][0];
        _12 = f[0][1];
        _13 = f[0][2];
        _14 = f[0][3];
        _21 = f[1][0];
        _22 = f[1][1];
        _23 = f[1][2];
        _24 = f[1][3];
        _31 = f[2][0];
        _32 = f[2][1];
        _33 = f[2][2];
        _34 = f[2][3];
        _41 = f[3][0];
        _42 = f[3][1];
        _43 = f[3][2];
        _44 = f[3][3];
    }
    Matrix4::Matrix4(const std::initializer_list<float> f)
    {
        if (f.size() == 1)
        {
            _11 = *f.begin();
            _12 = *f.begin();
            _13 = *f.begin();
            _14 = *f.begin();
            _21 = *f.begin();
            _22 = *f.begin();
            _23 = *f.begin();
            _24 = *f.begin();
            _31 = *f.begin();
            _32 = *f.begin();
            _33 = *f.begin();
            _34 = *f.begin();
            _41 = *f.begin();
            _42 = *f.begin();
            _43 = *f.begin();
            _44 = *f.begin();
        }
        if (f.size() < 16)
        {
            *this = Matrix4();
            return;
        }
        _11 = *f.begin();
        _12 = *(f.begin() + 1);
        _13 = *(f.begin() + 2);
        _14 = *(f.begin() + 3);
        _21 = *(f.begin() + 4);
        _22 = *(f.begin() + 5);
        _23 = *(f.begin() + 6);
        _24 = *(f.begin() + 7);
        _31 = *(f.begin() + 8);
        _32 = *(f.begin() + 9);
        _33 = *(f.begin() + 10);
        _34 = *(f.begin() + 11);
        _41 = *(f.begin() + 12);
        _42 = *(f.begin() + 13);
        _43 = *(f.begin() + 14);
        _44 = *(f.begin() + 15);
    }
    Matrix4 Matrix4::operator+(const Matrix4& m) const
    {
        Matrix4 result;

        result._11 = this->_11 + m._11;
        result._12 = this->_12 + m._12;
        result._13 = this->_13 + m._13;
        result._14 = this->_14 + m._14;
        result._21 = this->_21 + m._21;
        result._22 = this->_22 + m._22;
        result._23 = this->_23 + m._23;
        result._24 = this->_24 + m._24;
        result._31 = this->_31 + m._31;
        result._32 = this->_32 + m._32;
        result._33 = this->_33 + m._33;
        result._34 = this->_34 + m._34;
        result._41 = this->_41 + m._41;
        result._42 = this->_42 + m._42;
        result._43 = this->_43 + m._43;
        result._44 = this->_44 + m._44;

        return result;
    }

    Matrix4 Matrix4::operator-(const Matrix4& m) const
    {
        Matrix4 result;

        result._11 = this->_11 - m._11;
        result._12 = this->_12 - m._12;
        result._13 = this->_13 - m._13;
        result._14 = this->_14 - m._14;
        result._21 = this->_21 - m._21;
        result._22 = this->_22 - m._22;
        result._23 = this->_23 - m._23;
        result._24 = this->_24 - m._24;
        result._31 = this->_31 - m._31;
        result._32 = this->_32 - m._32;
        result._33 = this->_33 - m._33;
        result._34 = this->_34 - m._34;
        result._41 = this->_41 - m._41;
        result._42 = this->_42 - m._42;
        result._43 = this->_43 - m._43;
        result._44 = this->_44 - m._44;

        return result;
    }

    Matrix4 Matrix4::operator*(const Matrix4& right) const
    {
        Matrix4 result;

        result._11 = this->_11 * right._11 + this->_12 * right._21 + this->_13 * right._31 + this->_14 * right._41;
        result._12 = this->_11 * right._12 + this->_12 * right._22 + this->_13 * right._32 + this->_14 * right._42;
        result._13 = this->_11 * right._13 + this->_12 * right._23 + this->_13 * right._33 + this->_14 * right._43;
        result._14 = this->_11 * right._14 + this->_12 * right._24 + this->_13 * right._34 + this->_14 * right._44;
        result._21 = this->_21 * right._11 + this->_22 * right._21 + this->_23 * right._31 + this->_24 * right._41;
        result._22 = this->_21 * right._12 + this->_22 * right._22 + this->_23 * right._32 + this->_24 * right._42;
        result._23 = this->_21 * right._13 + this->_22 * right._23 + this->_23 * right._33 + this->_24 * right._43;
        result._24 = this->_21 * right._14 + this->_22 * right._24 + this->_23 * right._34 + this->_24 * right._44;
        result._31 = this->_31 * right._11 + this->_32 * right._21 + this->_33 * right._31 + this->_34 * right._41;
        result._32 = this->_31 * right._12 + this->_32 * right._22 + this->_33 * right._32 + this->_34 * right._42;
        result._33 = this->_31 * right._13 + this->_32 * right._23 + this->_33 * right._33 + this->_34 * right._43;
        result._34 = this->_31 * right._14 + this->_32 * right._24 + this->_33 * right._34 + this->_34 * right._44;
        result._41 = this->_41 * right._11 + this->_42 * right._21 + this->_43 * right._31 + this->_44 * right._41;
        result._42 = this->_41 * right._12 + this->_42 * right._22 + this->_43 * right._32 + this->_44 * right._42;
        result._43 = this->_41 * right._13 + this->_42 * right._23 + this->_43 * right._33 + this->_44 * right._43;
        result._44 = this->_41 * right._14 + this->_42 * right._24 + this->_43 * right._34 + this->_44 * right._44;

        return result;
    }

    Matrix4 Matrix4::operator*(const float& f) const
    {
        Matrix4 result = *this;
        for (auto& n : result.v)
            n *= f;
        return result;
    }

    Matrix4& Matrix4::operator+=(const Matrix4& m)
    {
        this->_11 += m._11;
        this->_12 += m._12;
        this->_13 += m._13;
        this->_14 += m._14;
        this->_21 += m._21;
        this->_22 += m._22;
        this->_23 += m._23;
        this->_24 += m._24;
        this->_31 += m._31;
        this->_32 += m._32;
        this->_33 += m._33;
        this->_34 += m._34;
        this->_41 += m._41;
        this->_42 += m._42;
        this->_43 += m._43;
        this->_44 += m._44;

        return *this;
    }

    Matrix4& Matrix4::operator-=(const Matrix4& m)
    {
        this->_11 -= m._11;
        this->_12 -= m._12;
        this->_13 -= m._13;
        this->_14 -= m._14;
        this->_21 -= m._21;
        this->_22 -= m._22;
        this->_23 -= m._23;
        this->_24 -= m._24;
        this->_31 -= m._31;
        this->_32 -= m._32;
        this->_33 -= m._33;
        this->_34 -= m._34;
        this->_41 -= m._41;
        this->_42 -= m._42;
        this->_43 -= m._43;
        this->_44 -= m._44;

        return *this;
    }

    Matrix4& Matrix4::operator*=(const Matrix4& right)
    {
        Matrix4 result;

        result._11 = this->_11 * right._11 + this->_12 * right._21 + this->_13 * right._31 + this->_14 * right._41;
        result._12 = this->_11 * right._12 + this->_12 * right._22 + this->_13 * right._32 + this->_14 * right._42;
        result._13 = this->_11 * right._13 + this->_12 * right._23 + this->_13 * right._33 + this->_14 * right._43;
        result._14 = this->_11 * right._14 + this->_12 * right._24 + this->_13 * right._34 + this->_14 * right._44;
        result._21 = this->_21 * right._11 + this->_22 * right._21 + this->_23 * right._31 + this->_24 * right._41;
        result._22 = this->_21 * right._12 + this->_22 * right._22 + this->_23 * right._32 + this->_24 * right._42;
        result._23 = this->_21 * right._13 + this->_22 * right._23 + this->_23 * right._33 + this->_24 * right._43;
        result._24 = this->_21 * right._14 + this->_22 * right._24 + this->_23 * right._34 + this->_24 * right._44;
        result._31 = this->_31 * right._11 + this->_32 * right._21 + this->_33 * right._31 + this->_34 * right._41;
        result._32 = this->_31 * right._12 + this->_32 * right._22 + this->_33 * right._32 + this->_34 * right._42;
        result._33 = this->_31 * right._13 + this->_32 * right._23 + this->_33 * right._33 + this->_34 * right._43;
        result._34 = this->_31 * right._14 + this->_32 * right._24 + this->_33 * right._34 + this->_34 * right._44;
        result._41 = this->_41 * right._11 + this->_42 * right._21 + this->_43 * right._31 + this->_44 * right._41;
        result._42 = this->_41 * right._12 + this->_42 * right._22 + this->_43 * right._32 + this->_44 * right._42;
        result._43 = this->_41 * right._13 + this->_42 * right._23 + this->_43 * right._33 + this->_44 * right._43;
        result._44 = this->_41 * right._14 + this->_42 * right._24 + this->_43 * right._34 + this->_44 * right._44;

        *this = result;
        return *this;
    }

    Matrix4& Matrix4::operator*=(const float& f)
    {
        for (auto& n : v)
            n *= f;
        return *this;
    }

    bool Matrix4::operator==(const Matrix4& m)
    {
        return
            fabs(_11 - m._11) < 0.001f && fabs(_12 - m._12) < 0.001f && fabs(_13 - m._13) < 0.001f && fabs(_14 - m._14) < 0.001f &&
            fabs(_21 - m._21) < 0.001f && fabs(_22 - m._22) < 0.001f && fabs(_23 - m._23) < 0.001f && fabs(_24 - m._24) < 0.001f &&
            fabs(_31 - m._31) < 0.001f && fabs(_32 - m._32) < 0.001f && fabs(_33 - m._33) < 0.001f && fabs(_34 - m._34) < 0.001f &&
            fabs(_41 - m._41) < 0.001f && fabs(_42 - m._42) < 0.001f && fabs(_43 - m._43) < 0.001f && fabs(_44 - m._44) < 0.001f;
    }


    Matrix4 Matrix4::RotationX(float rad)
    {
        Matrix4 result = Identity;
        float cosres = cosf(rad);
        float sinres = sinf(rad);

        result._22 = cosres;
        result._23 = sinres;
        result._32 = -sinres;
        result._33 = cosres;

        return result;
    }

    Matrix4 Matrix4::RotationY(float rad)
    {
        Matrix4 result = Identity;
        float cosres = cosf(rad);
        float sinres = sinf(rad);

        result._11 = cosres;
        result._13 = -sinres;
        result._31 = sinres;
        result._33 = cosres;

        return result;
    }

    Matrix4 Matrix4::RotationZ(float rad)
    {
        Matrix4 result = Identity;
        float cosres = cosf(rad);
        float sinres = sinf(rad);

        result._11 = cosres;
        result._12 = sinres;
        result._21 = -sinres;
        result._22 = cosres;

        return result;
    }

    Matrix4 Matrix4::RotationAxis(const Vector3& axis, const float& rad)
    {
        const Vector3 u = axis.Normalize();
        const float x = u.x;
        const float y = u.y;
        const float z = u.z;
        const float s = sin(rad);
        const float c = cos(rad);

        return {
            c + (x * x * (1.0f - c)),
            x * y * (1.0f - c) + z * s,
            x * z * (1.0f - c) - y * s,
            0.0f,

            x * y * (1.0f - c) - z * s,
            c + (y * y * (1.0f - c)),
            y * z * (1.0f - c) + x * s,
            0.0f,

            x * z * (1.0f - c) + y * s,
            y * z * (1.0f - c) - x * s,
            c + (z * z * (1.0f - c)),
            0.0f,

            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix4 Matrix4::Scaling(float s)
    {
        return Matrix4({ s, 0.0f, 0.0f, 0.0f,
                        0.0f, s, 0.0f, 0.0f,
                        0.0f, 0.0f, s, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f });
    }

    Matrix4 Matrix4::Scaling(Vector3 s)
    {
        return Matrix4({ s.x, 0.0f, 0.0f, 0.0f,
                        0.0f, s.y, 0.0f, 0.0f,
                        0.0f, 0.0f, s.z, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f });
    }

    Matrix4 Matrix4::Scaling(float sx, float sy, float sz)
    {
        return Matrix4({ sx, 0.0f, 0.0f, 0.0f,
                        0.0f, sy, 0.0f, 0.0f,
                        0.0f, 0.0f, sz, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f });
    }

    Matrix4 Matrix4::Translation(Vector3 d)
    {
        return Matrix4({ 1.0f, 0.0f, 0.0f, 0.f,
                    0.0f, 1.0f, 0.0f, 0.f,
                    0.0f, 0.0f, 1.0f, 0.f,
                    d.x, d.y, d.z, 1.0f });

    }

    Matrix4 Matrix4::Translation(float dx, float dy, float dz)
    {
        return Matrix4({ 1.0f, 0.0f, 0.0f, 0.f,
                    0.0f, 1.0f, 0.0f, 0.f,
                    0.0f, 0.0f, 1.0f, 0.f,
                    dx, dy, dz, 1.0f });

    }

    Vector3 Matrix4::TransformCoord(Vector3 v) const
    {
        const float w = ((v.x * this->_14) + (v.y * this->_24) + (v.z * this->_34) + (1.0f * this->_44));
        const float invW = (w == 0.0f) ? 1.0f : 1 / w;

        return {
            ((v.x * this->_11) + (v.y * this->_21) + (v.z * this->_31) + (1.0f * this->_41)) * invW,
            ((v.x * this->_12) + (v.y * this->_22) + (v.z * this->_32) + (1.0f * this->_42)) * invW,
            ((v.x * this->_13) + (v.y * this->_23) + (v.z * this->_33) + (1.0f * this->_43)) * invW
        };
    }

    Vector3 Matrix4::TransformNormal(Vector3 v) const
    {
        return {
            (v.x * this->_11) + (v.y * this->_21) + (v.z * this->_31),
            (v.x * this->_12) + (v.y * this->_22) + (v.z * this->_32),
            (v.x * this->_13) + (v.y * this->_23) + (v.z * this->_33)
        };

    }

    float Matrix4::Determinant() const
    {
        float det = 0.0f;
        det += (this->_11 * (this->_22 * (this->_33 * this->_44 - (this->_43 * this->_34)) - this->_23 * (this->_32 * this->_44 - (this->_42 * this->_34)) + this->_24 * (this->_32 * this->_43 - (this->_42 * this->_33))));
        det -= (this->_12 * (this->_21 * (this->_33 * this->_44 - (this->_43 * this->_34)) - this->_23 * (this->_31 * this->_44 - (this->_41 * this->_34)) + this->_24 * (this->_31 * this->_43 - (this->_41 * this->_33))));
        det += (this->_13 * (this->_21 * (this->_32 * this->_44 - (this->_42 * this->_34)) - this->_22 * (this->_31 * this->_44 - (this->_41 * this->_34)) + this->_24 * (this->_31 * this->_42 - (this->_41 * this->_32))));
        det -= (this->_14 * (this->_21 * (this->_32 * this->_43 - (this->_42 * this->_33)) - this->_22 * (this->_31 * this->_43 - (this->_41 * this->_33)) + this->_23 * (this->_31 * this->_42 - (this->_41 * this->_32))));
        return det;
    }

    Matrix4 Matrix4::Adjoint() const
    {
        return Matrix4({
            +(this->_22 * ((this->_33 * this->_44) - (this->_43 * this->_34)) - this->_23 * ((this->_32 * this->_44) - (this->_42 * this->_34)) + this->_24 * ((this->_32 * this->_43) - (this->_42 * this->_33))),
            -(this->_12 * ((this->_33 * this->_44) - (this->_43 * this->_34)) - this->_13 * ((this->_32 * this->_44) - (this->_42 * this->_34)) + this->_14 * ((this->_32 * this->_43) - (this->_42 * this->_33))),
            +(this->_12 * ((this->_23 * this->_44) - (this->_43 * this->_24)) - this->_13 * ((this->_22 * this->_44) - (this->_42 * this->_24)) + this->_14 * ((this->_22 * this->_43) - (this->_42 * this->_23))),
            -(this->_12 * ((this->_23 * this->_34) - (this->_33 * this->_24)) - this->_13 * ((this->_22 * this->_34) - (this->_32 * this->_24)) + this->_14 * ((this->_22 * this->_33) - (this->_32 * this->_23))),

            -(this->_21 * ((this->_33 * this->_44) - (this->_43 * this->_34)) - this->_31 * ((this->_23 * this->_44) - (this->_24 * this->_43)) + this->_41 * ((this->_23 * this->_34) - (this->_24 * this->_33))),
            +(this->_11 * ((this->_33 * this->_44) - (this->_43 * this->_34)) - this->_13 * ((this->_31 * this->_44) - (this->_41 * this->_34)) + this->_14 * ((this->_31 * this->_43) - (this->_41 * this->_33))),
            -(this->_11 * ((this->_23 * this->_44) - (this->_43 * this->_24)) - this->_13 * ((this->_21 * this->_44) - (this->_41 * this->_24)) + this->_14 * ((this->_21 * this->_43) - (this->_41 * this->_23))),
            +(this->_11 * ((this->_23 * this->_34) - (this->_33 * this->_24)) - this->_13 * ((this->_21 * this->_34) - (this->_31 * this->_24)) + this->_14 * ((this->_21 * this->_33) - (this->_31 * this->_23))),

            +(this->_21 * ((this->_32 * this->_44) - (this->_42 * this->_34)) - this->_31 * ((this->_22 * this->_44) - (this->_42 * this->_24)) + this->_41 * ((this->_22 * this->_34) - (this->_32 * this->_24))),
            -(this->_11 * ((this->_32 * this->_44) - (this->_42 * this->_34)) - this->_31 * ((this->_12 * this->_44) - (this->_42 * this->_14)) + this->_41 * ((this->_12 * this->_34) - (this->_32 * this->_14))),
            +(this->_11 * ((this->_22 * this->_44) - (this->_42 * this->_24)) - this->_12 * ((this->_21 * this->_44) - (this->_41 * this->_24)) + this->_14 * ((this->_21 * this->_42) - (this->_41 * this->_22))),
            -(this->_11 * ((this->_22 * this->_34) - (this->_32 * this->_24)) - this->_21 * ((this->_12 * this->_34) - (this->_32 * this->_14)) + this->_31 * ((this->_12 * this->_24) - (this->_22 * this->_14))),

            -(this->_21 * ((this->_32 * this->_43) - (this->_42 * this->_33)) - this->_31 * ((this->_22 * this->_43) - (this->_42 * this->_23)) + this->_41 * ((this->_22 * this->_33) - (this->_32 * this->_23))),
            +(this->_11 * ((this->_32 * this->_43) - (this->_42 * this->_33)) - this->_12 * ((this->_31 * this->_43) - (this->_41 * this->_33)) + this->_13 * ((this->_31 * this->_42) - (this->_41 * this->_32))),
            -(this->_11 * ((this->_22 * this->_43) - (this->_42 * this->_23)) - this->_12 * ((this->_21 * this->_43) - (this->_41 * this->_23)) + this->_13 * ((this->_21 * this->_42) - (this->_41 * this->_22))),
            +(this->_11 * ((this->_22 * this->_33) - (this->_32 * this->_23)) - this->_12 * ((this->_21 * this->_33) - (this->_31 * this->_23)) + this->_13 * ((this->_21 * this->_32) - (this->_31 * this->_22)))
            });
    }

    Matrix4 Matrix4::Transpose() const
    {
        Matrix4 result;

        result._11 = this->_11;
        result._12 = this->_21;
        result._13 = this->_31;
        result._14 = this->_41;
        result._21 = this->_12;
        result._22 = this->_22;
        result._23 = this->_32;
        result._24 = this->_42;
        result._31 = this->_13;
        result._32 = this->_23;
        result._33 = this->_33;
        result._34 = this->_43;
        result._41 = this->_14;
        result._42 = this->_24;
        result._43 = this->_34;
        result._44 = this->_44;

        return result;
    }

    Matrix4 Matrix4::Inverse() const
    {
        return Adjoint() * (1.0f / Determinant());
    }
}