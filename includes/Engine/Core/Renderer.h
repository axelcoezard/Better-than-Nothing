/*
 * File: BehaviorCollector.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Thursday, 9th March 2023 1:18:31 pm
 * Last Modified: Thursday, 9th March 2023 1:18:36 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <set>

#include "Core/GarbageCollector/GCObject.h"
#include "Core/Behavior.h"

struct Renderer: public GCObject {
	private:
		static Renderer* m_instance;

		std::set<Behavior*> m_behaviors;
	public:
		Renderer(void);
		~Renderer(void);

		void RegisterBehavior(Behavior* object);
		void UnregisterBehavior(Behavior* object);

		void Update(void);
		void Render(void);

		static Renderer* Get(void);
};
