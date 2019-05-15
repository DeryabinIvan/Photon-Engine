#pragma once

#include "Config.h"

namespace ph_engine {
	class NonCopyable {
		protected:
			NonCopyable()  {}
			~NonCopyable() {}

		private:
			NonCopyable(const NonCopyable&);
			NonCopyable& operator=(const NonCopyable&);
	};
}