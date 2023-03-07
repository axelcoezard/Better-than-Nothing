/*
 * File: GameBehavior.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 10:31:26 pm
 * Last Modified: Tuesday, 7th March 2023 10:31:28 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

struct GameBehavior {
	virtual ~GameBehavior(void) {}

	virtual void OnEnable(void) = 0;
	virtual void OnDisabled(void) = 0;

	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
};
