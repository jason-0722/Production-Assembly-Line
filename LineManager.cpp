// ==========================================
//  Milestone Final Project
//  Part: 3
//  Student Name  : Jason Shin
//  Student ID    : 111569216
//  Student Email : jwshin3@myseneca.ca
//  Course Section: OOP345-NRB
// ==========================================

#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		ifstream is(file);
		string temp;
		string itemname;
		string from;
		string to;
		size_t pos = 0;
		bool more = true;
		Utilities util;
		Utilities::setDelimiter('|');
		vector<Workstation*> remainfirst;
		while (!is.eof()) {			
			getline(is, temp);
			pos = 0;
			more = true;
			itemname = util.extractToken(temp, pos, more);
			Workstation* wp;
			wp = *(find_if(stations.begin(), stations.end(), [&](Workstation* sp) {
				return sp->getItemName() == itemname;
				}));
			m_activeLine.push_back(wp);
			remainfirst.push_back(wp);
		}
		is.seekg(ios::beg);
		while (!is.eof()) {
			getline(is, temp);
			pos = 0;
			more = true;
			from = util.extractToken(temp, pos, more);
			if (more) {
				Workstation* fromWp, * toWp;
				to = util.extractToken(temp, pos, more);
				toWp = *(find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* wp) {
					return wp->getItemName() == to;
				}));
				remove(remainfirst.begin(), remainfirst.end(), toWp);
				fromWp = *(find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* wp) {
					return wp->getItemName() == from;
					}
				));
				fromWp->setNextStation(toWp);
			}
		}
		m_cntCustomerOrder = g_pending.size();
		m_firstStation = remainfirst.front();
	}
	void LineManager::reorderStations()
	{
		std::vector<Workstation*> tempLine;
		Workstation* tp;
		tempLine.push_back(m_firstStation);
		while ((tp = tempLine.back()->getNextStation())) {
			tempLine.push_back(tp);
		}
		m_activeLine.clear();
		m_activeLine = tempLine;
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t count{}; //0
		count++;
		os << "Line Manager Iteration: " << count << endl;
		if (!g_pending.empty()) {
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
		}

		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->fill(os);
			});
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->attemptToMoveOrder();
			});	
		
		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
	}
	void LineManager::display(std::ostream& os) const
	{
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->display(os);
			});
	}
}