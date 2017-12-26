/*********************************************************************************************************
* ģ������: Chapter1_LoadImgDlg.h
* ժ    Ҫ: MVC�ܹ������Ŀ�����
* ��ǰ�汾: 1.0.0
* ��    ��: �س³�
* �������: 2017��12��20��
* ��    ��: ���Ի�����ΪMVC�ܹ��Ŀ�����
* ע    ��: 
**********************************************************************************************************
* ȡ���汾:
* ��    ��:
* �������:
* �޸�����:
* �޸��ļ�:
*********************************************************************************************************/


/*********************************************************************************************************
*                                              ����ͷ�ļ�
*********************************************************************************************************/
#pragma once
#include "piccontrol.h"
#include "MedicalImg.h"


/*********************************************************************************************************
*                                              �궨��
*********************************************************************************************************/
#define WM_SHOW_POS WM_USER+10


/*********************************************************************************************************
*                                              �ඨ��
*********************************************************************************************************/
class CChapter1_LoadImgDlg : public CDialogEx
{
// Construction
public:
	CChapter1_LoadImgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHAPTER1_LOADIMG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnShowPos(WPARAM,LPARAM);		//���������ͣ��Ϣ
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnOpenImage();
	afx_msg void OnSave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);



// Variable
public:
	/*View*/
	CPicControl m_picControl;
	CStatusBar m_wndStatusBar;
	CMenu m_ctrMenu;
	/*Data*/
	CMedicalImg* m_pMedImage;
	virtual void OnFinalRelease();
	afx_msg void OnHsvAdjust();
};
