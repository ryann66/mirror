#include "LevelSelectorScene.hh"

#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <filesystem>
#include <stdexcept>
#include <algorithm>

#include "Vector2.hh"
#include "Level.hh"
#include "LevelButton.hh"
#include "Label.hh"
#include "Window.hh"
#include "ErrorScene.hh"

#include "EmptyLevelSelectorScene.hh"

using std::string;
using std::logic_error;
using std::pair;
using std::sort;

using std::filesystem::directory_iterator;
using std::filesystem::directory_entry;
using std::filesystem::path;

using vector::Vector2;

namespace menu {

LevelSelectorScene* curScene;

float originY;
float clickY;

/**
 * Motion function for scrollbar
 */
void scrollbarMotionFunc(int x, int y) {
	float newY = originY + y - clickY;
	if (newY > curScene->maxScrollbarY) newY = curScene->maxScrollbarY;
	else if (newY < -curScene->maxScrollbarY) newY = -curScene->maxScrollbarY;
	curScene->scrollbar->offset.y = newY;

	// move buttons
	float scrollbarProgression = (newY + curScene->maxScrollbarY) / (2 * curScene->maxScrollbarY);
	float scrollbarButtonOffset = -curScene->maxScrollbarButtonsOffsetY * scrollbarProgression;
	scrollbarButtonOffset -= (scrollbarHeight / 2) * DEFAULT_BUTTON_SIZE.y;
	for (Button* b : curScene->scrollbarButtons) {
		b->offset.y = scrollbarButtonOffset;
		scrollbarButtonOffset += DEFAULT_BUTTON_SIZE.y;
	}

	glutPostRedisplay();
}

/**
 * OnClick function for scrollbar
 */
void scrollbarClickFunc() {
	glutMotionFunc(scrollbarMotionFunc);
}

/**
 * Handles displaying menu elements for the level selector scene
*/
void levelSelectorSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Button* b : curScene->buttons) b->display();

	// hide extra buttons
	glColor4f(0., 0., 0., 0.);
	vector::Vector2 ori(curScene->selectorBox.origin()), ds(curScene->selectorBox.destination());
	glRectf(-1, 1, 1, glCoordSpaceY(ori.y));
	glRectf(-1, 1, glCoordSpaceX(ori.x), -1);
	glRectf(-1, -1, 1, glCoordSpaceY(ds.y));
	glRectf(1, -1, glCoordSpaceX(ds.x), 1);

	for (MenuElement* e : curScene->elements) e->display();
	glutSwapBuffers();
}

/**
 * Handles clicking on buttons in level selector menu
*/
void levelSelectorSceneClickFunc(int button, int state, int x, int y) {
	if (curScene->selectorBox.inBounds(vector::Vector2(x, y)) && button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			for (Button* b : curScene->buttons) {
				if (b->inBounds(vector::Vector2(x, y))) b->onClick();
			}
			clickY = y;
			originY = curScene->scrollbar->offset.y;
		} else if (state == GLUT_UP) {
			glutMotionFunc(hoverFunc);
			hoverFunc(x, y);
		}
	}
}

LevelSelectorScene::LevelSelectorScene(std::vector<Button*>& scrollbarButtons) : 
	MenuScene(LEVEL_SELECTOR), 
	scrollbarButtons(scrollbarButtons), 
	selectorBox(CENTER, Vector2(), Vector2(DEFAULT_BUTTON_SIZE.x + SCROLLBAR_WIDTH, scrollbarHeight * DEFAULT_BUTTON_SIZE.y)),
	maxScrollbarButtonsOffsetY(DEFAULT_BUTTON_SIZE.y * (scrollbarButtons.size() - scrollbarHeight)) {
	const float offset = SCROLLBAR_WIDTH / -2;
	for (Button* b : scrollbarButtons) {
		b->offset.x = offset;
		this->addButton(b);
	}
	scrollbar = new EasyButton(CENTER, Vector2(DEFAULT_BUTTON_SIZE.x / 2, 0),
			Vector2(SCROLLBAR_WIDTH - SCROLLBAR_PADDING, (DEFAULT_BUTTON_SIZE.y * scrollbarHeight * scrollbarHeight / scrollbarButtons.size()) - SCROLLBAR_PADDING),
			"", scrollbarClickFunc);
	maxScrollbarY = (scrollbarHeight * DEFAULT_BUTTON_SIZE.y - scrollbar->size.y) / 2;
	scrollbar->offset.y = -maxScrollbarY;
	this->addButton(scrollbar);
}

void LevelSelectorScene::onLoad() {
	curScene = this;
	MenuScene::onLoad();
	glutDisplayFunc(levelSelectorSceneDisplayFunc);
	glutMouseFunc(levelSelectorSceneClickFunc);
}

Scene* levelSelectorMenu() {
	// get list of levels 
	std::vector<pair<path, string>> filepaths;
	for (directory_entry file : directory_iterator("./levels")) {
		if (!file.is_regular_file()) continue;
		filepaths.emplace_back(file.path(), menu::levelNameFromFilename(file.path()));
	}

	// sort list of levels
	sort(filepaths.begin(), filepaths.end(), [](pair<path, string>& lhs, pair<path, string>& rhs) { return menu::cmpAlphabetical(lhs.second, rhs.second); });

	// make buttons
	std::vector<Button*> levelButtons;
	Vector2 offset(0, -(scrollbarHeight / 2) * DEFAULT_BUTTON_SIZE.y);
	const int labelY = offset.y - DEFAULT_BUTTON_SIZE.y;
	for (pair<path, string>& filepath : filepaths) {
		LevelButton* level = new LevelButton(offset, filepath.second, filepath.first);
		levelButtons.push_back(level);
		offset.y += DEFAULT_BUTTON_SIZE.y;
	}

	// create scene to display (use menu scene if not enough to require scrollbar)
	MenuScene* retscene;
	if (levelButtons.size() <= scrollbarHeight) {
		if (levelButtons.empty()) {
			return new EmptyLevelSelectorScene();
		}
		retscene = new MenuScene(LEVEL_SELECTOR);
		for (Button* lb : levelButtons) retscene->addButton(lb);
	} else {
		retscene = new LevelSelectorScene(levelButtons);
	}

	// add common labels
	offset.y = labelY;
	retscene->addElement(new Label(CENTER, offset, "Select a level", MenuLabelColor));

	return retscene;
}

}  // namespace menu