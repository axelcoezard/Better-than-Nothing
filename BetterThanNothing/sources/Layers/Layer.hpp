namespace BetterThanNothing
{
	class Layer
	{
		public:
			virtual ~Layer(void) = default;

			virtual void OnAttach(void) = 0;
			virtual void OnDetach(void) = 0;
			virtual void OnUpdate(float deltatime) = 0;
			virtual void OnRender(void) = 0;
	};
};
