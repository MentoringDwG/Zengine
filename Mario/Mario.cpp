#include "../Zengine/Zengine/Zengine.h"
#include "../Mario/Mario/Application/AppMarioGame.h"
#include <functional>
#include "../Zengine/Zengine/StateMachine/StateMachine.h"
#include "../Zengine/Zengine/Renderer/Renderer.h"
#include "../Zengine/Zengine/World/World.h"
#include "../Zengine/Zengine/InputModule/CharacterInputHandler.h"
#include "../Zengine/Zengine/InputModule/InputProcessorModule.h"

Zengine* engine = nullptr;

class StartApp
{
public:
	void Start(int i)
	{
		AppMarioGame* appMarioGame = new AppMarioGame(engine->GetStateMachine(), engine->GetRenderingStack(), engine->GetRenderer(), engine->GetWorld());
		appMarioGame->Initialize(engine);
	}
};

int main(int argc, char** argv)
{
	engine = Zengine::CreateInstance();

	StartApp startApp;

	engine->Start = std::bind(&StartApp::Start, startApp, std::placeholders::_1);
	engine->Run();

	return 0;
}