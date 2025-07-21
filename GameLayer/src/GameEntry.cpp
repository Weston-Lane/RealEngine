#include <RealEngine.h>
#include "GLFW/glfw3.h"

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
		
	}
};
//inherits from RealApp for engine functions 
class GameEntry : public Real::RealApp
{
public:
	GameEntry()
	{
		
		RealApp::PushLayer(new GameLayer());
		RealApp::PushOverlayLayer(new Real::ImGuiLayer());
		
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
