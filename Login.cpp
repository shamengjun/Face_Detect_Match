// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "facedetection.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Login.h"

// Login 对话框

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strUser(_T(""))
	, m_strPassword(_T(""))
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER, m_strUser);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDOK, &Login::OnBnClickedOk)
END_MESSAGE_MAP()


// Login 消息处理程序


void Login::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_strUser.IsEmpty() || m_strPassword.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空！"), _T("用户登录信息"));
		return;
	}
	else if (m_strUser == "1"&& m_strPassword == "1")
	{
		MessageBox(_T("登录成功！"), _T("登陆"));//这句可有可无

	}
	else
	{
		MessageBox(_T("用户名或密码不正确"), _T("提示"));
		return;
	}
	CDialogEx::OnOK();
}
