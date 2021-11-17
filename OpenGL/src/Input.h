#pragma once

#include <vector>

class Input
{
private:
	static bool previousFrameKeysPressed[27];
public:
	enum KeyCode {Q,W,E,R,T,Y,U,I,O,P,A,S,D,F,G,H,J,K,L,Z,X,C,V,B,N,M,SPACE};
	static bool GetKey(KeyCode keyCode);
	static bool GetKeyDown(KeyCode keyCode);
	static void OnUpdate();
};