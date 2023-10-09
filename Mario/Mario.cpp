#include <Zengine/Zengine.h>
#include "Mario/Application/AppMarioGame.h"
#include <functional>
#include <Zengine/World/World.h>

Zengine* engine = nullptr;

class StartApp
{
public:
	AppMarioGame* appMarioGame = new AppMarioGame();

	void Start(int i)
	{
		appMarioGame->Initialize(engine);
	}
};

int main(int argc, char** argv)
{
	engine = Zengine::CreateInstance();

	StartApp startApp;

	engine->Start = std::bind(&StartApp::Start, startApp, std::placeholders::_1);
	engine->Run(startApp.appMarioGame->GetWorld());
	engine->Shutdown();

	return 0;
}