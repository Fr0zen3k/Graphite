#include "Graphite/Core/grpch.h"

#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_BENCHMARKER_H
#define GRAPHITE_BENCHMARKER_H

#include "Graphite/Core/Core.h"
#include "CsvLogger.h"

namespace Graphite
{
	class GRAPHITE_API Benchmarker
	{
	public:
		Benchmarker();
		virtual ~Benchmarker();

		void Log();

		inline void SetFrameTime(double time) { m_FrameTime = time; }
		inline void SetFPS(double fps) { m_FramesPerSecond = fps; }
		inline void SetAvgDrawCall(double time) { m_AvgDrawCallDuration = time; }
		inline void SetDrawCallCount(int count) { m_DrawCallCount = count; }
		inline void SetVertexCount(uint32_t count) { m_VertexCount = count; }
		inline void SetIndexCount(uint32_t count) { m_IndexCount = count; }
		inline void SetVFC(bool vfc) { m_ViewFrustumCulling = vfc; }
		inline void SetLOD(bool lod) { m_LevelOfDetail = lod; }
		inline void SetGPUBrand(const std::string& name) { m_GPUBrand = name; }
		inline void SetVRAM(int kb) { m_KilobytesVRAM = kb; }
		inline void SetMaxTextureSize(uint32_t size) { m_MaxTextureSize = size; }
		inline void SetMaxPushConstantSize(uint32_t size) { m_MaxPushConstantsSize = size; }
		
	private:
		CsvLogger* m_Logger;

		std::string m_CPUBrand;
		int m_NumOfCores;
		int m_TotalKilobytesRAM;
		
		double m_FrameTime;
		double m_FramesPerSecond;
		double m_AvgDrawCallDuration;
		int m_DrawCallCount;
		uint32_t m_VertexCount;
		uint32_t m_IndexCount;
		bool m_ViewFrustumCulling;
		bool m_LevelOfDetail;
		
		std::string m_GPUBrand;
		int m_KilobytesVRAM;
		uint32_t m_MaxTextureSize;
		uint32_t m_MaxPushConstantsSize;
		
	};
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif