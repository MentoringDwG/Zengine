#include "Zengine/Zengine.h"

int main(int argc, char** argv)
{
	// Tworzenie silnika i uruchomienie go.
	Zengine* engine = Zengine::CreateInstance();
	engine->Run();

	return 0;
}