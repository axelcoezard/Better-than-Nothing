#pragma once

#include <Layers/Layer.hpp>

namespace BetterThanNothing
{
	class Layer;
	class Scene;
	class Event;

	class SceneLayer : public Layer
	{
		private:
			Scene* m_pScene;
		public:
			SceneLayer(Scene* pScene);
			~SceneLayer() = default;

			void OnAttach() override;
			void OnDetach() override;
			void OnUpdate(float deltatime) override;
			void OnRender(Renderer* pRenderer) override;
			void OnEvent(Event* pEvent) override;
	};
};
