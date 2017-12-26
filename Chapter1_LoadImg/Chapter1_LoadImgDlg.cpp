/*********************************************************************************************************
* ģ������: Chapter1_LoadImgDlg.c
* ժ    Ҫ: MVC�ܹ������Ŀ�����
* ��ǰ�汾: 1.0.0
* ��    ��: �س³�
* �������: 2017��12��20��
* ��    ��: ���Ի�����ΪMVC�ܹ��Ŀ�����
* ע    ��: ���е�
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
#include "stdafx.h"
#include "Chapter1_LoadImg.h"
#include "Chapter1_LoadImgDlg.h"
#include "afxdialogex.h"
#include "ImgProcAlgorithm.h"
#include "HistDlg.h"
#include "HSVDlg.h"

/*********************************************************************************************************
*                                              �궨��
*********************************************************************************************************/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/*********************************************************************************************************
*                                              �ڲ�����
*********************************************************************************************************/
static UINT BASED_CODE indicators[] = {
	ID_INDICATOR_TIME,
	ID_INDICATOR_POS,
	ID_INDICATOR_PIXEL,
	ID_INDICATOR_HSV
};


/*********************************************************************************************************
*                                              �ڲ��ඨ��
*********************************************************************************************************/
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


/*********************************************************************************************************
*                                              ���Ա����ʵ��
*********************************************************************************************************/

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	CChapter1_LoadImgDlg
* ����Ȩ��: Public
* ��������: ���캯��, ��ʼ��ICON
* �������: pParent: CWnd *, �����ھ��
* �������: void
* �� �� ֵ: void
* ע    ��: 
*********************************************************************************************************/
CChapter1_LoadImgDlg::CChapter1_LoadImgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChapter1_LoadImgDlg::IDD, pParent), m_pMedImage(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	/*��ʼ���ڲ�����*/
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	DoDataExchange
* ����Ȩ��: Private
* ��������: �ռ��븸���ڽ������ݽ���
* �������: pDX: CDataExchange*, ����������ָ��
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_picControl);
}

/*********************************************************************************************************
* ��������:	BEGIN_MESSAGE_MAP
* ��������: ӳ��ؼ�����Ӧ��Ϣ����
* �������: CChapter1_LoadImgDlg, CDialogEx
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
BEGIN_MESSAGE_MAP(CChapter1_LoadImgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CChapter1_LoadImgDlg::OnBnClickedButtonClose)
	ON_MESSAGE(WM_SHOW_POS, &CChapter1_LoadImgDlg::OnShowPos) 
	ON_COMMAND(ID_OPEN, &CChapter1_LoadImgDlg::OnOpenImage)
	ON_COMMAND(ID_SAVE, &CChapter1_LoadImgDlg::OnSave)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_COMMAND(ID_HSV_ADJUST, &CChapter1_LoadImgDlg::OnHsvAdjust)
END_MESSAGE_MAP()

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnInitDialog
* ����Ȩ��: Protected
* ��������: ��ʼ����Ϣ��Ӧ���������ʼ�����пռ�
* �������: pDX: CDataExchange*, ����������ָ��
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
BOOL CChapter1_LoadImgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	/*��ʼ���˵�*/
	m_ctrMenu.LoadMenu(IDR_MENU1);
	SetMenu(&m_ctrMenu);
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	/*����״̬��*/
	m_wndStatusBar.Create(this);
	m_wndStatusBar.SetIndicators(indicators, 4);
	CRect rect;
	GetClientRect(&rect);
	m_wndStatusBar.SetPaneInfo(0, ID_INDICATOR_TIME, SBPS_STRETCH, 0);
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_POS, SBPS_STRETCH, 0);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_PIXEL, SBPS_STRETCH, 0);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_HSV, SBPS_STRETCH, 0);
	m_wndStatusBar.GetStatusBarCtrl().SetBkColor(RGB(250, 180, 56));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, AFX_IDW_CONTROLBAR_FIRST);
	/*���ö�ʱ��*/
	SetTimer(1, 1000, NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}


/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnSysCommand
* ����Ȩ��: Private
* ��������: ��Ӧϵͳ��Ϣ
* �������: nID: UINT, ��Դ�������lParam: LPARAM, ��ָ��
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnPaint
* ����Ȩ��: Private
* ��������: ��Ӧ��ͼ��Ϣ�����е��ػ�������ִ��
* �������: void
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	if (m_pMedImage)
	{
		CRect rect;
		CWnd* pImgWnd = GetDlgItem(IDC_STATIC_PIC);
		pImgWnd->GetClientRect(&rect);
		CDC* pImgDC = pImgWnd->GetDC();
		m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));
	}
	
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnQueryDragIcon-
* ����Ȩ��: Private
* ��������: ��Ӧ����϶�ͼ����Ϣ
* �������: void
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
HCURSOR CChapter1_LoadImgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnBnClickedButtonClose
* ����Ȩ��: Private
* ��������: ��Ӧ�˳���ť��Ϣ���˳�����
* �������: void
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	if (m_pMedImage)
	{
		delete m_pMedImage;
	}
	SendMessage(WM_CLOSE);
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnShowPos
* ����Ȩ��: Private
* ��������: ��Ӧ��̬�ı�������ƶ���Ϣ����ȡ�����Կռ����Ͻǵ�λ�ã�������״̬��
* �������: ix�� WPARAM�������ꣻiy�� LPARAM��������
* �������: LRESULT���ͣ� 0��ʶ�ɹ�ִ�У����㣬��ʶ�쳣
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
LRESULT CChapter1_LoadImgDlg::OnShowPos( WPARAM ix, LPARAM iy)
{
	//���������ͣ�¼�
	int x = ix;
	int y = iy;
	CString strPos;
	strPos.Format(_T("����: (%d, %d)"), x, y);
	m_wndStatusBar.SetPaneText(1, strPos);
	CPoint p(x, y);
	COLORREF color = m_picControl.GetDC()->GetPixel(p);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	CString strRGB;
	strRGB.Format(_T("RGB(%d, %d, %d)"), r, g, b);
	m_wndStatusBar.SetPaneText(2, strRGB);
	float h, s, v;
	CImgProcAlgorithm::RGB2HSV(r, g, b, h, s, v);
	CString strHSV;
	strHSV.Format(_T("HSV(%.3f, %.3f, %.3f)"), h, s, v);
	m_wndStatusBar.SetPaneText(3, strHSV);
	// validate
	// CImgProcAlgorithm::HSV2RGB(int(h), int(s), int(v), r, g, b);
	
	return 0;
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnOpenImage
* ����Ȩ��: Private
* ��������: ��Ӧ�˵����Ĵ��ļ���Ϣ��ִ�е���ͼƬ���ع��ܣ������¾�̬�ı�����ʾͼ��
* �������: void
* �������: LRESULT���ͣ� 0��ʶ�ɹ�ִ�У����㣬��ʶ�쳣
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnOpenImage()
{
	/*���ļ��Ի���*/
	CString filter = L"�����ļ�(*.bmp,*.jpg,*.tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp|JPG(*.jpg)|*.jpg|GIF(*.gif)|TIFF(*.tiff)|*.tiff";
	CFileDialog fileDLg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	if (IDOK == fileDLg.DoModal())
	{
		CString fPath = fileDLg.GetPathName();			// ��ȡ�ļ�·��  
		CString fEnt = fileDLg.GetFileExt();			// ��ȡ�ļ���չ��  
		fEnt.MakeLower();								// ���ļ���չ��ת��ΪСд��ĸ  

		if (fEnt.Compare(_T("bmp")) == 0)
		{	// ����򿪵���bmp�ļ�
			if (!m_pMedImage)
			{
				m_pMedImage = new CMedicalImg(fPath);
			}
			else
			{
				delete m_pMedImage;
				m_pMedImage = new CMedicalImg(fPath);
			}
			/*��ʾͼ��*/
			// ���´��ڴ�С
			CWnd* pImgWnd = GetDlgItem(IDC_STATIC_PIC);
			long imgHeight = abs(m_pMedImage->GetHeight());
			long imgWidth = m_pMedImage->GetWidth();
			SetWindowPos(NULL, 0, 0, imgWidth + 38, imgHeight + 150, SWP_NOZORDER | SWP_NOMOVE);
			pImgWnd->SetWindowPos(NULL, 0, 0, imgWidth, imgHeight, SWP_NOZORDER | SWP_NOMOVE);
			CWnd* pBtnWnd = GetDlgItem(IDC_BUTTON_CLOSE);
			pBtnWnd->SetWindowPos(NULL, imgWidth - 200, imgHeight + 30, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			UpdateWindow();
			CDC* pImgDC = pImgWnd->GetDC();
			CRect rect;
			pImgWnd->GetClientRect(&rect);
			m_pMedImage->SetToDC(*pImgDC, rect, (CPoint(0, 0)));
		}
		else
		{
			AfxMessageBox(_T("�ļ���ʽ������Ҫ��"));
		}
	}
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnSave
* ����Ȩ��: Private
* ��������: ��Ӧ�˵����ı����ļ���Ϣ��ִ�д��ļ��Ի���ͱ����ļ�
* �������: void
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnSave()
{
	// TODO: �ڴ���������������
	// ����ͼ��
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnTimer
* ����Ȩ��: Private
* ��������: ��Ӧ��ʱ����Ϣ������״̬��ʱ��
* �������: void
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString strTime;
	// ��ȡϵͳ��ǰʱ�䣬�����浽curTime   
	CTime curTime = CTime::GetCurrentTime();
	// ��ʽ��curTime�����ַ������浽strTime   
	strTime = curTime.Format(_T("%Y��%m��%d�� %H:%M:%S"));
	// ��״̬����ʱ�䴰������ʾϵͳʱ���ַ���   
	m_wndStatusBar.SetPaneText(0, strTime);

	CDialogEx::OnTimer(nIDEvent);
}

/*********************************************************************************************************
* ������:	CChapter1_LoadImgDlg
* ��������:	OnSize
* ����Ȩ��: Private
* ��������: ��Ӧ���ڴ�С�ı���Ϣ������״̬��λ��
* �������: void
* �������: void
* �� �� ֵ: void
* ע    ��:
*********************************************************************************************************/
void CChapter1_LoadImgDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_wndStatusBar.GetSafeHwnd())
	{
		CRect  m_rect;
		GetClientRect(&m_rect);
		m_rect.top = m_rect.bottom - 20;
		m_wndStatusBar.MoveWindow(&m_rect, TRUE);
	}
}


void CChapter1_LoadImgDlg::OnFinalRelease()
{
	// TODO: �ڴ����ר�ô����/����û���
	if (m_pMedImage)
	{
		delete m_pMedImage;
	}
	CDialogEx::OnFinalRelease();
}



void CChapter1_LoadImgDlg::OnHsvAdjust()
{
	// TODO: �ڴ���������������
	//CHSVDlg hsvdlg(m_pMedImage->m_strPath, this);

	//hsvdlg.DoModal();
	if (m_pMedImage)
	{
		CHSVDlg dlg(m_pMedImage->m_strPath, this);
		dlg.DoModal();
	}
	else
	{
		CHSVDlg dlg(this);
		dlg.DoModal();
	}
	
}
