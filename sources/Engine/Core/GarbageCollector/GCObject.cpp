/*
 * File: GCObject.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Thursday, 9th March 2023 9:48:20 am
 * Last Modified: Thursday, 9th March 2023 9:48:21 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Core/GarbageCollector/GarbageCollector.h"
#include "Core/GarbageCollector/GCObject.h"


GCObject::GCObject(void): m_marked(false) {
	GarbageCollector::Get()->AddObject(this);
}

GCObject::~GCObject(void) {
	GarbageCollector::Get()->RemoveObject(this);
}

void GCObject::SetMarked(bool marked) {
	m_marked = marked;
}

bool GCObject::IsMarked(void) {
	return m_marked;
}

size_t GCObject::GetSize(void) {
	return m_size;
}

void* GCObject::operator new(size_t size) {
	return (void*) std::malloc(size);
}

void GCObject::operator delete(void* ptr) {
	if (ptr != nullptr) {
		std::free(ptr);
	}
}
