
// libvlc_player_MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include <string>//std::string
#include "configs.h"//libvlc

#define MAX_URL_LENGTH 100

enum PlayerState {
	STATE_PREPARE,
	STATE_PLAY,
	STATE_PAUSE
};

// Clibvlc_player_MFCDlg �Ի���
class Clibvlc_player_MFCDlg : public CDialogEx
{
// ����
public:
	Clibvlc_player_MFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBVLC_PLAYER_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_url;

	libvlc_instance_t * libvlc_inst;
	libvlc_media_player_t *libvlc_mp;
	libvlc_media_t *libvlc_m;
	PlayerState playerState;

	afx_msg void OnBnClickedButtonUrl();
	afx_msg void OnBnClickedPlay();
	void UNICODE_to_UTF8(CStringW& unicodeString, std::string& str);
	void InitSystem();
	afx_msg void OnBnClickedButtonStop();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonPause();
	// ��ǰ����ʱ��
	CEdit m_curtime;
	// ��ʱ��
	CEdit m_totaltime;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// ������
	CScrollBar m_progress;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnFileOpen();
	afx_msg void OnCsdn();
	afx_msg void OnAbout();
	afx_msg void OnBnClickedButtonInfo();
};
