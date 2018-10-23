#pragma once





class ImguiManager
{
private:
	static ImguiManager* m_Instance;
	D3DClass m_d3dobj;

public:
	ImguiManager();
	~ImguiManager();

	void Init();
	void Update();
	void Destroy();

	static ImguiManager* getInstance();

};

