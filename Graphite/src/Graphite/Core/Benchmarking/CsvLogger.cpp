#include "Graphite/Core/grpch.h"
#include "CsvLogger.h"

namespace Graphite
{
	CsvLogger::CsvLogger(const std::string& path, std::vector<std::string>& rows, const char& delimiter) : m_FilePath(path), m_RowNames(std::vector<std::string>(rows)), m_Delimiter(delimiter)
	{
		m_FileStream.open(m_FilePath);

		if(!m_FileStream.is_open())
		{
			throw std::runtime_error("Failed to open a csv benchmarking file!");
		}

		for(int i = 0; i < m_RowNames.size(); i++)
		{
			if(i != 0)
			{
				m_FileStream << m_Delimiter;
			}

			m_FileStream << m_RowNames[i];
		}

		m_FileStream << std::endl;
	}

	CsvLogger::~CsvLogger()
	{
		m_FileStream.close();
	}

	void CsvLogger::AddDataRow(std::vector<std::string>& row)
	{
		if(m_QueuePos != 0)
		{
			throw std::runtime_error("Cannot add a row to cvs when the previous one isn't finished!");
		}

		for(int i = 0; i < row.size(); i++)
		{
			if(i != 0)
			{
				m_FileStream << m_Delimiter;
			}

			m_FileStream << row[i];
		}

		m_FileStream << std::endl;
	}

	void CsvLogger::Flush()
	{
		for(int i = 0; i < m_DataQueue.size(); i++)
		{
			if(m_QueuePos != 0)
			{
				m_FileStream << m_Delimiter;
			}

			m_FileStream << m_DataQueue[i];

			m_QueuePos++;
			m_QueuePos %= m_RowNames.size();

			if(m_QueuePos == 0)
			{
				m_FileStream << std::endl;
			}
		}

		m_DataQueue.resize(0);
	}

	void CsvLogger::QueueData(std::string data)
	{
		m_DataQueue.emplace_back(data);
	}

}