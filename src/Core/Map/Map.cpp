#include <Core/Map/Map.hpp>

#include <stdexcept>
#include <string>
#include <algorithm>

namespace core
{

	Map::Map(uint32_t width, uint32_t height) :
			_width(width),
			_height(height),
			_cells(std::vector<std::vector<Cell>>(width, std::vector<Cell>(height)))
	{}

	void Map::checkPosition(const Point& point) const
	{
		if (point.getX() >= _width || point.getX() < 0 || point.getY() >= _height || point.getY() < 0)
		{
			throw std::out_of_range(
				"ERR: The position " + std::to_string(point.getX()) + ", " + std::to_string(point.getY())
				+ " is outside the field of " + std::to_string(_width) + "x" + std::to_string(_height) + " size!");
		}
	}

	std::vector<uint32_t> Map::getUnitsInZone(
		const Point& point, int32_t innerRadius, int32_t outerRadius) const
	{
		checkPosition(point);
		std::vector<uint32_t> ids;

		int32_t cX = point.getX();
		int32_t cY = point.getY();


		int32_t r2min = innerRadius * innerRadius;
		int32_t r2max = outerRadius * outerRadius;

		int32_t x0 = std::max(0, cX - outerRadius);
		int32_t x1 = std::min((int32_t)_height - 1, cX + outerRadius);
		int32_t y0 = std::max(0, cY - outerRadius);
		int32_t y1 = std::min((int32_t)_width - 1, cY + outerRadius);

		for (int x = x0; x <= x1; ++x)
		{
			int32_t dX = x - cX;

			for (int y = y0; y <= y1; ++y)
			{
				int32_t dY = y - cY;
				int32_t d2 = dY * dY + dX * dX;
				if (d2 <= r2max && d2 > r2min)
				{
					std::vector<uint32_t> currCellIds = _cells[x][y].getUnitIds();
					ids.insert(std::end(ids), std::begin(currCellIds), std::end(currCellIds));
				}
			}
		}

		return ids;
	}

	bool Map::isCellEmpty(const Point& point) const
	{
		checkPosition(point);

		return _cells[point.getX()][point.getY()].getEmptyStatus();
	}

	void Map::removeFromCell(const Point& point, uint32_t unitId, bool isOccupiable)
	{
		checkPosition(point);
		if (isOccupiable)
		{
			_cells[point.getX()][point.getY()].setEmptyStatus(true);
		}
		_cells[point.getX()][point.getY()].deleteUnitId(unitId);
	}

	void Map::setToCell(const Point& point, uint32_t unitId, bool isOccupiable)
	{
		checkPosition(point);
		if (isOccupiable)
		{
			_cells[point.getX()][point.getY()].setEmptyStatus(false);
		}
		_cells[point.getX()][point.getY()].appendUnitId(unitId);
	}

	uint32_t Map::getWidth() const
	{
		return _width;
	}

	uint32_t Map::getHeight() const
	{
		return _height;
	}

}