#pragma once
#include "pch.h"
#include "sdk/unity.h"

namespace Features {
	namespace ESP {
		void Initialize();
		void Render();
		void Shutdown();

		// Drawing helpers
		void DrawBox(const Unity::Vector3& worldPos, const Unity::Vector3& screenPos, const Unity::Color& color);
		void DrawLine(const Unity::Vector2& from, const Unity::Vector2& to, const Unity::Color& color);
		void DrawText(const Unity::Vector2& pos, const std::string& text, const Unity::Color& color);
		bool WorldToScreen(const Unity::Vector3& world, Unity::Vector2& screen);
	}
}
