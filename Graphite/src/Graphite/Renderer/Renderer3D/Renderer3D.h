#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../RendererCore/GraphicsContext.h"

namespace Graphite
{
	struct GRAPHITE_API RendererSettings
	{
		bool LOD = true;
		bool culling = true;
	};
	
	class GRAPHITE_API Renderer3D
	{
	public:
		static void Init();
		static void InitAPI();
		static void OnTick();
		static void Shutdown();

		static void UpdateSettings(RendererSettings settings);

		inline static RendererSettings GetSettings() { return s_Settings; }
		inline static void SetCulling(bool culling) { s_Settings.culling = culling; }
		inline static bool GetCulling() { return s_Settings.culling; }
		inline static bool GetLOD() { return s_Settings.LOD; }

		static GraphicsContext* GetGraphicsContext();

	private:
		static GraphicsContext* s_GraphicsContext;

		static RendererSettings s_Settings;
	};
}


#if defined (_MSC_VER)
#pragma warning(pop)
#endif