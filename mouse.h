#pragma once
class Mouse
{
public:
	Mouse();   //初始化，并移除快速编辑模式(对于win10用户)

	bool leftButtonDown();   //返回鼠标是否按下左键
	bool rightButtonDown();   //返回鼠标是否按下右键
	bool middleButtonDown();   //返回鼠标是否按下中键

	//获取鼠标箭头在窗口的位置，存储在成员x和y里，返回是否成功获取
	bool getCursorWindowPos();
	//获取鼠标箭头在窗口的坐标，存储在成员x和y里，返回是否成功获取；该坐标可用于Pos。
	bool getCursorWindowCoor();
	//获取鼠标箭头在整个屏幕的位置，存储在成员x和y里，返回是否成功获取
	bool getCursorScreenPos();

	int getX() { return x; }
	int getY() { return y; }
private:
	int x;
	int y;
};

