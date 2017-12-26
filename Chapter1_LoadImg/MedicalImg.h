/*********************************************************************************************************
* ģ������: MedicalImg
* ժ    Ҫ: MVC���������ģ�ͣ�ҽѧͼ��
* ��ǰ�汾: 1.0.0
* ��    ��: �س³�
* �������: 2017/12/20
* ��    ��: ҽѧͼ�����
* ע    ��: ���е�����ģ��ֻ�ܺͿ���������                                                                  
**********************************************************************************************************
* ȡ���汾: 
* ��    ��:
* �������: 
* �޸�����:
* �޸��ļ�: 
*********************************************************************************************************/
#pragma once

/*********************************************************************************************************
*                                              �ṹ�嶨��
*********************************************************************************************************/
struct Pixel
{
	unsigned char iR;
	unsigned char iG;
	unsigned char iB;
};

/*********************************************************************************************************
*                                              �ඨ��
*********************************************************************************************************/
class CMedicalImg
{
public:
	CMedicalImg(void);
	~CMedicalImg(void);
	CMedicalImg(CString path);			// ���ļ��ж�ȡDIB
	CMedicalImg(CBitmap& ddb, CPalette* palette);	// ��DDB�л��DIB
	void* GetBits();					// ������������
	int GetBitsPerPixel();				// ����ÿ�����ص�λ��
	long GetWidth();					// ��ȡͼ��Ŀ��
	long GetHeight();					// ��ȡͼ��ĸ߶�
	long BytesPerline();				// ���ͼ��ÿ��ɨ����������ֽ���
	CPalette* GetPalette();				// ��ȡ��ɫ��
	void CopyPalette(CPalette&);		// ���Ƶ�ɫ��
	int	GetPaletteCount();				// ��õ�ɫ��Ĵ�С
	long GetBodySize();					// �����������Ĵ�С
	// ��ָ��DC���������
	int StretchToDC(CDC& dc, CRect& src, CRect& dst, DWORD rop = SRCCOPY);
	int SetToDC(CDC& dc, CRect& src, CPoint& dst);	// ��ָ��DC����������ı��С
	void LoadImg(CString path);
	void SaveDIB(CString dibName);
	int GetPixelRGB(int row, int col, int &r, int &g, int b);
	void UpdateRGB(char * imageBuffer, int deltaR, int deltaG, int deltaB);
private:
	void* m_pDibBits;			// ��������
	BITMAPINFO*	m_pDibInfo;		// DIB�ļ�
public:
	CString m_strPath;			// ͼƬ·��
};

