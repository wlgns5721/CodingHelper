// TabTwo.cpp : 구현 파일입니다.
//
#pragma warning(disable: 4996)


#include "stdafx.h"
#include "Coding_Helper.h"
#include "TabTwo.h"
#include "afxdialogex.h"
#include <afxinet.h>
#include "json.h"
#include <cpprest/http_msg.h>
#include <cpprest/http_client.h>
#include <fstream>
#include <locale>
#include <vector>


#define NAVER_CLIENT_ID L"J2KGpBnh46nMRU7uRFnR";
#define NAVER_CLIENT_SECRET L"s_p06B5WLM";
using namespace web;
using namespace web::http;
using namespace web::http::client;



wstring ConvertCharToWstring(TCHAR *text);

CFont word_font;
CFont meaning_font;

// TabTwo 대화 상자입니다.

IMPLEMENT_DYNAMIC(TabTwo, CDialogEx)

TabTwo::TabTwo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUB2, pParent)
{

}

TabTwo::~TabTwo()
{
}

void TabTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listBox);
	DDX_Control(pDX, IDC_COMBO1, m_combo);

	DDX_Control(pDX, IDC_EDIT3, m_word);
	DDX_Control(pDX, IDC_EDIT2, m_explain);
}


BEGIN_MESSAGE_MAP(TabTwo, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_LIST2, &TabTwo::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON8, &TabTwo::OnBnClickedButton8)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// TabTwo 메시지 처리기입니다.


BOOL TabTwo::OnInitDialog()
{
	locale::global(locale("Korean"));
	
	CDialogEx::OnInitDialog();
	
	//폰트 설정을 한다.	
	word_font.CreateFont(40, 30, 0, 0, 1000, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, 0, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("굴림"));
	GetDlgItem(IDC_EDIT3)->SetFont(&word_font);

	meaning_font.CreateFont(15, 15, 0, 0, 1000, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, 0, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("굴림"));
	GetDlgItem(IDC_EDIT2)->SetFont(&meaning_font);

	m_combo.AddString(L"한 -> 영");
	m_combo.AddString(L"영 -> 한");
	m_combo.SetCurSel(0);

	SetDlgItemText(IDC_STATIC, L"");
	SetDlgItemText(IDC_BUTTON8, L"검색");
	m_explain.SetWindowTextW(L"");
	m_word.SetWindowTextW(L"");
	

	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

wstring ConvertCharToWstring(TCHAR* text) {
	char strUtf8[256] = { 0, };
	string convertedString = "";
	wstring convertedWstring;
	
	int nLen = WideCharToMultiByte(CP_UTF8, 0, text, lstrlenW(text), NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, text, lstrlenW(text), strUtf8, nLen, NULL, NULL);
	for (int i = 0; strUtf8[i] != NULL; i++) {
		char temp[10];
		sprintf(temp, "%%%x", (BYTE)strUtf8[i]);
		string str(temp);
		convertedString += str;
	}
	convertedWstring.assign(convertedString.begin(), convertedString.end());
	return convertedWstring;
}

//JSON 형식으로 받는다.
wstring TabTwo::GetDictionaryData(wstring phrase) {
	wstring url;
	wstring utf8_phrase = ConvertCharToWstring(W2T((wchar_t*)phrase.c_str()));
	
	if (m_combo.GetCurSel() == 0)     //한 -> 영으로 설정되어있을 경우
		url = L"https://glosbe.com/gapi/translate?from=kor&dest=eng&format=json&pretty=true&phrase=";
	else      //영 -> 한으로 설정되어있을 경우
		url = L"https://glosbe.com/gapi/translate?from=eng&dest=kor&format=json&pretty=true&phrase=";
	http_client client(url + utf8_phrase);
	http_request request(methods::GET);
	request.headers().set_content_type(L"application/json");
	http_response response = client.request(request).get();
	if (response.status_code() == status_codes::OK) {
		wstring str = response.extract_string().get();
		return str;
	}
	else
		return L"";
	/*
	client.request(request).then([](http_response response) {
		
		
		wstring str = response.extract_string().get();
	});*/
}

//배경을 설정하는 함수
BOOL TabTwo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));
	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH TabTwo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor) {
	case CTLCOLOR_STATIC: {
		CBrush m_brush;
		m_brush.CreateSolidBrush(RGB(0, 0, 0));	
		pDC->SetBkColor(RGB(255, 255, 255));
		return m_brush;
	 }
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void TabTwo::SetPhraseInformation(int index) {
	CClientDC dc(this);
	dc.SelectObject(meaning_font);
	CSize width;
	CRect rect;
	
	GetDlgItem(IDC_EDIT2)->GetClientRect(rect);
	int text_width = width.cx;
	int control_width = rect.Width();
	wstring wstr = L"";
	TCHAR temp[2];
	memset(temp, '\0', sizeof(temp));
	
	for (int s = 0; s < dictionary_vec[index].meaning_vec.size(); s++) {
		TCHAR* meaning = W2T((wchar_t*)dictionary_vec[index].meaning_vec[s].c_str());
		int text_size = wcslen(meaning);
		int sum = 0;
		wstr += to_wstring(s + 1);
		wstr += L". ";
		wstr += dictionary_vec[index].meaning_vec[s];
		/*sum += dc.GetTextExtent(L"xxx").cx;
		for (int i = 0; i < text_size; i++) {
			*temp = *(meaning + i);
			width = dc.GetTextExtent(temp);
			sum += width.cx;
			if (sum > control_width) {
				wstr += L"\r\n";
				sum = width.cx;
			}
			wstr += meaning[i];
		}*/
		
		wstr += L"\r\n\r\n";
		
	}
	m_explain.SetWindowTextW(wstr.c_str());
	m_word.SetWindowTextW(dictionary_vec[index].phrase.c_str());
}

void TabTwo::ParsingData(wstring jsonData) {
	wstring remainedData = jsonData;
	while (true) {
		int phrase_index = remainedData.find(L"\"phrase\" : ");  //"text" : " 의 인덱스를 찾는다.
		wstring temp = remainedData.substr(phrase_index+1);
		int block_end_index = temp.find(L"\"phrase\" : ");
		wstring block;
		bool phrase_flag = true;

		if (phrase_index == wstring::npos)
			return;

		if (block_end_index == wstring::npos)
			return;
		else {
			block_end_index += 1;
			block = remainedData.substr(phrase_index, block_end_index);
		}
		
		while (true) {
			int text_index = block.find(L"\"text\" : \"");
			if (text_index == wstring::npos)
				break;

			wstring subblock = block.substr(text_index + 10);
			int quotes_index = subblock.find(L"\""); //다음 "가 시작하는 인덱스를 찾는다.
			wstring text = subblock.substr(0, quotes_index);
			block = subblock.substr(quotes_index);  //원하는 부분을

			if (phrase_flag == true) {
				phrase_flag = false;
				ParsedData parsedData;
				parsedData.phrase = text;
				dictionary_vec.push_back(parsedData);
				continue;
			}

			dictionary_vec[dictionary_vec.size() - 1].meaning_vec.push_back(text);
		}
		
		//남은 텍스트로 계속 파싱을 진행한다.
		remainedData = remainedData.substr(phrase_index + block_end_index);

	}
}

void TabTwo::OnLbnSelchangeList2()
{	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = listBox.GetCurSel();
	SetPhraseInformation(index);
	Invalidate(false);
}


void TabTwo::OnBnClickedButton8()
{
	GetDictionaryData();
}


void TabTwo::GetDictionaryData() {
	//사전 정보를 얻어온다.
	CString CText;
	GetDlgItemText(IDC_EDIT1, CText);
	wstring phrase(CText);

	//이전 정보를 제거한다.
	dictionary_vec.clear();
	listBox.ResetContent();

	wstring jsonData = GetDictionaryData(phrase);
	if (jsonData.compare(L"") == 0)
		return;
	//json으로 받아온 값을 파싱한다.
	ParsingData(jsonData);

	//phrase들을 삽입한다.
	for (int i = 0; i < dictionary_vec.size(); i++)
		listBox.AddString(dictionary_vec[i].phrase.c_str());
	if (dictionary_vec.empty()) {
		m_word.SetWindowTextW(L"검색 결과가 없습니다.");
		m_explain.SetWindowTextW(L"");
	}
	else
		SetPhraseInformation(0);  	//제일 첫번째로 나오는 단어 및 뜻을 보여준다.

	
}



BOOL TabTwo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			GetDictionaryData();
			return TRUE;                // Do not process further
		}
		else if (pMsg->wParam == VK_ESCAPE) {
			return TRUE;
		}
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


