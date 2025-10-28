
#include <Core/Unit/CharacteristicHandler.hpp>

#include <algorithm>

namespace core
{
	CharacteristicHandler::CharacteristicHandler() :
			_characteristics(std::unordered_map<features::Characteristic, std::pair<int32_t, int32_t>>())
	{}

	 CharacteristicHandler::CharacteristicHandler(
		std::unordered_map<features::Characteristic, std::pair<int32_t, int32_t>> characteristics) :
			_characteristics(characteristics)
	{}


	int32_t CharacteristicHandler::getCharacteristic(features::Characteristic type)
	{
		auto it = _characteristics.find(type);
		if (it == _characteristics.end())
		{
			return 0;
		}
		return it->second.first;
	}

	void CharacteristicHandler::setCharacteristics(
		std::unordered_map<features::Characteristic, std::pair<int32_t, int32_t>> characteristics) 
	{
		_characteristics = characteristics;
	}

	int32_t CharacteristicHandler::incrCharacteristic(features::Characteristic type, int32_t val)
	{
		auto it = _characteristics.find(type);
		if (it == _characteristics.end())
		{
			return 0;
		}
		it->second.first += val;

		// Check that the characteristic value (second.first) does not exceed the maximum value (second.second)
		if (it->second.first > it->second.second)
		{
			it->second.first = it->second.second;
		}
		return it->second.first;
	}
}
