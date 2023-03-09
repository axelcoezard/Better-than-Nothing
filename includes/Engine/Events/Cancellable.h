/*
 * File: Cancellable.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Monday, 6th March 2023 4:47:21 pm
 * Last Modified: Tuesday, 7th March 2023 9:56:19 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

struct Cancellable {
	virtual ~Cancellable(void) {}

	virtual bool IsCancelled(void) = 0;
	virtual void SetCancelled(bool cancel) = 0;
};
