#pragma once

#include "Config.h"

namespace ph_engine {
	class PHOTONENGINE_API System {
		public:
		static double getTime();
		static void setTime(double time);
	};
}
