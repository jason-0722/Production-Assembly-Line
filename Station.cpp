// ==========================================
//  Milestone Final Project
//  Part: 3
//  Student Name  : Jason Shin
//  Student ID    : 111569216
//  Student Email : jwshin3@myseneca.ca
//  Course Section: OOP345-NRB
// ==========================================

#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;

namespace sdds {
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	Station::Station(const std::string& str)
	{
		size_t pos = 0;
		bool more = true;
		Utilities util;
		m_stationId = ++id_generator;

		m_itemName = util.extractToken(str, pos, more);
		m_nextSerialNum = stoi(util.extractToken(str, pos, more));
		m_numOfItems = stoi(util.extractToken(str, pos, more));
		if (util.getFieldWidth() > Station::m_widthField) {
			Station::m_widthField = util.getFieldWidth();
		}
		m_desc = util.extractToken(str, pos, more);
	}

	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_nextSerialNum++;
	}
	size_t Station::getQuantity() const
	{
		return m_numOfItems;
	}
	void Station::updateQuantity()
	{
		if (m_numOfItems >= 1)
			m_numOfItems--;
	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << setw(3) << setfill('0') << right << m_stationId
			<< " | " << setw(m_widthField + 1) << setfill(' ') << left << m_itemName
			<< " | " << setw(6) << right << setfill('0') << m_nextSerialNum << " | ";
		if (full) {
			os << setw(4) << setfill(' ') << m_numOfItems << " | " << m_desc;
		}
		os << endl;
	}
}