#include "Layer.hpp"

namespace BetterThanNothing
{
	class ImGuiLayer : public Layer
	{
		public:
			ImGuiLayer(void);
			~ImGuiLayer(void) = default;

			void OnAttach(void) override;
			void OnDetach(void) override;
			void OnUpdate(float deltatime) override;
			void OnRender(void) override;
	};
};
