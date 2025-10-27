#pragma once

#include <vector>
#include <cstdint> 

namespace core
{
	/*
	* Class with position
	*/
	class Point
	{
	public:
		Point(uint32_t x, uint32_t y);

		[[nodiscard]]
		uint32_t getX() const;

		[[nodiscard]]
		uint32_t getY() const;

		void setX(uint32_t x);

		void setY(uint32_t y);

		bool operator==(const Point& other) const;
		bool operator!=(const Point& other) const;

	private:
		uint32_t _x;
		uint32_t _y;
	};
}