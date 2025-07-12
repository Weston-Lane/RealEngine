#include <print>
#include <RealEngine.h>

//inherits from RealApp for engine functions 
class GameEntry : public Real::RealApp
{
public:
	GameEntry()
	{

	}
	~GameEntry()
	{

	}

private:
};

//Function declared in EntryPoint and defined here 
Real::RealApp* Real::CreateApp()
{
	return new GameEntry();
}
