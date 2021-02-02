﻿#pragma once
#include "AllocatorBase.h"

namespace sakura
{
	class RuntimeCoreAPI linear_allocator : public allocator {
	protected:
		void* m_start_ptr = nullptr;
		std::size_t m_offset = 0;
	public:
		linear_allocator(const std::size_t totalSize);
		linear_allocator(const linear_allocator& linear_allocator);

		virtual ~linear_allocator() override;

		virtual void* allocate(
			const std::size_t size, const std::size_t alignment = 0) override;

		virtual void free(void* ptr) override;

		virtual void init() override;

		virtual void reset();
		linear_allocator(linear_allocator&&) = default;

	private:
		linear_allocator(linear_allocator& linear_allocator);
		linear_allocator() = default;
	};

}