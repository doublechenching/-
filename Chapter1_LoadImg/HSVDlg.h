#pragma once
#include "MedicalImg.h"

// CHSVDlg �Ի���

class CHSVDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHSVDlg)

public:
	CHSVDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CHSVDlg(CString imagePath, CWnd* pParent = NULL);
	virtual ~CHSVDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HSV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMedicalImg* m_pMedImage;
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedHsvCancel();
	afx_msg void OnBnClickedButtonLoad();
private:
	// �Ƿ���ͼ��
	bool m_bIsLoad;
	// ����·��
	CString m_strPath;
public:
	afx_msg void OnNMCustomdrawSliderH(NMHDR *pNMHDR, LRESULT *pResult);
	int m_iH;
	int m_iS;
	int m_iV;
	afx_msg void OnNMCustomdrawSliderS(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderV(NMHDR *pNMHDR, LRESULT *pResult);
};
