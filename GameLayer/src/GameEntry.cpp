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

//Function declared in App class and defined here 
Real::RealApp* Real::CreateApp()
{
	RL_CORE_FATAL("{}",1);
	RL_FATAL("{}", 1);
	RL_CORE_ERROR("{}", 1);
	RL_ERROR("{}", 1);
	RL_CORE_WARN("{}", 1);
	RL_WARN("{}", 1);
	RL_CORE_INFO("{}", 1);
	RL_INFO("{}", 1);
	RL_CORE_DEBUG("{}", 1);
	RL_DEBUG("{}", 1);
	RL_CORE_TRACE("{}", 1);
	RL_TRACE("{}", 2);
	
	return new GameEntry();
}
