// ==========================================
//  Milestone Final Project
//  Part: 3
//  Student Name  : Jason Shin
//  Student ID    : 111569216
//  Student Email : jwshin3@myseneca.ca
//  Course Section: OOP345-NRB
// ==========================================

#include "Utilities.h"
using namespace std;

namespace sdds {
	char Utilities::m_delimiter{};
	void trim(string& src)
	{
		if (src.length() > 0) {
			int begin = src.find_first_not_of(' ');
			int end = src.find_last_not_of(' ');
			if (begin == -1) src = "";
			else src = src.substr(begin, end - begin + 1);
		}
	}

	void sdds::Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t sdds::Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string sdds::Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		int next_del_index;
		string result;
		if (str[next_pos] == m_delimiter)
		{
			more = false;
			throw - 1;
		}

		else {
			string temp = str.substr(next_pos);
			if ((next_del_index = temp.find_first_of(m_delimiter)) != -1) {
				result = temp.substr(0, next_del_index);
				trim(result);
				next_pos += next_del_index + 1;
				more = true;
			}
			else {
				result = temp;
				trim(result);
				more = false;
			}
		}
		if (m_widthField < result.length())
			setFieldWidth(result.length());

		return result;
	}

	void sdds::Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char sdds::Utilities::getDelimiter()
	{
		return m_delimiter;
	}

}