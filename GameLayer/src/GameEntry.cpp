#include <RealEngine.h>


class GameLayer : public Real::Layer
{
public:
	float posX, posY = 0;
	float velocity = 1;
	GameLayer()
		:Layer("Game Layer") {}

	void OnUpdate() override
	{
		
	}
	void OnEvent(Real::Event& event) override
	{
		if(event.GetEventType() == Real::EventType::MouseMoved)
		{
			
		}
		else if (event.GetEventType() == Real::EventType::KeyPressed)
		{
			RL_TRACE("{}", event.ToString());
			Real::KeyPressedEvent e = static_cast<Real::KeyPressedEvent&>(event);
			if (e.GetKeyCode() == 87) { posY += velocity; }
			RL_DEBUG("{},{}", posX, posY);
		}
		
	}
};
//inherits from RealApp for engine functions 
class GameEntry : public Real::RealApp
{
public:
	GameEntry()
	{
		RealApp::PushLayer(new GameLayer());
	}
	~GameEntry()
	{

	}

private:
};

//Function declared in App class and defined here 
Real::RealApp* Real::CreateApp()
{	
	return new GameEntry();
}
