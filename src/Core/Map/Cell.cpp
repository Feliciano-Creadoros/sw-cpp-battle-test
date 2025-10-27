
#include <Core/Map/Cell.hpp>

#include <algorithm>

namespace core
{

	Cell::Cell() :
			_emptyStatus(true),
			_unitIds(std::vector<uint32_t>())
	{}
	bool Cell::getEmptyStatus() const
	{
		return _emptyStatus;
	}

	void Cell::setEmptyStatus(bool emptyStatus)
	{
		_emptyStatus = emptyStatus;
	}

	std::vector<uint32_t> Cell::getUnitIds() const
	{
		return _unitIds;
	}

	bool Cell::checkUnitId(uint32_t unitId) const
	{
		if (std::find(_unitIds.begin(), _unitIds.end(), unitId) != _unitIds.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Cell::appendUnitId(uint32_t unitId)
	{
		_unitIds.push_back(unitId);
	}

	void Cell::deleteUnitId(uint32_t unitId)
	{
		_unitIds.erase(std::remove(_unitIds.begin(), _unitIds.end(), unitId), _unitIds.end());
	}

}
