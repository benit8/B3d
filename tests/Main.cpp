/*
** B, 2019
** tests / Main.cpp
*/

#include "B/SimpleApplication.hpp"
#include "B/Rendering/Mesh.hpp"
#include "B/Utils/Logger.hpp"

////////////////////////////////////////////////////////////////////////////////

using namespace B;

////////////////////////////////////////////////////////////////////////////////

int main()
{
	SimpleApplication app;
	bool paused = false;

	app.onCreate.add([&]() {
		auto win = app.createWindow(Size(1280, 720), "Hello World");
		app.createRenderer(*win);

		win->onClose.add([&] () {
			app.close();
		});

		/*
		win->onKeyDown.filter(
			std::bind(&SimpleApplication::close, app),
			[](const KeyEvent &e) {
				return e.noMods() && e.key == "escape";
			}
		);

		win->onKeyDown.filter(
			[&paused] { paused = !paused; },
			[] (const KeyEvent &e) {
				return e.key == "space";
			}
		);
		*/
	});

	Mesh mesh;
	app.onCreate.add([&] {
		if (!mesh.loadFromFile("../assets/ship.obj")) {
			LogFatal("Failed to load mesh");
		}

		mesh.translate({0, 0, 8});
		mesh.rotateX(0.5);
	});

	app.onUpdate.add([&] (f64 delta) {
		if (!paused)
			mesh.rotateY(delta / 2);
	});

	app.onRender.add([&] (std::shared_ptr<Renderer> renderer) {
		renderer->render(mesh);
	});

	app.onDestroy.add([&] () {
		app.window()->close();
	});

	return app.run();
}