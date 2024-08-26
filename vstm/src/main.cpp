#include "vstmr/vstmr.h"

class Application : public vstmr::Application
{
	void some()
	{
	}
};

vstmr::Application* CreateApplication()
{
	return new Application{};
}