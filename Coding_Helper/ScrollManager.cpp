#include "stdafx.h"
#include "ScrollManager.h"
void ScrollManager::InitScroll() {
		m_ctrVScroll.SetScrollRange(0, 100);
		m_ctrVScroll.SetScrollPos(50);

		SCROLLINFO scroll_info;
		scroll_info.cbSize = sizeof(scroll_info);
		scroll_info.fMask = SIF_ALL;
		scroll_info.nMin = 0;
		scroll_info.nMax = 100;
		scroll_info.nPage = 10;  //������ ���� ������
		scroll_info.nTrackPos = 0;    //Ʈ���ٰ� ������ ���� ��ġ��
		scroll_info.nPos = 50;
		m_ctrVScroll.SetScrollInfo(&scroll_info);
		
}
