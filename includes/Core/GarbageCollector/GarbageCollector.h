/*
 * File: GarbageCollector.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Thursday, 9th March 2023 9:35:55 am
 * Last Modified: Thursday, 9th March 2023 9:36:32 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <set>
#include "Core/GarbageCollector/GCObject.h"

struct GarbageCollector {
	private:
		static GarbageCollector* m_instance;

		std::set<GCObject*> m_objects;
	public:
		void AddObject(GCObject* object);
		void RemoveObject(GCObject* object);

		void Collect(void);

		static GarbageCollector* Get(void);
		static void Destroy(void);
};
