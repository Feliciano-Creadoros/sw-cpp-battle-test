
#include <Core/Map/Point.hpp>

#include <algorithm>

namespace core
{
	Point::Point(uint32_t x, uint32_t y) : _x(x), _y(y)
	{}

	uint32_t Point::getX() const
	{
		return _x;
	}

	uint32_t Point::getY() const
	{
		return _y;
	}

	void Point::setX(uint32_t x) {
		_x = x;
	}

	void Point::setY(uint32_t y) {
		_y = y;
	}

	bool Point::operator==(const Point& other) const
	{
		return ((_x == other.getX()) && (_y == other.getY()));
	}

	bool Point::operator!=(const Point& other) const
	{
		return !(*this == other);
	}
}
