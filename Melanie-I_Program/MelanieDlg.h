// MelanieDlg.h : header file
//

#if !defined(AFX_MELANIEDLG_H__F4E083A6_6F9E_11D8_B526_DD03F61C585C__INCLUDED_)
#define AFX_MELANIEDLG_H__F4E083A6_6F9E_11D8_B526_DD03F61C585C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "serialport.h"			//Use Serial Port Libraries


/////////////////////////////////////////////////////////////////////////////
// CMelanieDlg dialog

class CMelanieDlg : public CDialog
{
// Construction
private:
	void DecToHex(int DecNumber, char *Hex);
	void SendCommand (CString sCommand);
		 CSerialPort port;
public:
	void RunPreset (CString FileName);
	unsigned char cSpeed (unsigned char cServo);
	char cHex[3];
	CMelanieDlg(CWnd* pParent = NULL);	// standard constructor
	~CMelanieDlg();

// Dialog Data
	//{{AFX_DATA(CMelanieDlg)
	enum { IDD = IDD_MELANIE_DIALOG };
	int		m_SliderServo01;
	int		m_SliderServo02;
	int		m_SliderServo03;
	int		m_SliderServo04;
	int		m_SliderServo05;
	int		m_SliderServo06;
	int		m_SliderServo07;
	int		m_SliderServo08;
	int		m_SliderServo09;
	int		m_SliderServo10;
	int		m_SliderServo11;
	int		m_SliderServo12;
	int		m_SliderServo13;
	int		m_SliderServo14;
	int		m_SliderServo15;
	int		m_SliderServo16;
	int		m_SliderServo17;
	int		m_SliderServo18;
	int		m_SliderServo19;
	int		m_pos01;
	int		m_pos02;
	int		m_pos03;
	int		m_pos04;
	int		m_pos05;
	int		m_pos06;
	int		m_pos07;
	int		m_pos08;
	int		m_pos09;
	int		m_pos10;
	int		m_pos11;
	int		m_pos12;
	int		m_pos13;
	int		m_pos14;
	int		m_pos15;
	int		m_pos16;
	int		m_pos17;
	int		m_pos18;
	int		m_pos19;
	BYTE	m_pause;
	CString	m_seqname;
	BOOL	m_switch;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMelanieDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

private:
	//Structure for the sequence of positions of the robot
	struct	stPosition							//Define Position of Robot
	{
		unsigned char		cServoPos[21],		//Define position of up to 20 servos
							cPause;				//Pause after this position
		struct stPosition	*nextpos,			//Used for linked list
							*prevpos;

	};
	struct	stPosition	*pstFirstPos,			//First global position
						*pstActualPos,			//Actual global position
						*pstPrevPos;

// Implementation
protected:
	void LoadSequence(CString FileName);
	void CreateSequence();
	int temp;
	void SetGlobalPos();
	void SetServoPos (CString cServo, int iPosition, int iSpeed);
	void ActivateServo(CString cServo, unsigned char cPos);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMelanieDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCustomdrawSliderservo01(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo02(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo03(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo04(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo05(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo06(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo07(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo08(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo09(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo10(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo11(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo12(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo13(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo14(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo15(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo16(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo17(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo18(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderservo19(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSavepos();
	afx_msg void OnSaveseq();
	afx_msg void OnTopback();
	afx_msg void OnTopforward();
	afx_msg void OnStepforward();
	afx_msg void OnAllforward();
	afx_msg void OnClearseq();
	afx_msg void OnStepback();
	afx_msg void OnAllback();
	afx_msg void OnLoadseq();
	afx_msg void OnLoadOverSeq();
	afx_msg void OnSwitch();
	afx_msg void OnSaveinvseq();
	afx_msg void OnPreset1();
	afx_msg void OnPreset2();
	afx_msg void OnPreset6();
	afx_msg void OnPreset3();
	afx_msg void OnPreset10();
	afx_msg void OnPreset4();
	afx_msg void OnPreset8();
	afx_msg void OnPreset9();
	afx_msg void OnPreset5();
	afx_msg void OnPreset7();
	afx_msg void OnPreset11();
	afx_msg void OnPresetset1();
	afx_msg void OnPreset12();
	afx_msg void OnPresetset2();
	afx_msg void OnPreset13();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MELANIEDLG_H__F4E083A6_6F9E_11D8_B526_DD03F61C585C__INCLUDED_)
