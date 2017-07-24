
// facedetectionDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

UINT ThreadFunc(LPVOID pParm);
UINT ThreadFunc1(LPVOID pParm);
UINT ThreadFunc2(LPVOID pParm);
// CfacedetectionDlg 对话框
#define   WM_UPDATEDATA   WM_USER + 5 
class CfacedetectionDlg : public CDialogEx
{
// 构造
public:
	CfacedetectionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACEDETECTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic card;
	afx_msg void OnBnClickedLoadPicBut();
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedStatic2();
	CString detect_use_time;
	afx_msg void OnStnClickedStaticTime();
	afx_msg void OnBnClickedButton2Exit();
	afx_msg void OnStnClickedroi();
	afx_msg void OnStnClickedface();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	LRESULT OnUpdateData(WPARAM wParam, LPARAM lParam);
	CWinThread  *pThread;//匹配计算线程
	CWinThread  *pThread1;//加载卡信息线程
	CWinThread  *pThread2;
	void my_accept();
	CString match_result;
	double similarity;
	afx_msg void OnEnChangeMatchResult();
	double match_distance;
	double match_of_distance;
	CString m_strName;
	CString m_strSex;
	CString m_strFolk;
	CString m_strBirth;
	CString m_strAddr;
	CString m_strIdnum;
	CString m_strDep;
	CString m_strBegin;
	CString m_strEnd;
	CStatic m_ctPicCard;
	CFont m_editFont;
	//afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedButton4();
	CStatic m_ctCardroi;
//	int m_intNum;
	CString m_strTimer;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeMatchDistance();
};
