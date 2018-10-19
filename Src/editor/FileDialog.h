#pragma once

#include "inc.h"

enum eFileDialogUsage
{
	eFileDialogUsage_OpenFile,
	eFileDialogUsage_SaveFile,
	eFileDialogUsage_OpenFolder
};

class FileDialog
{
public:
	FileDialog(const char* name, const char* ext, eFileDialogUsage usage);
	// �����ļ��Ի���Ĭ���ļ���;
	void SetDefaultDirectory(const std::string& szDir);
	// ����Open()�������ļ��Ի���;
	void Open();
	// ���ȷ������true�����ȡ������false��Render��ÿ֡����;
	bool DoModal();
	// ��ǰ�ļ��Ի����Ƿ��;
	bool IsOpen();
	// DoModal()����trueʱ�򣬿��Ի���ļ���;
	const char* GetFileName();
	// DoModal()����trueʱ�򣬿��Ի���ļ�����;
	const char* GetDirectory();
	// �ļ����Ƿ���ָ����ʽ��;
	static bool IsExt(const std::string& filename, const std::string& ext);
private:
	void GetFiles(const std::string& path);
private:
	std::string fileName;
	char directory[MAX_PATH];
	char cur_directory[MAX_PATH];
	bool open;
	std::string dlgName;
	eFileDialogUsage mUsage;
	std::string mExt;
	char cur_filename[MAX_PATH];
	int selFileIndex;
	int selFolderIndex;
	std::vector<std::string> files;
	std::vector<std::string> folders;
};