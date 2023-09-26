// ==========================================
//  Milestone Final Project
//  Part: 3
//  Student Name  : Jason Shin
//  Student ID    : 111569216
//  Student Email : jwshin3@myseneca.ca
//  Course Section: OOP345-NRB
// ==========================================

#include "Workstation.h"

using namespace std;
namespace sdds {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	Workstation::Workstation(const std::string& str) : Station(str)
	{
	}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool result = false;
		if (!m_orders.empty()) {
			result = true;
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				if (m_pNextStation)
					(*m_pNextStation) += move(m_orders.front());

				else if (m_orders.front().isOrderFilled())
					g_completed.push_back(move(m_orders.front()));

				else
					g_incomplete.push_back(move(m_orders.front()));

				m_orders.pop_front();
			}
			else result = false;

		}
		return result;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		if (station) m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> " << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line") << endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));

		return *this;
	}

}

