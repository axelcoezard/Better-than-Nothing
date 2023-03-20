/*
 * File: WindowBuilder.hpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 7:34:58 pm
 * Last Modified: Tuesday, 7th March 2023 7:35:00 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <string>
#include <string_view>

struct Window;

struct WindowBuilder {
	private:
		static WindowBuilder* m_instance;
		std::string m_title;
		uint32_t m_width;
		uint32_t m_height;

	public:
		WindowBuilder* WithTitle(std::string_view title);
		WindowBuilder* WithSize(uint32_t width, uint32_t height);

		Window* Build(void) const;
};
