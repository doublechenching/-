/*********************************************************************************************************
* ģ������: MedicalImg
* ժ    Ҫ: ͼƬ�ؼ�ʵ��
* ��ǰ�汾: 1.0.0
* ��    ��: �س³�
* �������: 2017/12/20
* ��    ��: 
* ע    ��: none                                                                  
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
#include "StdAfx.h"
#include "MedicalImg.h"
#include <vector>

using std::vector;		//ֻ���벿������
/*********************************************************************************************************
*                                              ���Ա����ʵ��
*********************************************************************************************************/

/*********************************************************************************************************
* ��������:  CMedicalImg::CMedicalImg
* Ȩ    ��:  public 
* ��������:  ���캯��
* ��    ��:  void
* �� �� ֵ:  
* ע    ��:  
*********************************************************************************************************/
CMedicalImg::CMedicalImg(void)
	:m_pDibInfo(NULL), m_strPath(L""), m_pDibBits(NULL)
{
}


/*********************************************************************************************************
* ��������:  CMedicalImg::CMedicalImg
* Ȩ    ��:  public 
* ��������:  ͨ��ͼƬ·����ʼ������
* ��    ��:  CString path
* �� �� ֵ:  
* ע    ��:  
*********************************************************************************************************/
CMedicalImg::CMedicalImg(CString path )
	: m_strPath(path)
{
	LoadImg(path);
}


CMedicalImg::CMedicalImg(CBitmap& ddb, CPalette* palette)
	:m_pDibInfo(NULL), m_strPath(L""), m_pDibBits(NULL)
{
	BITMAP ddbinfo;
	//���DDB�������Ϣ
	ddb.GetBitmap(&ddbinfo);
	/*�������ͼ��ĸ߶ȿ�ȵ���Ϣ����дDIB�������BITMAPINFO*/
	int w = ddbinfo.bmWidth;
	int h = ddbinfo.bmHeight;
	int BitsPerPixel = ddbinfo.bmPlanes*ddbinfo.bmBitsPixel;

	int i;
	int PaletteSize = 0, cbHeaderSize;

	//����ÿ������Ҫ����bit������RGBQUAD����Ĵ�С
	switch (BitsPerPixel)
	{
	case 1:
		PaletteSize = 2;
		break;
	case 4:
		PaletteSize = 16;
		break;
	case 8:
		PaletteSize = 256;
		break;
		//����8λ��DIB����Ҫ��ɫ��
	case 15:
	case 16:
		BitsPerPixel = 16;
		break;
	}

	cbHeaderSize = sizeof(BITMAPINFOHEADER) + PaletteSize * sizeof(RGBQUAD);
	if (m_pDibInfo) delete[] m_pDibInfo;
	//ΪBITMAPINFO�Ķ���DibInfo����һ���ڴ�ռ�
	m_pDibInfo = (BITMAPINFO*) new char[cbHeaderSize];
	//��дBITMAPINFO
	m_pDibInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pDibInfo->bmiHeader.biWidth = w;
	m_pDibInfo->bmiHeader.biHeight = h;
	m_pDibInfo->bmiHeader.biPlanes = 1;
	m_pDibInfo->bmiHeader.biBitCount = short(BitsPerPixel);
	m_pDibInfo->bmiHeader.biCompression = BI_RGB;
	m_pDibInfo->bmiHeader.biSizeImage = BytesPerline() * m_pDibInfo->bmiHeader.biHeight;
	m_pDibInfo->bmiHeader.biXPelsPerMeter = m_pDibInfo->bmiHeader.biYPelsPerMeter = 3780;
	m_pDibInfo->bmiHeader.biClrUsed = PaletteSize;
	m_pDibInfo->bmiHeader.biClrImportant = PaletteSize;

	if (PaletteSize)
	{
		//��RGBQUAD�����е�ÿ��Ԫ��ȫ����0
		for (i = 0; i < PaletteSize; i++)
		{
			m_pDibInfo->bmiColors[i].rgbRed = 0;
			m_pDibInfo->bmiColors[i].rgbGreen = 0;
			m_pDibInfo->bmiColors[i].rgbBlue = 0;
			m_pDibInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	//ΪDIB�����������ռ䣬��С��GetBodySize()����
	m_pDibBits = (void*) new char[GetBodySize()];
	//�ж��Ƿ��ɵ�ɫ�壬�������palette�е�entry
	//���Ƶ�BITMAPINFO��RGBQUAD������
	if (palette) CopyPalette(*palette);

	// ��DDB�е�ͼ����Ϣ���Ƶ�DIB��
	// GetDesktopWindow()�������洰�ڵľ��
	CWnd DesktopWnd;
	DesktopWnd.Attach(::GetDesktopWindow());
	CWindowDC dtpDC(&DesktopWnd);
	// ��ɴ�DDB��DIB��ת������
	::GetDIBits(dtpDC.m_hDC,
		HBITMAP(ddb),
		0,
		ddbinfo.bmHeight,
		LPVOID(m_pDibBits),
		m_pDibInfo,
		DIB_RGB_COLORS
		);
	DesktopWnd.Detach();
}


void* CMedicalImg::GetBits()
{
	return m_pDibBits;
}

int CMedicalImg::GetBitsPerPixel()
{
	if (!m_pDibInfo)
	{
		return 0;
	}
		
	return m_pDibInfo->bmiHeader.biBitCount;
}

long CMedicalImg::GetWidth()
{
	return m_pDibInfo->bmiHeader.biWidth;
}

long CMedicalImg::GetHeight()
{
	return m_pDibInfo->bmiHeader.biHeight;
}

long CMedicalImg::BytesPerline()
{
	return ((((m_pDibInfo->bmiHeader.biWidth * GetBitsPerPixel()) + 31) / 32) * 4);
}

void CMedicalImg::CopyPalette(CPalette& palette)
{
	int i;
	PALETTEENTRY *pe;

	if (!m_pDibInfo->bmiHeader.biBitCount) return;
	if (palette.GetEntryCount() != m_pDibInfo->bmiHeader.biBitCount) return;

	pe = new PALETTEENTRY[palette.GetEntryCount()];
	palette.GetPaletteEntries(0, palette.GetEntryCount(), pe);

	for (i = 0; i < palette.GetEntryCount(); i++)
	{
		m_pDibInfo->bmiColors[i].rgbRed = pe[i].peRed;
		m_pDibInfo->bmiColors[i].rgbGreen = pe[i].peGreen;
		m_pDibInfo->bmiColors[i].rgbBlue = pe[i].peBlue;
		m_pDibInfo->bmiColors[i].rgbReserved = 0;
	}

	delete[] pe;
}

int CMedicalImg::GetPaletteCount()
{
	int iPaletteSize = 0;
	if (!m_pDibInfo) return 0;
	switch (m_pDibInfo->bmiHeader.biBitCount)
	{
	case 1:
		iPaletteSize = 2;
		break;
	case 4:
		iPaletteSize = 16;
		break;
	case 8:
		iPaletteSize = 256;
		break;
	}
	return iPaletteSize;
}

long CMedicalImg::GetBodySize()
{
	return BytesPerline() * m_pDibInfo->bmiHeader.biHeight;
}


int CMedicalImg::StretchToDC(CDC& dc, CRect& src, CRect& dst, DWORD rop /*= SRCCOPY*/)
{
	return ::StretchDIBits(
		dc.m_hDC,
		dst.left,
		dst.top,
		dst.Width(),
		dst.Height(),
		src.left,
		src.top,
		src.Width(),
		src.Height(),
		m_pDibBits,
		m_pDibInfo,
		DIB_RGB_COLORS,
		rop
		);
}

int CMedicalImg::SetToDC(CDC& dc, CRect& src, CPoint& dst)
{
	return ::SetDIBitsToDevice(
		dc.m_hDC,
		dst.x,
		dst.y,
		src.Width(),
		src.Height(),
		src.left,
		src.top,
		0,
		m_pDibInfo->bmiHeader.biHeight,
		m_pDibBits,
		m_pDibInfo,
		DIB_RGB_COLORS
		);
}

/*********************************************************************************************************
* ��������:  CMedicalImg::~CMedicalImg
* Ȩ    ��:  public 
* ��������:  ��������
* ��    ��:  void
* �� �� ֵ:  
* ע    ��:  
*********************************************************************************************************/
CMedicalImg::~CMedicalImg(void)
{
	delete[] m_pDibInfo;
	delete[] m_pDibBits;
}


/*********************************************************************************************************
* ��������:  CMedicalImg::LoadImg
* Ȩ    ��:  public 
* ��������:  ͨ��·������ͼƬ
* ��    ��:  CString path�� ͼƬ·��
* �� �� ֵ:  
* ע    ��:  
*********************************************************************************************************/
void CMedicalImg::LoadImg( CString path )
{
	// ����CFile����
	m_strPath = path;
	CFile bmpFile(path, CFile::modeRead | CFile::typeBinary);

	BITMAPFILEHEADER bmfileheader;
	BITMAPINFOHEADER bmheader;

	ULONGLONG headpos;
	int iPaletteSize = 0;
	int iRet, iCB_HeaderSize;
	// ��ȡ�ļ�ָ���λ��
	headpos = bmpFile.GetPosition();
	// ��ȡBMP�ļ�ͷ
	iRet = bmpFile.Read(&bmfileheader, sizeof(BITMAPFILEHEADER));
	// ����ļ����ͱ�ͷ���ǡ�0x4d42������ʾ���ļ�����BMP�����ļ�
	if (bmfileheader.bfType != 0x4d42)
	{
		AfxMessageBox(L"Error!");
		return;
	}
	// ��ȡBMP�ļ���Ϣͷ	
	iRet = bmpFile.Read(&bmheader, sizeof(BITMAPINFOHEADER));
	// ����RGBQUAD�Ĵ�С
	switch (bmheader.biBitCount)
	{
	case 1:
		iPaletteSize = 2;
		break;
	case 4:
		iPaletteSize = 16;
		break;
	case 8:
		iPaletteSize = 256;
		break;
	}

	// ΪBITMAPINFO�ṹ�����ڴ�
	iCB_HeaderSize = sizeof(BITMAPINFOHEADER) + iPaletteSize*sizeof(RGBQUAD);
	m_pDibInfo = (BITMAPINFO*) new char[iCB_HeaderSize];
	m_pDibInfo->bmiHeader = bmheader;
	// ��ȡ��ɫ��
	if (iPaletteSize)
	{
		iRet = bmpFile.Read(&(m_pDibInfo->bmiColors[0]), iPaletteSize*sizeof(RGBQUAD));
		if (iRet != int(iPaletteSize*sizeof(RGBQUAD)))
		{
			delete[] m_pDibInfo;
			m_pDibInfo = NULL;
			return;
		}
	}

	// Ϊ�����������ռ䣬��С��GetBodySize()����
	m_pDibBits = (void*) new char[GetBodySize()];
	// ���ļ�ָ���ƶ���DIBͼ������
	bmpFile.Seek(headpos + bmfileheader.bfOffBits, CFile::begin);
	// ��ȡ��������
	iRet = bmpFile.Read(m_pDibBits, GetBodySize());
	if (iRet != int(GetBodySize()))
	{
		delete[] m_pDibInfo;
		delete[] m_pDibBits;
		m_pDibInfo = NULL;
		m_pDibBits = NULL;
	}
	//�ر��ļ�
	bmpFile.Close();
}


void CMedicalImg::SaveDIB(CString dibName)
{
	//��DIBΪ������ʾ���󲢷���
	if (!m_pDibInfo)
	{
		AfxMessageBox(L"DIB��Ϣ�����ڣ�");
		return;
	}

	//ͨ���ļ�������CFile����
	//���ļ���ʧ������ʾ���󲢷���
	CFile file;
	if (!file.Open(dibName, CFile::modeCreate | CFile::modeReadWrite))
	{
		AfxMessageBox(L"�����ļ�ʧ�ܣ�");
		return;
	}

	//Bitmap�ļ�ͷ
	BITMAPFILEHEADER bmfileheader;

	long size = BytesPerline() * m_pDibInfo->bmiHeader.biHeight;
	int PaletteSize = GetPaletteCount();

	//��дBMP�ļ�������
	bmfileheader.bfType = 0x4d42;//���ͱ�ʾ"BM"
	bmfileheader.bfReserved1 = bmfileheader.bfReserved2 = 0;//������0
	bmfileheader.bfOffBits =
		sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ PaletteSize*sizeof(RGBQUAD);
	bmfileheader.bfSize = bmfileheader.bfOffBits + size;

	//���ļ�ͷ��λͼ��Ϣ����������д������ļ�
	file.Write(&bmfileheader, sizeof(BITMAPFILEHEADER));
	file.Write(m_pDibInfo, sizeof(BITMAPINFOHEADER) + PaletteSize*sizeof(RGBQUAD));
	file.Write(m_pDibBits, size);
	//�ر��ļ�
	file.Close();
}

int CMedicalImg::GetPixelRGB(int row, int col, int &r, int &g, int b)
{
	char *pDibBits = (char *)m_pDibBits;
	int index = (row - 1) * BytesPerline() + (col - 1) * GetBitsPerPixel();
	b = (int)(*(pDibBits + index + 0));
	g = (int)(*(pDibBits + index + 1));
	r = (int)(*(pDibBits + index + 2));

	return 0;
}

void CMedicalImg::UpdateRGB(char * imageBuffer, int deltaR, int deltaG, int deltaB)
{
	int index = 0;
	for (int i = 0; i < GetHeight(); i++)
	{
		for (int j = 0; j < GetWidth(); j++)
		{
			index = i * BytesPerline() + j * GetBitsPerPixel() / 8;
			imageBuffer[index] = abs((imageBuffer[index] + deltaB) % 255);
			imageBuffer[index + 1] = abs((imageBuffer[index + 1] + deltaG) %255);
			imageBuffer[index + 2] = abs((imageBuffer[index + 1] + deltaR) %255);
		}
	}
}
