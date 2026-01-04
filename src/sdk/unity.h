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
}
