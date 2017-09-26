
// libvlc_player_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "libvlc_player_MFC.h"
#include "libvlc_player_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Clibvlc_player_MFCDlg �Ի���



Clibvlc_player_MFCDlg::Clibvlc_player_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LIBVLC_PLAYER_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clibvlc_player_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_URL, m_url);
	DDX_Control(pDX, IDC_EDIT_CURRENT, m_curtime);
	DDX_Control(pDX, IDC_EDIT_TOTAL, m_totaltime);
	DDX_Control(pDX, IDC_SCROLLBAR, m_progress);
}

BEGIN_MESSAGE_MAP(Clibvlc_player_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_URL, &Clibvlc_player_MFCDlg::OnBnClickedButtonUrl)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &Clibvlc_player_MFCDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &Clibvlc_player_MFCDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &Clibvlc_player_MFCDlg::OnBnClickedButtonPause)
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_WM_DROPFILES()
	ON_COMMAND(ID_OPEN, &Clibvlc_player_MFCDlg::OnFileOpen)
	ON_COMMAND(ID_CSDN, &Clibvlc_player_MFCDlg::OnCsdn)
	ON_COMMAND(ID_ABOUT, &Clibvlc_player_MFCDlg::OnAbout)
	ON_BN_CLICKED(IDC_INFO, &Clibvlc_player_MFCDlg::OnBnClickedButtonInfo)
END_MESSAGE_MAP()


// Clibvlc_player_MFCDlg ��Ϣ�������

BOOL Clibvlc_player_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// Load the VLC engine
	libvlc_inst = libvlc_new(0, NULL);
	//���ý�������Χ
	m_progress.SetScrollRange(0, 100);
	//ϵͳ����
	InitSystem();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Clibvlc_player_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Clibvlc_player_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Clibvlc_player_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clibvlc_player_MFCDlg::OnBnClickedButtonUrl()
{
	CString FilePathName;
	//Filter String
	CString strfilter;
	strfilter.Append(_T("Common media formats|*.avi;*.wmv;*.wmp;*.wm;*.asf;*.rm;*.ram;*.rmvb;*.ra;*.mpg;*.mpeg;*.mpe;*.m1v;*.m2v;*.mpv2;"));
	strfilter.Append(_T("*.mp2v;*.dat;*.mp4;*.m4v;*.m4p;*.vob;*.ac3;*.dts;*.mov;*.qt;*.mr;*.3gp;*.3gpp;*.3g2;*.3gp2;*.swf;*.ogg;*.wma;*.wav;"));
	strfilter.Append(_T("*.mid;*.midi;*.mpa;*.mp2;*.mp3;*.m1a;*.m2a;*.m4a;*.aac;*.mkv;*.ogm;*.m4b;*.tp;*.ts;*.tpr;*.pva;*.pss;*.wv;*.m2ts;*.evo;"));
	strfilter.Append(_T("*.rpm;*.realpix;*.rt;*.smi;*.smil;*.scm;*.aif;*.aiff;*.aifc;*.amr;*.amv;*.au;*.acc;*.dsa;*.dsm;*.dsv;*.dss;*.pmp;*.smk;*.flic|"));
	strfilter.Append(_T("Windows Media Video(*.avi;*wmv;*wmp;*wm;*asf)|*.avi;*.wmv;*.wmp;*.wm;*.asf|"));
	strfilter.Append(_T("Windows Media Audio(*.wma;*wav;*aif;*aifc;*aiff;*mid;*midi;*rmi)|*.wma;*.wav;*.aif;*.aifc;*.aiff;*.mid;*.midi;*.rmi|"));
	strfilter.Append(_T("Real(*.rm;*ram;*rmvb;*rpm;*ra;*rt;*rp;*smi;*smil;*.scm)|*.rm;*.ram;*.rmvb;*.rpm;*.ra;*.rt;*.rp;*.smi;*.smil;*.scm|"));
	strfilter.Append(_T("MPEG Video(*.mpg;*mpeg;*mpe;*m1v;*m2v;*mpv2;*mp2v;*dat;*mp4;*m4v;*m4p;*m4b;*ts;*tp;*tpr;*pva;*pss;*.wv;)|"));
	strfilter.Append(_T("*.mpg;*.mpeg;*.mpe;*.m1v;*.m2v;*.mpv2;*.mp2v;*.dat;*.mp4;*.m4v;*.m4p;*.m4b;*.ts;*.tp;*.tpr;*.pva;*.pss;*.wv;|"));
	strfilter.Append(_T("MPEG Audio(*.mpa;*mp2;*m1a;*m2a;*m4a;*aac;*.m2ts;*.evo)|*.mpa;*.mp2;*.m1a;*.m2a;*.m4a;*.aac;*.m2ts;*.evo|"));
	strfilter.Append(_T("DVD(*.vob;*ifo;*ac3;*dts)|*.vob;*.ifo;*.ac3;*.dts|MP3(*.mp3)|*.mp3|CD Tracks(*.cda)|*.cda|"));
	strfilter.Append(_T("Quicktime(*.mov;*qt;*mr;*3gp;*3gpp;*3g2;*3gp2)|*.mov;*.qt;*.mr;*.3gp;*.3gpp;*.3g2;*.3gp2|"));
	strfilter.Append(_T("Flash Files(*.flv;*swf;*.f4v)|*.flv;*.swf;*.f4v|Playlist(*.smpl;*.asx;*m3u;*pls;*wvx;*wax;*wmx;*mpcpl)|*.smpl;*.asx;*.m3u;*.pls;*.wvx;*.wax;*.wmx;*.mpcpl|"));
	strfilter.Append(_T("Others(*.ivf;*au;*snd;*ogm;*ogg;*fli;*flc;*flic;*d2v;*mkv;*pmp;*mka;*smk;*bik;*ratdvd;*roq;*drc;*dsm;*dsv;*dsa;*dss;*mpc;*divx;*vp6;*.ape;*.flac;*.tta;*.csf)"));
	strfilter.Append(_T("|*.ivf;*.au;*.snd;*.ogm;*.ogg;*.fli;*.flc;*.flic;*.d2v;*.mkv;*.pmp;*.mka;*.smk;*.bik;*.ratdvd;*.roq;*.drc;*.dsm;*.dsv;*.dsa;*.dss;*.mpc;*.divx;*.vp6;*.ape;*.amr;*.flac;*.tta;*.csf|"));
	strfilter.Append(_T("All Files(*.*)|*.*||"));

	LPCTSTR lpszfilter = strfilter;
	CFileDialog dlg(TRUE, NULL, NULL, NULL, lpszfilter);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի��� 
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();
		m_url.SetWindowText(FilePathName);
	}
}


void Clibvlc_player_MFCDlg::OnBnClickedPlay()
{
	CStringW cstr_url;

#ifdef _UNICODE
	m_url.GetWindowText(cstr_url);
#else
	USES_CONVERSION;
	CStringA cstr_urla;
	m_url.GetWindowText(cstr_urla);
	cstr_url.Format(L"%s", A2W(cstr_urla));
#endif

	std::string str_url;
	UNICODE_to_UTF8(cstr_url, str_url);
	const char *char_url = str_url.c_str();

	if (strcmp(char_url, "") == 0)
	{
		AfxMessageBox(_T("Input URL is NULL!"));
		return;
	}

	HWND screen_hwnd = NULL;
	screen_hwnd = this->GetDlgItem(IDC_PICTURE)->m_hWnd;

	if (playerState != STATE_PREPARE) 
	{
		AfxMessageBox(_T("��Ƶ���ڲ�����"));
		return;
	}


	//Create a new item
	//���������ַ����������Ϊ�Լ��ڱ��ش�ĵ㲥��rtmp�������㲥��ַ������ڵ��Գ���ʱ���Ը�Ϊ�������õ����粥�ŵ�ַ��
	//libvlc_m = libvlc_media_new_location (libvlc_inst, "rtmp://192.168.154.203:1935/vod/sample.mp4");

	//���ű�����Ƶ�ļ���
	libvlc_m = libvlc_media_new_path(libvlc_inst, char_url);

	/* Create a media player playing environement */
	libvlc_mp = libvlc_media_player_new_from_media(libvlc_m);

	/* No need to keep the media now */
	libvlc_media_release(libvlc_m);

	//on windows
	libvlc_media_player_set_hwnd(libvlc_mp, screen_hwnd);

	/* play the media_player */
	libvlc_media_player_play(libvlc_mp);

	SetTimer(1, 1000, NULL);
	playerState = STATE_PLAY;

}


void Clibvlc_player_MFCDlg::UNICODE_to_UTF8(CStringW& unicodeString, std::string& str)
{
	int stringLength = ::WideCharToMultiByte(CP_UTF8, NULL, unicodeString, wcslen(unicodeString), NULL, 0, NULL, NULL);

	char* buffer = new char[stringLength + 1];
	::WideCharToMultiByte(CP_UTF8, NULL, unicodeString, wcslen(unicodeString), buffer, stringLength, NULL, NULL);
	buffer[stringLength] = '\0';

	str = buffer;

	delete[] buffer;
}


void Clibvlc_player_MFCDlg::InitSystem()
{
	libvlc_mp = NULL;
	libvlc_m = NULL;
	m_curtime.SetWindowText(_T("00:00:00"));
	m_totaltime.SetWindowText(_T("00:00:00"));
	m_progress.SetScrollPos(0);
	playerState = STATE_PREPARE;
}


void Clibvlc_player_MFCDlg::OnBnClickedButtonStop()
{
	if (libvlc_mp != NULL) 
	{
		//Stop playing
		libvlc_media_player_stop(libvlc_mp);
		//Free the media_player
		libvlc_media_player_release(libvlc_mp);
		//�رն�ʱ��
		KillTimer(1);
		//ϵͳ����
		InitSystem();
	}	
}


BOOL Clibvlc_player_MFCDlg::DestroyWindow()
{
	/* Free the media_player */
	libvlc_release(libvlc_inst);
	return CDialogEx::DestroyWindow();
}


void Clibvlc_player_MFCDlg::OnBnClickedButtonPause()
{
	if (playerState == STATE_PLAY) {
		libvlc_media_player_set_pause(libvlc_mp, 1);//��ͣ
		playerState = STATE_PAUSE;
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("����"));
	}
	else if (playerState == STATE_PAUSE) {
		libvlc_media_player_set_pause(libvlc_mp, 0);//����
		playerState = STATE_PLAY;
		GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("��ͣ"));
	}
}


void Clibvlc_player_MFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		CString curtimestr, durationstr;
		int curtime;
		int duration;
		int tns, thh, tmm, tss;
		int progress;
		//ms
		curtime = (int)(libvlc_media_player_get_time(libvlc_mp));
		if (curtime != 0) 
		{
			//change to second
			tns = curtime / 1000;
			thh = tns / 3600;
			tmm = (tns % 3600) / 60;
			tss = (tns % 60);
			curtimestr.Format(_T("%02d:%02d:%02d"), thh, tmm, tss);
			m_curtime.SetWindowText(curtimestr);
		}
		duration = (int)(libvlc_media_player_get_length(libvlc_mp));
		if (duration != 0) 
		{
			//change to second
			tns = duration / 1000;
			thh = tns / 3600;
			tmm = (tns % 3600) / 60;
			tss = (tns % 60);
			durationstr.Format(_T("%02d:%02d:%02d"), thh, tmm, tss);
			m_totaltime.SetWindowText(durationstr);

			progress = curtime * 100 / duration;
			m_progress.SetScrollPos(progress);
		}
	}

	//Stop in the end
	if (libvlc_media_player_get_state(libvlc_mp) == libvlc_Ended)
		OnBnClickedButtonStop();
	CDialogEx::OnTimer(nIDEvent);
}

void Clibvlc_player_MFCDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (playerState == STATE_PLAY)
	{
		int curpos = pScrollBar->GetScrollPos();//��ȡ��ǰλ��
		float f_pos = 0.0;//�ļ�����λ�ã���Χ0.0-1.0
		switch (nSBCode)
		{
			// ����������һ�У���pos��1   
			case SB_LINEUP:
				if (curpos > 0)
				curpos -= 1;
				break;
			// ������ҹ���һ�У���pos��1   
			case SB_LINEDOWN:
				curpos += 1;
				break;
			// ����������һҳ����pos��10   
			case SB_PAGEUP:
				curpos -= 10;
				break;
			// ������ҹ���һҳ����pos��10   
			case SB_PAGEDOWN:
				curpos += 10;
				break;
			case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
				curpos = nPos;// of the scroll box at the end of the drag operation.
				break;

			case SB_THUMBTRACK:// Drag scroll box to specified position. nPos is the
				curpos = nPos;// position that the scroll box has been dragged to.
				break;
		}
		if (curpos > 100)
		{
			curpos = 100;
		}
		else if (curpos < 0)
		{
			curpos = 0;
		}
		pScrollBar->SetScrollPos(curpos);//����λ��
		f_pos = (float)(curpos / 100.0);
		libvlc_media_player_set_position(libvlc_mp, f_pos);//�����ļ�����λ��
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void Clibvlc_player_MFCDlg::OnDropFiles(HDROP hDropInfo)
{
	LPTSTR pFilePathName = (LPTSTR)malloc(MAX_URL_LENGTH);
	::DragQueryFile(hDropInfo, 0, pFilePathName, MAX_URL_LENGTH);//��ȡ�Ϸ��ļ��������ļ���
	m_url.SetWindowText(pFilePathName);
	::DragFinish(hDropInfo);   //�ͷ�WindowsΪ�����ļ��ϷŶ�������ڴ�
	free(pFilePathName);
	CDialogEx::OnDropFiles(hDropInfo);
}

void Clibvlc_player_MFCDlg::OnFileOpen()
{
	OnBnClickedButtonUrl();
}


void Clibvlc_player_MFCDlg::OnCsdn()
{
	ShellExecuteA(NULL, "open", "http://blog.csdn.net/zhuyinglong2010", NULL, NULL, SW_SHOWNORMAL);
}


void Clibvlc_player_MFCDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


void Clibvlc_player_MFCDlg::OnBnClickedButtonInfo()
{
	if (playerState == STATE_PLAY)
	{
		CString infostr;
		infostr.AppendFormat(_T("========��Ƶ��Ϣ========\r\n"));
		unsigned video_w = 0, video_h = 0;
		float framerate = 0;
		libvlc_video_get_size(libvlc_mp, 0, &video_w, &video_h);
		framerate = libvlc_media_player_get_fps(libvlc_mp);
		infostr.AppendFormat(_T("Video Width:%d\r\nVideo Height:%d\r\nVideo Framerate:%f\r\n")
			, video_w, video_h, framerate);

		infostr.AppendFormat(_T("========��Ƶ��Ϣ========\r\n"));
		int channel = 0;
		channel = libvlc_audio_get_channel(libvlc_mp);
		infostr.AppendFormat(_T("Audio Channels:%d\r\n"), channel);

		AfxMessageBox(infostr, MB_ICONINFORMATION);
	}
}
