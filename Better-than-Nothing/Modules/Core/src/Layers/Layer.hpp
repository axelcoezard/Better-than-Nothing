#pragma once

namespace BetterThanNothing
{
	class Renderer;
	class Event;

	class Layer
	{
		private:
			std::string m_Label;
		public:
			Layer(const std::string& label);
			virtual ~Layer();

			virtual void OnAttach() = 0;
			virtual void OnDetach() = 0;
			virtual void OnUpdate(f32 deltatime) = 0;
			virtual void OnRender(Renderer* pRenderer) = 0;
			virtual void OnEvent(Event* pEvent) = 0;
			// TO-DO: add OnEvent method

			inline const std::string& GetName() const { return m_Label; }
	};
};
