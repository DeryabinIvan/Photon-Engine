#pragma once

#include "Config.h"

#include <chrono>
#include <thread>
#include <future>

namespace ph_engine {
	class PHOTONENGINE_API Timer{
		std::chrono::time_point<std::chrono::steady_clock> start_point, end_point;
		std::chrono::duration<double> duration = std::chrono::seconds(0);
		bool stopped = false;

		public:
			~Timer();

			void start();
			double step();
			void reset();
			
			typedef void(*timer_event)(void);

			//Counting in another thread
			void startMT();
			void stopMT();
			void setDuration(int ms);
			void setTimerCallback(timer_event f);
		private:
			timer_event event = nullptr;
			std::promise<void> barrier;
			std::future<void> barrier_future;
	};
}
