#include "Layer.hpp"

namespace BetterThanNothing
{
	class SceneLayer : public Layer
	{
		public:
			SceneLayer(void);
			~SceneLayer(void) = default;

			void OnAttach(void) override;
			void OnDetach(void) override;
			void OnUpdate(float deltatime) override;
			void OnRender(void) override;
	};
};
