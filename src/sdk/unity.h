#pragma once
#include "pch.h"

namespace Unity {
	struct Vector3 {
		float x, y, z;

		Vector3() : x(0), y(0), z(0) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		float Distance(const Vector3& other) const {
			float dx = x - other.x;
			float dy = y - other.y;
			float dz = z - other.z;
			return sqrtf(dx * dx + dy * dy + dz * dz);
		}

		Vector3 operator-(const Vector3& other) const {
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
	};

	struct Quaternion {
		float x, y, z, w;
	};

	struct Matrix4x4 {
		float m[4][4];
	};

	struct Color {
		float r, g, b, a;

		Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
	};

	struct Rect {
		float x, y, width, height;
	};

	// IL2CPP runtime structures
	struct Il2CppObject {
		void* klass;
		void* monitor;
	};

	struct Il2CppString {
		Il2CppObject object;
		int32_t length;
		wchar_t chars[1];

		std::string ToString() const {
			std::wstring ws(chars, length);
			return std::string(ws.begin(), ws.end());
		}
	};

	template<typename T>
	struct Il2CppArray {
		Il2CppObject object;
		void* bounds;
		uintptr_t max_length;
		T items[1];

		T* begin() { return items; }
		T* end() { return items + max_length; }
		size_t size() const { return max_length; }
	};

	// Quaternion/Euler conversion helpers
	inline Quaternion EulerToQuaternion(float pitch, float yaw, float roll) {
		float cy = cosf(yaw * 0.5f * 3.14159f / 180.0f);
		float sy = sinf(yaw * 0.5f * 3.14159f / 180.0f);
		float cp = cosf(pitch * 0.5f * 3.14159f / 180.0f);
		float sp = sinf(pitch * 0.5f * 3.14159f / 180.0f);
		float cr = cosf(roll * 0.5f * 3.14159f / 180.0f);
		float sr = sinf(roll * 0.5f * 3.14159f / 180.0f);

		Quaternion q;
		q.w = cr * cp * cy + sr * sp * sy;
		q.x = sr * cp * cy - cr * sp * sy;
		q.y = cr * sp * cy + sr * cp * sy;
		q.z = cr * cp * sy - sr * sp * cy;
		return q;
	}

	inline Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t) {
		float dot = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

		if (dot < 0.0f) {
			dot = -dot;
		}

		if (dot > 0.9995f) {
			// Linear interpolation for very close quaternions
			Quaternion result;
			result.x = a.x + t * (b.x - a.x);
			result.y = a.y + t * (b.y - a.y);
			result.z = a.z + t * (b.z - a.z);
			result.w = a.w + t * (b.w - a.w);

			float len = sqrtf(result.x * result.x + result.y * result.y + result.z * result.z + result.w * result.w);
			result.x /= len;
			result.y /= len;
			result.z /= len;
			result.w /= len;
			return result;
		}

		float theta = acosf(dot);
		float sinTheta = sinf(theta);
		float wa = sinf((1.0f - t) * theta) / sinTheta;
		float wb = sinf(t * theta) / sinTheta;

		Quaternion result;
		result.x = wa * a.x + wb * b.x;
		result.y = wa * a.y + wb * b.y;
		result.z = wa * a.z + wb * b.z;
		result.w = wa * a.w + wb * b.w;
		return result;
	}
}
