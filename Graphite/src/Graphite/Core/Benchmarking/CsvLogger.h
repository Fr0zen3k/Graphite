#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_CSVLOGGER_H
#define GRAPHITE_CSVLOGGER_H

namespace Graphite
{
	class GRAPHITE_API CsvLogger
	{
	public:
		CsvLogger(const std::string& path, std::vector<std::string>& rows, const char& delimiter = ',');
		virtual ~CsvLogger();

		void AddDataRow(std::vector<std::string>& row);
		void QueueData(std::string data);

		void Flush();
	private:
		const std::string& m_FilePath;
		std::vector<std::string> m_RowNames;
		std::vector<std::string> m_DataQueue;
		std::ofstream m_FileStream;
		char m_Delimiter;
		uint32_t m_QueuePos = 0;
	};
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif