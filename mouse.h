#pragma once
class Mouse
{
public:
	Mouse();   //��ʼ�������Ƴ����ٱ༭ģʽ(����win10�û�)

	bool leftButtonDown();   //��������Ƿ������
	bool rightButtonDown();   //��������Ƿ����Ҽ�
	bool middleButtonDown();   //��������Ƿ����м�

	//��ȡ����ͷ�ڴ��ڵ�λ�ã��洢�ڳ�Աx��y������Ƿ�ɹ���ȡ
	bool getCursorWindowPos();
	//��ȡ����ͷ�ڴ��ڵ����꣬�洢�ڳ�Աx��y������Ƿ�ɹ���ȡ�������������Pos��
	bool getCursorWindowCoor();
	//��ȡ����ͷ��������Ļ��λ�ã��洢�ڳ�Աx��y������Ƿ�ɹ���ȡ
	bool getCursorScreenPos();

	int getX() { return x; }
	int getY() { return y; }
private:
	int x;
	int y;
};

