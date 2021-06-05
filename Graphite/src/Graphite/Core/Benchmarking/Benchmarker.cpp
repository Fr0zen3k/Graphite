#include "Graphite/Core/grpch.h"
#include "Benchmarker.h"

#include "Graphite/Core/Application.h"

namespace Graphite
{

	Benchmarker::Benchmarker()
	{
		std::vector<std::string> collumns = {"CPU", "Cores", "RAM (KB)", "Frame Time", 
											"FPS", "Draw Call Length", "Draw Call Count",
											"Vertex Count", "Index Count", "View-Frustum Culling",
											"LOD", "GPU", "VRAM (KB)", "Max Texture Size", "Max Push Constant Size"};

		m_Logger = new CsvLogger(Application::GetAppDir() + "Benchmark\\log.csv", collumns, ',');

		// Get CPU info
		int CPUInfo[4] = { -1 };
		unsigned nExIds, i = 0;
		char CPUBrand[0x40];

		__cpuid(CPUInfo, 0x80000000);
		nExIds = CPUInfo[0];

		for(i = 0x80000000; i <= nExIds; i++)
		{
			__cpuid(CPUInfo, i);

			if(i == 0x80000002)
			{
				memcpy(CPUBrand, CPUInfo, sizeof(CPUInfo));
			}
			else if(i == 0x80000003)
			{
				memcpy(CPUBrand + 16, CPUInfo, sizeof(CPUInfo));
			}
			else if(i == 0x80000004)
			{
				memcpy(CPUBrand + 32, CPUInfo, sizeof(CPUInfo));
			}
		}

		m_CPUBrand = std::string(CPUBrand);

		SYSTEM_INFO info;
		GetSystemInfo(&info);
		m_NumOfCores = info.dwNumberOfProcessors;


		// Get memory info
		MEMORYSTATUSEX mem;
		mem.dwLength = sizeof mem;
		GlobalMemoryStatusEx(&mem);
		m_TotalKilobytesRAM = mem.ullTotalPhys / 1024;
	}

	Benchmarker::~Benchmarker()
	{
		delete m_Logger;
	}

	void Benchmarker::Log()
	{
		std::vector<std::string> data;

		std::stringstream ss;

		ss << m_CPUBrand;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_NumOfCores;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_TotalKilobytesRAM;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_FrameTime;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_FramesPerSecond;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_AvgDrawCallDuration;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_DrawCallCount;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_VertexCount;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_IndexCount;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_ViewFrustumCulling;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_LevelOfDetail;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_GPUBrand;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_KilobytesVRAM;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_MaxTextureSize;
		data.emplace_back(ss.str());
		ss.str("");

		ss << m_MaxPushConstantsSize;
		data.emplace_back(ss.str());
		ss.str("");

		m_Logger->AddDataRow(data);
	}

}