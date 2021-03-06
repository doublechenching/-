/*********************************************************************************************************
* 模块名称: PicControl
* 摘    要: 图片控件
* 当前版本: 1.0.0
* 作    者: 秦陈陈
* 完成日期: 2017/12/20
* 内    容:
* 注    意: none                                                                  
**********************************************************************************************************
* 取代版本: 
* 作    者:
* 完成日期: 
* 修改内容:
* 修改文件: 
*********************************************************************************************************/


/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "stdafx.h"
#include "Chapter1_LoadImg.h"
#include "PicControl.h"
#include "Chapter1_LoadImgDlg.h"


/*********************************************************************************************************
*                                              类成员函数实现
*********************************************************************************************************/
IMPLEMENT_DYNAMIC(CPicControl, CStatic)

CPicControl::CPicControl()
{

}

CPicControl::~CPicControl()
{
}

/*消息映射宏函数*/
BEGIN_MESSAGE_MAP(CPicControl, CStatic)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


/*********************************************************************************************************
* 函数名称:  CPicControl::OnMouseMove
* 权限    :  public 
* 函数功能:  
* 参数    :  UINT nFlags
* 参数    :  CPoint point
* 返回值  :  void
* 注意    :  
*********************************************************************************************************/
void CPicControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int x = point.x;
	int y = point.y;
	GetParent()->SendMessage(WM_SHOW_POS, x, y);
	CStatic::OnMouseMove(nFlags, point);
}
