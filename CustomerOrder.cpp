// ==========================================
//  Milestone Final Project
//  Part: 3
//  Student Name  : Jason Shin
//  Student ID    : 111569216
//  Student Email : jwshin3@myseneca.ca
//  Course Section: OOP345-NRB
// ==========================================

#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder()
	{
	}

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		size_t pos = 0;
		bool more = true;
		Utilities util;

		m_name = util.extractToken(str, pos, more);
		m_product = util.extractToken(str, pos, more);
		vector<Item*> tempVec;
		Item* tempItem;
		while (more) {
			tempItem = new Item(util.extractToken(str, pos, more));
			tempVec.push_back(tempItem);	
		}
		m_cntItem = tempVec.size();
		m_lstItem = new Item* [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = tempVec[i];
		}
		if (util.getFieldWidth() > m_widthField) {
			m_widthField = util.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& I)
	{
		throw - 1;
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& I) noexcept
	{
		*this = move(I);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		if (this != &other) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;
			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
			other.m_name = "";
			other.m_product = "";
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		bool result = true;
		for (size_t i = 0; i < m_cntItem && result; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				result = false;
			}
		}
		return result;

	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool result = true;
		for (size_t i = 0; i < m_cntItem && result; i++) {
			if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false){
				result = false;
			}
		}
		return result;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool isDone = false;
		for (size_t i = 0; i < m_cntItem && !isDone; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !(m_lstItem[i]->m_isFilled)) {
				if (station.getQuantity() >= 1) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]"<<endl;
					isDone = true;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]"<<endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os  << "[" << setw(6) << setfill('0')<<right << m_lstItem[i]->m_serialNumber << "] "<<left<<setw(m_widthField+2)<<setfill(' ') << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}
}