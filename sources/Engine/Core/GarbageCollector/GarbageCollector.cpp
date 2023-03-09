/*
 * File: GarbageCollector.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Thursday, 9th March 2023 9:51:11 am
 * Last Modified: Thursday, 9th March 2023 9:51:21 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <iostream>

#include "Core/GarbageCollector/GarbageCollector.h"
#include "Core/GarbageCollector/GCObject.h"

GarbageCollector* GarbageCollector::m_instance = nullptr;

void GarbageCollector::AddObject(GCObject* object) {
	m_objects.insert(object);
}

void GarbageCollector::RemoveObject(GCObject* object) {
	m_objects.erase(object);
}

void GarbageCollector::Collect(bool verbose) {
	std::set<GCObject*>::iterator current = m_objects.begin();
	std::set<GCObject*>::iterator end = m_objects.end();

	unsigned int freedCount = 0;
	unsigned int freedSize = 0;
	while (current != end) {
		GCObject* object = *current;

		if (object->IsMarked()) {
			object->SetMarked(false);
		} else {
			freedCount++;
			freedSize += object->GetSize();
			this->RemoveObject(object);
			delete object;
		}
		current++;
	}

	if (verbose) {
		std::cout << "Freed memory: " << std::endl;
		std::cout << " - objects count = " << freedCount << std::endl;
		std::cout << " - total size = " << freedSize / 8.0f << " bytes" << std::endl;
	}
}

GarbageCollector* GarbageCollector::Get(void) {
	if (m_instance == nullptr) {
		m_instance = new GarbageCollector();
	}
	return m_instance;
}

void GarbageCollector::Destroy(bool verbose) {
	if (m_instance != nullptr) {
		m_instance->Collect(verbose);
		delete m_instance;
	}
}
