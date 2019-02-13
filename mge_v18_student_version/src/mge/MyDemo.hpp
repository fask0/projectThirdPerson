#ifndef MYDEMO_HPP
#define MYDEMO_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

class MyDemo : public AbstractGame
{

	public:
	MyDemo();
	virtual ~MyDemo();

	//override initialize so we can add a DebugHud
	virtual void initialize();

	protected:
	//override so we can construct the actual scene
	virtual void _initializeScene();

	//override render to render the hud as well.
	virtual void _render();

	private:
	DebugHud* _hud;                   //hud display

	void _updateHud();

	MyDemo(const MyDemo&);
	MyDemo& operator=(const MyDemo&);
};

#endif