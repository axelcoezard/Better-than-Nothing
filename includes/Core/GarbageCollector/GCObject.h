/*
 * File: GCObject.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Thursday, 9th March 2023 9:36:01 am
 * Last Modified: Thursday, 9th March 2023 9:36:08 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <cstdio>
#include <cstdlib>
#include <new>

struct GCObject {
	protected:
		size_t	m_size;
		bool	m_marked;
	public:
		GCObject(void);

		void SetMarked(bool marked);
		bool IsMarked(void);

		size_t GetSize(void);

		void* operator new(size_t size);
		void operator delete(void* ptr);
};
