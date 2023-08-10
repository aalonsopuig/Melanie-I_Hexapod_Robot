// MelanieDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Melanie.h"
#include "MelanieDlg.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Servo hexadecimal references as connected in MSCC20 module
#define SERVO01	"06"
#define SERVO02	"05"
#define SERVO03	"09"
#define SERVO04	"0D"
#define SERVO05	"10"
#define SERVO06	"0A"
#define SERVO07	"0F"
#define SERVO08	"0E"
#define SERVO09	"0C"
#define SERVO10	"12"
#define SERVO11	"03"
#define SERVO12	"04"
#define SERVO13	"08"
#define SERVO14	"00"
#define SERVO15	"01"
#define SERVO16	"07"
#define SERVO17	"11"
#define SERVO18	"0B"
#define SERVO19	"02"
#define SERVO20	"13"


/////////////////////////////////////////////////////////////////////////////
// CMelanieDlg dialog

CMelanieDlg::CMelanieDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMelanieDlg::IDD, pParent)
{
	//Initialize sequence of positions
	CreateSequence();


	//{{AFX_DATA_INIT(CMelanieDlg)
	m_SliderServo01 = 0;
	m_SliderServo02 = 0;
	m_SliderServo03 = 0;
	m_SliderServo04 = 0;
	m_SliderServo05 = 0;
	m_SliderServo06 = 0;
	m_SliderServo07 = 0;
	m_SliderServo08 = 0;
	m_SliderServo09 = 0;
	m_SliderServo10 = 0;
	m_SliderServo11 = 0;
	m_SliderServo12 = 0;
	m_SliderServo13 = 0;
	m_SliderServo14 = 0;
	m_SliderServo15 = 0;
	m_SliderServo16 = 0;
	m_SliderServo17 = 0;
	m_SliderServo18 = 0;
	m_SliderServo19 = 0;
	m_pos01 = 0;
	m_pos02 = 0;
	m_pos03 = 0;
	m_pos04 = 0;
	m_pos05 = 0;
	m_pos06 = 0;
	m_pos07 = 0;
	m_pos08 = 0;
	m_pos09 = 0;
	m_pos10 = 0;
	m_pos11 = 0;
	m_pos12 = 0;
	m_pos13 = 0;
	m_pos14 = 0;
	m_pos15 = 0;
	m_pos16 = 0;
	m_pos17 = 0;
	m_pos18 = 0;
	m_pos19 = 0;
	m_pause = 80;
	m_seqname = _T("seqfile.txt");
	m_switch = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	port.Open(1, 9600, CSerialPort::NoParity, 8, CSerialPort::OneStopBit, CSerialPort::NoFlowControl);	

}

CMelanieDlg::~CMelanieDlg()
// Destructor
{
	delete(pstFirstPos);	//Free memory previously used
	port.Close();			//Close Serial Port

}

void CMelanieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMelanieDlg)
	DDX_Slider(pDX, IDC_SLIDERSERVO01, m_SliderServo01);
	DDX_Slider(pDX, IDC_SLIDERSERVO02, m_SliderServo02);
	DDX_Slider(pDX, IDC_SLIDERSERVO03, m_SliderServo03);
	DDX_Slider(pDX, IDC_SLIDERSERVO04, m_SliderServo04);
	DDX_Slider(pDX, IDC_SLIDERSERVO05, m_SliderServo05);
	DDX_Slider(pDX, IDC_SLIDERSERVO06, m_SliderServo06);
	DDX_Slider(pDX, IDC_SLIDERSERVO07, m_SliderServo07);
	DDX_Slider(pDX, IDC_SLIDERSERVO08, m_SliderServo08);
	DDX_Slider(pDX, IDC_SLIDERSERVO09, m_SliderServo09);
	DDX_Slider(pDX, IDC_SLIDERSERVO10, m_SliderServo10);
	DDX_Slider(pDX, IDC_SLIDERSERVO11, m_SliderServo11);
	DDX_Slider(pDX, IDC_SLIDERSERVO12, m_SliderServo12);
	DDX_Slider(pDX, IDC_SLIDERSERVO13, m_SliderServo13);
	DDX_Slider(pDX, IDC_SLIDERSERVO14, m_SliderServo14);
	DDX_Slider(pDX, IDC_SLIDERSERVO15, m_SliderServo15);
	DDX_Slider(pDX, IDC_SLIDERSERVO16, m_SliderServo16);
	DDX_Slider(pDX, IDC_SLIDERSERVO17, m_SliderServo17);
	DDX_Slider(pDX, IDC_SLIDERSERVO18, m_SliderServo18);
	DDX_Slider(pDX, IDC_SLIDERSERVO19, m_SliderServo19);
	DDX_Text(pDX, IDC_POS01, m_pos01);
	DDX_Text(pDX, IDC_POS02, m_pos02);
	DDX_Text(pDX, IDC_POS03, m_pos03);
	DDX_Text(pDX, IDC_POS04, m_pos04);
	DDX_Text(pDX, IDC_POS05, m_pos05);
	DDX_Text(pDX, IDC_POS06, m_pos06);
	DDX_Text(pDX, IDC_POS07, m_pos07);
	DDX_Text(pDX, IDC_POS08, m_pos08);
	DDX_Text(pDX, IDC_POS09, m_pos09);
	DDX_Text(pDX, IDC_POS10, m_pos10);
	DDX_Text(pDX, IDC_POS11, m_pos11);
	DDX_Text(pDX, IDC_POS12, m_pos12);
	DDX_Text(pDX, IDC_POS13, m_pos13);
	DDX_Text(pDX, IDC_POS14, m_pos14);
	DDX_Text(pDX, IDC_POS15, m_pos15);
	DDX_Text(pDX, IDC_POS16, m_pos16);
	DDX_Text(pDX, IDC_POS17, m_pos17);
	DDX_Text(pDX, IDC_POS18, m_pos18);
	DDX_Text(pDX, IDC_POS19, m_pos19);
	DDX_Text(pDX, IDC_PAUSE, m_pause);
	DDX_Text(pDX, IDC_SEQNAME, m_seqname);
	DDX_Check(pDX, IDC_SWITCH, m_switch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMelanieDlg, CDialog)
	//{{AFX_MSG_MAP(CMelanieDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO01, OnCustomdrawSliderservo01)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO02, OnCustomdrawSliderservo02)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO03, OnCustomdrawSliderservo03)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO04, OnCustomdrawSliderservo04)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO05, OnCustomdrawSliderservo05)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO06, OnCustomdrawSliderservo06)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO07, OnCustomdrawSliderservo07)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO08, OnCustomdrawSliderservo08)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO09, OnCustomdrawSliderservo09)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO10, OnCustomdrawSliderservo10)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO11, OnCustomdrawSliderservo11)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO12, OnCustomdrawSliderservo12)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO13, OnCustomdrawSliderservo13)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO14, OnCustomdrawSliderservo14)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO15, OnCustomdrawSliderservo15)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO16, OnCustomdrawSliderservo16)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO17, OnCustomdrawSliderservo17)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO18, OnCustomdrawSliderservo18)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO19, OnCustomdrawSliderservo19)
	ON_BN_CLICKED(IDC_SAVEPOS, OnSavepos)
	ON_BN_CLICKED(IDC_SAVESEQ, OnSaveseq)
	ON_BN_CLICKED(IDC_TOPBACK, OnTopback)
	ON_BN_CLICKED(IDC_TOPFORWARD, OnTopforward)
	ON_BN_CLICKED(IDC_STEPFORWARD, OnStepforward)
	ON_BN_CLICKED(IDC_ALLFORWARD, OnAllforward)
	ON_BN_CLICKED(IDC_CLEARSEQ, OnClearseq)
	ON_BN_CLICKED(IDC_STEPBACK, OnStepback)
	ON_BN_CLICKED(IDC_ALLBACK, OnAllback)
	ON_BN_CLICKED(IDC_LOADSEQ, OnLoadseq)
	ON_BN_CLICKED(IDC_LOADOVERSEQ, OnLoadOverSeq)
	ON_BN_CLICKED(IDC_SWITCH, OnSwitch)
	ON_BN_CLICKED(IDC_SAVEINVSEQ, OnSaveinvseq)
	ON_BN_CLICKED(IDC_PRESET1, OnPreset1)
	ON_BN_CLICKED(IDC_PRESET2, OnPreset2)
	ON_BN_CLICKED(IDC_PRESET6, OnPreset6)
	ON_BN_CLICKED(IDC_PRESET3, OnPreset3)
	ON_BN_CLICKED(IDC_PRESET10, OnPreset10)
	ON_BN_CLICKED(IDC_PRESET4, OnPreset4)
	ON_BN_CLICKED(IDC_PRESET8, OnPreset8)
	ON_BN_CLICKED(IDC_PRESET9, OnPreset9)
	ON_BN_CLICKED(IDC_PRESET5, OnPreset5)
	ON_BN_CLICKED(IDC_PRESET7, OnPreset7)
	ON_BN_CLICKED(IDC_PRESET11, OnPreset11)
	ON_BN_CLICKED(IDC_PRESETSET1, OnPresetset1)
	ON_BN_CLICKED(IDC_PRESET12, OnPreset12)
	ON_BN_CLICKED(IDC_PRESETSET2, OnPresetset2)
	ON_BN_CLICKED(IDC_PRESET13, OnPreset13)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMelanieDlg message handlers

BOOL CMelanieDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMelanieDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

HCURSOR CMelanieDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMelanieDlg::DecToHex(int DecNumber, char *Hex)
//	Conversion of decimal number (0...255) to hexadecimal string (2 digits).
{
	itoa(DecNumber / 16, Hex, 16);			//MSD = dec. number / 16
	itoa(DecNumber % 16, Hex+1, 16);		//LSD = remainder dec number / 16
}

void CMelanieDlg::SendCommand(CString sCommand)
{
	CString	cr=13, lf=10;	//Carriage Return, Line Feed
	port.Write(sCommand, strlen(sCommand));
	port.Write(cr, 1);
	port.Write(lf, 1);
	port.Flush();
//	Sleep(10);
}






void CMelanieDlg::SetServoPos(CString cServo, int iPosition, int iSpeed=2)
// Move a servo to a specified position at a specified speed  
// by sending the adecuate information via RS232 to MSCC20 module
{
	if (m_switch) 
	{
		if (iSpeed==0) iSpeed=1;
	 	DecToHex(iPosition, cHex);
		port.Write("M", 1);
		port.Write(cServo, 2);
		port.Write(cHex, 2);
	 	DecToHex(iSpeed, cHex);
		SendCommand(cHex);
	}
}

void CMelanieDlg::ActivateServo(CString cServo, unsigned char cPos)
// Activate a servo by sending the 
// adecuate information via RS232 to MSCC20 module
{
	port.Write("SE", 2);
	SendCommand(cServo);
	SetServoPos(cServo,cPos,255);
}


void CMelanieDlg::OnCustomdrawSliderservo01(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos01=250-(m_SliderServo01*250/100);
	SetServoPos(SERVO01,m_pos01);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo02(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos02=(m_SliderServo02*250/100);
	SetServoPos(SERVO02,m_pos02);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo03(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos03=250-(m_SliderServo03*250/100);
	SetServoPos(SERVO03,m_pos03);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo04(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos04=250-(m_SliderServo04*250/100);
	SetServoPos(SERVO04,m_pos04);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo05(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos05=(m_SliderServo05*250/100);
	SetServoPos(SERVO05,m_pos05);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo06(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos06=250-(m_SliderServo06*250/100);
	SetServoPos(SERVO06,m_pos06);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo07(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos07=250-(m_SliderServo07*250/100);
	SetServoPos(SERVO07,m_pos07);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo08(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos08=(m_SliderServo08*250/100);
	SetServoPos(SERVO08,m_pos08);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo09(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos09=250-(m_SliderServo09*250/100);
	SetServoPos(SERVO09,m_pos09);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo10(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos10=(m_SliderServo10*250/100);
	SetServoPos(SERVO10,m_pos10);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo11(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos11=(m_SliderServo11*250/100);
	SetServoPos(SERVO11,m_pos11);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo12(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos12=250-(m_SliderServo12*250/100);
	SetServoPos(SERVO12,m_pos12);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo13(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos13=(m_SliderServo13*250/100);
	SetServoPos(SERVO13,m_pos13);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo14(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos14=(m_SliderServo14*250/100);
	SetServoPos(SERVO14,m_pos14);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo15(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos15=250-(m_SliderServo15*250/100);
	SetServoPos(SERVO15,m_pos15);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo16(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos16=(m_SliderServo16*250/100);
	SetServoPos(SERVO16,m_pos16);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo17(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos17=(m_SliderServo17*250/100);
	SetServoPos(SERVO17,m_pos17);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo18(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos18=250-(m_SliderServo18*250/100);
	SetServoPos(SERVO18,m_pos18);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo19(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos19=(m_SliderServo19*250/100);
	SetServoPos(SERVO19,m_pos19);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}


void CMelanieDlg::OnSavepos() 
// Save the position of all servos in the sequence in memory
{
	UpdateData(TRUE);				//Read Form	

	pstActualPos->cServoPos[ 1]=	m_pos01;
	pstActualPos->cServoPos[ 2]=	m_pos02;
	pstActualPos->cServoPos[ 3]=	m_pos03;
	pstActualPos->cServoPos[ 4]=	m_pos04;
	pstActualPos->cServoPos[ 5]=	m_pos05;
	pstActualPos->cServoPos[ 6]=	m_pos06;
	pstActualPos->cServoPos[ 7]=	m_pos07;
	pstActualPos->cServoPos[ 8]=	m_pos08;
	pstActualPos->cServoPos[ 9]=	m_pos09;
	pstActualPos->cServoPos[10]=	m_pos10;
	pstActualPos->cServoPos[11]=	m_pos11;
	pstActualPos->cServoPos[12]=	m_pos12;
	pstActualPos->cServoPos[13]=	m_pos13;
	pstActualPos->cServoPos[14]=	m_pos14;
	pstActualPos->cServoPos[15]=	m_pos15;
	pstActualPos->cServoPos[16]=	m_pos16;
	pstActualPos->cServoPos[17]=	m_pos17;
	pstActualPos->cServoPos[18]=	m_pos18;
	pstActualPos->cServoPos[19]=	m_pos19;
	pstActualPos->cServoPos[20]=	0;
	pstActualPos->cPause=			m_pause;

	if (pstActualPos->nextpos==NULL)
	{
		pstActualPos->nextpos=	new(struct	stPosition);
		pstPrevPos=pstActualPos;
		pstActualPos=pstActualPos->nextpos;
		pstActualPos->nextpos=NULL;
		pstActualPos->prevpos=pstPrevPos;
	}
	else
	{
		pstActualPos=pstActualPos->nextpos;
	}

}


void CMelanieDlg::OnSaveseq() 
// Save sequence in file
{
//	ofstream seqfile("seqfile.txt",ios::out);
	UpdateData(TRUE);				//Read Form	
	ofstream seqfile(m_seqname,ios::out);
	if(!seqfile) 
		MessageBox("Sequence file could not be opened","Error Message",MB_ICONEXCLAMATION);
	else 
	{
		pstActualPos=pstFirstPos;
		while (pstActualPos->nextpos!=NULL)
		{
			seqfile.put(pstActualPos->cPause);
			for (temp=1;temp<=20;temp++)
				seqfile.put(pstActualPos->cServoPos[temp]);
			seqfile.put((unsigned char)10);
			pstActualPos=pstActualPos->nextpos;
		}
		seqfile.close();
	}
}

void CMelanieDlg::SetGlobalPos()
// Set all servo positions as specified by the actual pointer
// from the sequence
{

	//Move servos to specified positions
	SetServoPos(SERVO01,pstActualPos->cServoPos[ 1], cSpeed( 1));
	SetServoPos(SERVO02,pstActualPos->cServoPos[ 2], cSpeed( 2));
	SetServoPos(SERVO03,pstActualPos->cServoPos[ 3], cSpeed( 3));
	SetServoPos(SERVO04,pstActualPos->cServoPos[ 4], cSpeed( 4));
	SetServoPos(SERVO05,pstActualPos->cServoPos[ 5], cSpeed( 5));
	SetServoPos(SERVO06,pstActualPos->cServoPos[ 6], cSpeed( 6));
	SetServoPos(SERVO07,pstActualPos->cServoPos[ 7], cSpeed( 7));
	SetServoPos(SERVO08,pstActualPos->cServoPos[ 8], cSpeed( 8));
	SetServoPos(SERVO09,pstActualPos->cServoPos[ 9], cSpeed( 9));
	SetServoPos(SERVO10,pstActualPos->cServoPos[10], cSpeed(10));
	SetServoPos(SERVO11,pstActualPos->cServoPos[11], cSpeed(11));
	SetServoPos(SERVO12,pstActualPos->cServoPos[12], cSpeed(12));
	SetServoPos(SERVO13,pstActualPos->cServoPos[13], cSpeed(13));
	SetServoPos(SERVO14,pstActualPos->cServoPos[14], cSpeed(14));
	SetServoPos(SERVO15,pstActualPos->cServoPos[15], cSpeed(15));
	SetServoPos(SERVO16,pstActualPos->cServoPos[16], cSpeed(16));
	SetServoPos(SERVO17,pstActualPos->cServoPos[17], cSpeed(17));
	SetServoPos(SERVO18,pstActualPos->cServoPos[18], cSpeed(18));
	SetServoPos(SERVO19,pstActualPos->cServoPos[19], cSpeed(19));

	//Update form values as per the values especified
	m_pos01=pstActualPos->cServoPos[ 1];
	m_pos02=pstActualPos->cServoPos[ 2];
	m_pos03=pstActualPos->cServoPos[ 3];
	m_pos04=pstActualPos->cServoPos[ 4];
	m_pos05=pstActualPos->cServoPos[ 5];
	m_pos06=pstActualPos->cServoPos[ 6];
	m_pos07=pstActualPos->cServoPos[ 7];
	m_pos08=pstActualPos->cServoPos[ 8];
	m_pos09=pstActualPos->cServoPos[ 9];
	m_pos10=pstActualPos->cServoPos[10];
	m_pos11=pstActualPos->cServoPos[11];
	m_pos12=pstActualPos->cServoPos[12];
	m_pos13=pstActualPos->cServoPos[13];
	m_pos14=pstActualPos->cServoPos[14];
	m_pos15=pstActualPos->cServoPos[15];
	m_pos16=pstActualPos->cServoPos[16];
	m_pos17=pstActualPos->cServoPos[17];
	m_pos18=pstActualPos->cServoPos[18];
	m_pos19=pstActualPos->cServoPos[19];

	//Update form sliders as per the values especified
	m_SliderServo01=100-(pstActualPos->cServoPos[ 1]*100/250);
	m_SliderServo02=(pstActualPos->cServoPos[ 2]*100/250);
	m_SliderServo03=100-(pstActualPos->cServoPos[ 3]*100/250);
	m_SliderServo04=100-(pstActualPos->cServoPos[ 4]*100/250);
	m_SliderServo05=(pstActualPos->cServoPos[ 5]*100/250);
	m_SliderServo06=100-(pstActualPos->cServoPos[ 6]*100/250);
	m_SliderServo07=100-(pstActualPos->cServoPos[ 7]*100/250);
	m_SliderServo08=(pstActualPos->cServoPos[ 8]*100/250);
	m_SliderServo09=100-(pstActualPos->cServoPos[ 9]*100/250);
	m_SliderServo10=(pstActualPos->cServoPos[10]*100/250);
	m_SliderServo11=(pstActualPos->cServoPos[11]*100/250);
	m_SliderServo12=100-(pstActualPos->cServoPos[12]*100/250);
	m_SliderServo13=(pstActualPos->cServoPos[13]*100/250);
	m_SliderServo14=(pstActualPos->cServoPos[14]*100/250);
	m_SliderServo15=100-(pstActualPos->cServoPos[15]*100/250);
	m_SliderServo16=(pstActualPos->cServoPos[16]*100/250);
	m_SliderServo17=(pstActualPos->cServoPos[17]*100/250);
	m_SliderServo18=100-(pstActualPos->cServoPos[18]*100/250);
	m_SliderServo19=(pstActualPos->cServoPos[19]*100/250);
	m_pause=pstActualPos->cPause;
	UpdateData(FALSE);				//Update Form	
	Sleep((pstActualPos->cPause)*5);
	
}

void CMelanieDlg::OnTopback()
//Set actual pointer position to first one in sequence 
{
	pstActualPos=pstFirstPos;
	if (pstActualPos->nextpos!=NULL) SetGlobalPos();
}

void CMelanieDlg::OnTopforward() 
//Set actual pointer position to last one in sequence 
{
	while (pstActualPos->nextpos!=NULL)
	{
		pstActualPos=pstActualPos->nextpos;
	}
	if (pstActualPos->prevpos!=NULL)
	{
		pstActualPos=pstActualPos->prevpos;
		SetGlobalPos();
	}
	
}

void CMelanieDlg::OnStepforward() 
//Make one movement from the sequence in forward mode
{
	if (pstActualPos->nextpos!=NULL)
	{
		pstActualPos=pstActualPos->nextpos;
		if (pstActualPos->nextpos==NULL)
		{
			pstActualPos=pstActualPos->prevpos;
			SetGlobalPos();
		}
		else
			SetGlobalPos();
	}
}

void CMelanieDlg::OnAllforward() 
//Make all the sequence of movements from actual position 
//of pointer in forward mode
{
	while (pstActualPos->nextpos!=NULL)
	{
		pstActualPos=pstActualPos->nextpos;
		if (pstActualPos->nextpos!=NULL) SetGlobalPos();
	}
	if ((pstActualPos->nextpos==NULL) && 
		(pstActualPos->prevpos!=NULL))
		{
			pstActualPos=pstActualPos->prevpos;
		}
	
}


void CMelanieDlg::OnStepback() 
//Make one movement from the sequence in reverse mode
{
	if (pstActualPos->prevpos!=NULL)
	{
		pstActualPos=pstActualPos->prevpos;
		SetGlobalPos();
	}
	
}

void CMelanieDlg::OnClearseq() 
//Clear Sequence in memory
{
	delete(pstFirstPos);	//Free memory previously used
	CreateSequence();
}

void CMelanieDlg::CreateSequence()
//Create the sequence, so could be used here and there
{
	pstFirstPos=new (struct	stPosition);
	pstActualPos=pstFirstPos;
	pstActualPos->nextpos=NULL;
	pstActualPos->prevpos=NULL;
	for (temp=1;temp<=20;temp++)
		pstActualPos->cServoPos[temp]=0;
	pstActualPos->cPause=0;

}

void CMelanieDlg::OnAllback() 
//Make all the sequence of movements from actual position 
//of pointer in reverse mode
{
	while (pstActualPos->prevpos!=NULL)
	{
		pstActualPos=pstActualPos->prevpos;
		SetGlobalPos();
	}
}

void CMelanieDlg::OnLoadseq() 
//Load sequence from file
{
	delete(pstFirstPos);	//Free memory previously used
	CreateSequence();
	UpdateData(TRUE);				//Read Form	
	LoadSequence(m_seqname);	
}


void CMelanieDlg::LoadSequence(CString FileName)
//Load sequence from file storing from actual pointer
//position
{
	unsigned char c;		

	UpdateData(TRUE);				//Read Form	
	ifstream seqfile(FileName,ios::in|ios::nocreate);
	if(!seqfile) 
		MessageBox("Sequence file could not be opened","Error Message",MB_ICONEXCLAMATION);
	else 
	{
		while (seqfile.get(c))
		{
			pstActualPos->cPause=c;
			for (temp=1;temp<=20;temp++)
				seqfile.get(pstActualPos->cServoPos[temp]);
			seqfile.get(c);		//Carriage return
			if (pstActualPos->nextpos==NULL)
			{
				pstActualPos->nextpos=	new(struct	stPosition);
				pstPrevPos=pstActualPos;
				pstActualPos=pstActualPos->nextpos;
				pstActualPos->nextpos=NULL;
				pstActualPos->prevpos=pstPrevPos;
			}
			else
			{
				pstActualPos=pstActualPos->nextpos;
			}
		}
		seqfile.close();
		OnTopback();
	}
}

void CMelanieDlg::OnLoadOverSeq() 
//Load a sequence overwriting actual secuence in memory
//from the actual pointer position onwards
{
	UpdateData(TRUE);				//Read Form	
	LoadSequence(m_seqname);	
}

void CMelanieDlg::OnSwitch() 
//Switch ON/OFF Robot
{
	UpdateData(TRUE);				//Read Form	
	if (m_switch) 
	{
		SendCommand("SO");
		SendCommand("SX1F9D");


		//Left Leg - 1
		ActivateServo(SERVO01,18);
		ActivateServo(SERVO02,55);
		ActivateServo(SERVO03,103);

		//Left Leg - 2
		ActivateServo(SERVO04,10);
		ActivateServo(SERVO05,35);
		ActivateServo(SERVO06,85);

		//Left Leg - 3
		ActivateServo(SERVO07,23);
		ActivateServo(SERVO08,65);
		ActivateServo(SERVO09,118);

		//Head
		ActivateServo(SERVO10,85);

		//Right Leg - 1
		ActivateServo(SERVO11,155);
		ActivateServo(SERVO12,210);
		ActivateServo(SERVO13,85);

		//Right Leg - 2
		ActivateServo(SERVO14,175);
		ActivateServo(SERVO15,180);
		ActivateServo(SERVO16,95);

		//Right Leg - 3
		ActivateServo(SERVO17,160);
		ActivateServo(SERVO18,180);
		ActivateServo(SERVO19,75);

		RunPreset("start.txt");	
		m_seqname = _T("seqfile.txt");
		UpdateData(FALSE);


	}
	else
	{
		SendCommand("SF");
	}
}

unsigned char CMelanieDlg::cSpeed(unsigned char cServo)
//Calculate the Speed for a Servo as a function of the Pause
//and de position
{
	int iSP;
	if (pstActualPos->prevpos==NULL)
		iSP=1;
	else
	{
		pstPrevPos=pstActualPos->prevpos;

		if (pstActualPos->cServoPos[cServo] > pstPrevPos->cServoPos[cServo])
			iSP=(int)((float)(pstActualPos->cServoPos[cServo] - 
				pstPrevPos->cServoPos[cServo])*(float)8/
				(float)pstActualPos->cPause);
		else
			iSP=(int)((float)(pstPrevPos->cServoPos[cServo] - 
				pstActualPos->cServoPos[cServo])*(float)8/
				(float)pstActualPos->cPause);

	}
	if (iSP>255) iSP=255;
	if (iSP==0) iSP=1;
	return (iSP);
}

void CMelanieDlg::OnSaveinvseq() 
// Save inverted sequence in file
{
	UpdateData(TRUE);				//Read Form	
	ofstream seqfile(m_seqname,ios::out);
	if(!seqfile) 
		MessageBox("Sequence file could not be opened","Error Message",MB_ICONEXCLAMATION);
	else 
	{
		while (pstActualPos->nextpos!=NULL)
		{
			pstActualPos=pstActualPos->nextpos;
		}
		if (pstActualPos->prevpos!=NULL)
		{
			pstActualPos=pstActualPos->prevpos;
		}
		do {
			seqfile.put(pstActualPos->cPause);
			for (temp=1;temp<=20;temp++)
				seqfile.put(pstActualPos->cServoPos[temp]);
			seqfile.put((unsigned char)10);
			pstActualPos=pstActualPos->prevpos;
		} while (pstActualPos->prevpos!=NULL);
		seqfile.put(pstActualPos->cPause);
		for (temp=1;temp<=20;temp++)
			seqfile.put(pstActualPos->cServoPos[temp]);
		seqfile.put((unsigned char)10);
		seqfile.close();
	}
}

void CMelanieDlg::RunPreset(CString FileName)
//Load and run a specific file of sequence
{
	m_seqname=FileName;
	UpdateData(FALSE);		//Update form
	OnLoadseq();			//Load the preset sequence
	OnAllforward();			//Run it	

}

void CMelanieDlg::OnPreset1() 
//Up
{
	RunPreset("up.txt");
}


void CMelanieDlg::OnPreset2() 
//Down
{
	RunPreset("down.txt");	
}

void CMelanieDlg::OnPreset6() 
//PreFwd
{
	RunPreset("prefwd.txt");	
}

void CMelanieDlg::OnPreset3() 
//Fwd
{
	RunPreset("fwd.txt");	
}

void CMelanieDlg::OnPreset10() 
//PosFwd
{
	RunPreset("posfwd.txt");	
}

void CMelanieDlg::OnPreset4() 
//Back
{
	RunPreset("back.txt");	
}

void CMelanieDlg::OnPreset8() 
//Left
{
	RunPreset("left.txt");	
}

void CMelanieDlg::OnPreset9() 
//Right
{
	RunPreset("right.txt");	
}

void CMelanieDlg::OnPreset5() 
//Run
{
	RunPreset("run.txt");	
}

void CMelanieDlg::OnPreset7() 
//PreRight
{
	RunPreset("preright.txt");	
}

void CMelanieDlg::OnPreset11() 
//PosRight
{
	RunPreset("posright.txt");	
}

void CMelanieDlg::OnPresetset1() 
//Preset set: up - fwd - right 45º - fwd - down
{
	RunPreset("up.txt");	
	RunPreset("prefwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("posfwd.txt");	
	RunPreset("preright.txt");	
	RunPreset("right.txt");	
	RunPreset("right.txt");	
	RunPreset("posright.txt");	
	RunPreset("prefwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("posfwd.txt");	
	RunPreset("down.txt");	
}

void CMelanieDlg::OnPreset12() 
//PreLeft
{
	RunPreset("preleft.txt");	
}

void CMelanieDlg::OnPresetset2() 
//Preset set: Up - Fwd - Left 180º - Fwd - Down
{
	RunPreset("up.txt");	
	RunPreset("prefwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("posfwd.txt");	
	RunPreset("preleft.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("posleft.txt");	
	RunPreset("prefwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("posfwd.txt");	
	RunPreset("down.txt");	
	
}

void CMelanieDlg::OnPreset13() 
//PosLeft
{
	RunPreset("posleft.txt");	
	
}
