#pragma once

#include <Features/Characteristic.hpp>

#include <unordered_map>
#include <utility>
#include <cstdint> 

namespace core
{	

	class CharacteristicHandler
	{
	public:
		CharacteristicHandler();
		CharacteristicHandler(std::unordered_map<features::Characteristic, std::pair<int32_t, int32_t>> characteristics);

		/**
		* Getter for characteristic
		* @param type - enum characteristic type
		* @return current characteristic value
		*/
		int32_t getCharacteristic(features::Characteristic type);

		/**
		* Setter for characteristic
		* @param characteristics - Hash table of all unit characteristics
		*/
		void setCharacteristic(std::unordered_map<features::Characteristic, std::pair<int32_t, int32_t>> characteristics);

		/**
		* For changing characteristic
		* @param type - enum characteristic type
		* @param val - positive nums for increase, negative for decrease (ty captain obvious)
		* @return current characteristic value
		*/
		int32_t incrCharacteristic(features::Characteristic type, int32_t val);

	private:
		// Hash table of all unit characteristics. The first is the characteristic type.
		// The second is a pair, where the characteristic value comes first, followed by the maximum characteristic value.
		std::unordered_map<features::Characteristic, std::pair<int32_t, int32_t>> _characteristics;
	};
}
