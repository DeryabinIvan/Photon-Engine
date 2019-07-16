#include "Timer.h"

namespace ph_engine {
	Timer::~Timer(){
		if (duration.count() > 0 && event)
			barrier.set_value();
	}
	void Timer::start(){
		start_point = std::chrono::steady_clock::now();
	}
	double Timer::step(){
		end_point = std::chrono::steady_clock::now();

		std::chrono::duration<double> tmp = end_point - start_point;
		start_point = end_point;

		return tmp.count();
	}
	void Timer::reset(){
		start_point = std::chrono::steady_clock::now();
	}



	void Timer::startMT(){
		if (duration.count() == 0 || !event) return;
		
		barrier_future = barrier.get_future();

		std::thread t([&]() {
			while (barrier_future.wait_for(duration) != std::future_status::ready) {
				event();
			}
		});
		t.detach();
	}
	void Timer::stopMT(){
		//Stop timer thread
		barrier.set_value();
	}
	void Timer::setDuration(int ms){
		duration = std::chrono::milliseconds(ms);
	}
	void Timer::setTimerCallback(timer_event f){
		event = f;
	}
}