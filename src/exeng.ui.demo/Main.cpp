
#include <exeng/ui/Window.hpp>
#include <exeng/ui/Label.hpp>
#include <exeng/ui/Button.hpp>
#include <exeng.main/Main.hpp>

#include <memory>

namespace exeng { namespace main {
	int main(int argc, char** argv) {

		using namespace exeng;
		using namespace exeng::ui;

		Window mainWindow;
		Label label(&mainWindow);
		Button button(&mainWindow);

		mainWindow.setText("exeng.ui.demo Application")
			->seSize(400, 400)
			->setPosition(100, 100)
			->setVisible(true);

		exeng::Size2i size;
		exeng::Vector2i pos;

		label.setText("Hello, world!")
			->seSize(400, 400)
			->setPosition(100, 100)
			->setVisible(true);

		size = label.geSize();
		pos = label.getPosition();

// 		button->setText("Push me!")->setWidth(250)->setHeight(45)->setLeft(20)->setTop(120);
// 		button->setVisible(true);

		while (mainWindow.doEvent()) {}

		return 0;
	}
}}
