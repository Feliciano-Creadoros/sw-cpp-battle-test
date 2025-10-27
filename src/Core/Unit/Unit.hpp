#pragma once

#include <IO/System/EventLog.hpp>

#include <Core/Interfaces/IAction.hpp>
#include <Core/Unit/CharacteristicHandler.hpp>
#include <memory>
#include <string>

namespace core
{
	class UnitHandler;
	class IAction;
	/**
	* Basic unit class
	*/
	class Unit
	{
	public:
		Unit(uint32_t id, uint32_t x, uint32_t y, bool occupyStatus, std::string name);

		virtual ~Unit() {}

		/**
		* In this method, actions assigned to the unit are attempted sequentially.
		* @param map - the battle map interface, through which we can access the locations of units on the map.
        * @param unitHandler - Unit Handler.
		* @param tick - Current simulation tick.
		* @param eventLog - Logger.
		* @return Success of completed actions. false - no action was completed due to non-compliance with the conditions for these actions. 
		* true - one of the actions was performed.
		*/
		virtual bool doAction(
			std::shared_ptr<IMap>& map,
			std::shared_ptr<UnitHandler> unitHandler,
			uint64_t tick,
			std::shared_ptr<sw::EventLog> eventLog);

		/**
		* In this method, death actions assigned to the unit are attempted.
		* @param map - the battle map interface, through which we can access the locations of units on the map.
        * @param unitHandler - Unit Handler.
		* @param tick - Current simulation tick.
		* @param eventLog - Logger.
		* @return Success of completed death actions. false - no action was completed due to non-compliance with the conditions for these actions. 
		* true - one of the death actions was performed.
		*/
		virtual bool deathAction(
			std::shared_ptr<IMap>& map,
			std::shared_ptr<UnitHandler> unitHandler,
			uint64_t tick,
			std::shared_ptr<sw::EventLog> eventLog);

		/**
		* Getter for id
		* @return current id 
		*/
		[[nodiscard]]
		uint32_t getId() const;

		/**
		* Getter for name
		* @return name 
		*/
		[[nodiscard]]
		std::string getName() const;

		/**
		* Getter for coordinates
		* @return current coordinates
		*/
		[[nodiscard]]
		Point getCoordinates() const;

		/**
		* Setter for coordinates
		* @param point - new coordinates value
		*/
		void setCoordinates(const Point& point);

		/**
		* Getter for target coordinates
		* @return current coordinates
		*/
		[[nodiscard]]
		Point getTargetCoordinates() const;

		/**
		* Setter for target coordinates
		* @param point - new coordinates value
		*/
		void setTargetCoordinates(const Point& point);


		/**
		* Getter for occupy status
		* @return true - occupy cell; false - not
		*/
		bool geOccupyStatus() const;

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
		void setCharacteristic(
			std::unordered_map<features::Characteristic, std::pair<int32_t, int32_t>> characteristics);

		/**
		* For changing characteristic
		* @param type - enum characteristic type
		* @param val - positive nums for increase, negative for decrease (ty captain obvious)
		* @return current characteristic value
		*/
		int32_t incrCharacteristic(features::Characteristic type, int32_t val);


	protected:
		// Unit action list. Such as movement, melee attack, shooting, hooking other units, etc.
		std::vector<std::unique_ptr<IAction>> _actions;
		// Unit death action. Runs after all actions are completed.
		std::unique_ptr<IAction> _death_action;
		// Unit id
		uint32_t _id;
		// Unit id
		std::string _name;
		// Unit target position
		Point _targetPoint;
		// Unit position
		Point _point;
		// Status indicating whether the unit occupies the cell or not
		bool _occupyStatus;
		// This handler is responsible for all the unit's characteristics
		std::unique_ptr<CharacteristicHandler> _characteristicsHandler;
	};
}