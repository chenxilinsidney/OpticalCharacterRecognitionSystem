
// OpticalCharacterRecognitionSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpticalCharacterRecognitionSystem.h"
#include "OpticalCharacterRecognitionSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpticalCharacterRecognitionSystemDlg dialog




COpticalCharacterRecognitionSystemDlg::COpticalCharacterRecognitionSystemDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(COpticalCharacterRecognitionSystemDlg::IDD, pParent)
    ,image_height(360)
    ,image_width(200)
    ,image_interval(20)
    ,ocr()
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    rect_image_gray = CRect(0, 0, 0, 0);
    rect_image_binary = CRect(0, 0, 0, 0);
    ocr.setImageBinary(Mat(36, 20, CV_8UC1, Scalar::all(0)));
    ocr.setImageGray(Mat(36, 20, CV_8UC1, Scalar::all(0)));
}

void COpticalCharacterRecognitionSystemDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpticalCharacterRecognitionSystemDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_GRAYIMAGE, &COpticalCharacterRecognitionSystemDlg::OnClickedButtonGrayimage)
    ON_BN_CLICKED(IDC_BUTTON_BINARYIMAGE, &COpticalCharacterRecognitionSystemDlg::OnClickedButtonBinaryimage)
    ON_BN_CLICKED(IDC_BUTTON_RECOGNITION, &COpticalCharacterRecognitionSystemDlg::OnClickedButtonRecognition)
    ON_BN_CLICKED(IDC_BUTTON_BINARY_GENERATE, &COpticalCharacterRecognitionSystemDlg::OnClickedButtonBinaryGenerate)
END_MESSAGE_MAP()


// COpticalCharacterRecognitionSystemDlg message handlers

BOOL COpticalCharacterRecognitionSystemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpticalCharacterRecognitionSystemDlg::OnPaint()
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
    // set window
    MoveWindow(image_interval,
        image_interval,
        13 * image_interval + 2 * image_width,
        11 * image_interval + image_height);
    // set picture handler
    GetDlgItem(IDC_IMAGE_GRAY)->MoveWindow(
        image_interval * 1,
        image_interval * 3,
        image_width,
        image_height);
    GetDlgItem(IDC_IMAGE_GRAY)->GetClientRect(&rect_image_gray);
    GetDlgItem(IDC_IMAGE_BINARY)->MoveWindow(
        image_interval * 2 + image_width,
        image_interval * 3,
        image_width,
        image_height);
    GetDlgItem(IDC_IMAGE_BINARY)->GetClientRect(&rect_image_binary);
    // set static text
    int static_width = 140;
    int static_height = image_interval;
    CFont testfont;
    testfont.CreatePointFont(110, "微软雅黑");
    // IDC_STATIC_GRAYIMAGE
    GetDlgItem(IDC_STATIC_GRAYIMAGE)->MoveWindow(
        image_interval * 1 + (image_width - static_width) / 2,
        image_interval * 1,
        static_width,
        static_height);
    SetDlgItemText(IDC_STATIC_GRAYIMAGE, LPCTSTR("Gray-Image"));
    GetDlgItem(IDC_STATIC_GRAYIMAGE)->SetFont(&testfont);
    GetDlgItem(IDC_STATIC_GRAYIMAGE)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDC_STATIC_BINARYIMAGE
    GetDlgItem(IDC_STATIC_BINARYIMAGE)->MoveWindow(
        image_interval * 2 + image_width + (image_width - static_width) / 2,
        image_interval * 1,
        static_width,
        static_height);
    SetDlgItemText(IDC_STATIC_BINARYIMAGE, LPCTSTR("Binary-Image"));
    GetDlgItem(IDC_STATIC_BINARYIMAGE)->SetFont(&testfont);
    GetDlgItem(IDC_STATIC_BINARYIMAGE)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDC_BUTTON_GRAYIMAGE
    GetDlgItem(IDC_BUTTON_GRAYIMAGE)->MoveWindow(
        image_interval * 3 + image_width * 2,
        image_interval * 3,
        static_width,
        static_height);
    SetDlgItemText(IDC_BUTTON_GRAYIMAGE, LPCTSTR("Open-Gray-Image"));
    GetDlgItem(IDC_BUTTON_GRAYIMAGE)->SetFont(&testfont);
    GetDlgItem(IDC_BUTTON_GRAYIMAGE)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDC_BUTTON_BINARYIMAGE
    GetDlgItem(IDC_BUTTON_BINARYIMAGE)->MoveWindow(
        image_interval * 3 + image_width * 2,
        image_interval * 6,
        static_width,
        static_height);
    SetDlgItemText(IDC_BUTTON_BINARYIMAGE, LPCTSTR("Open-Binary-Image"));
    GetDlgItem(IDC_BUTTON_BINARYIMAGE)->SetFont(&testfont);
    GetDlgItem(IDC_BUTTON_BINARYIMAGE)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDC_BUTTON_BINARYIMAGE
    GetDlgItem(IDC_BUTTON_BINARY_GENERATE)->MoveWindow(
        image_interval * 3 + image_width * 2,
        image_interval * 9,
        static_width,
        static_height);
    SetDlgItemText(IDC_BUTTON_BINARY_GENERATE, LPCTSTR("Create-Binary-Image"));
    GetDlgItem(IDC_BUTTON_BINARY_GENERATE)->SetFont(&testfont);
    GetDlgItem(IDC_BUTTON_BINARY_GENERATE)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDC_BUTTON_RECOGNITION
    GetDlgItem(IDC_BUTTON_RECOGNITION)->MoveWindow(
        image_interval * 3 + image_width * 2,
        image_interval * 12,
        static_width * 1.2,
        static_height * 1.2);
    SetDlgItemText(IDC_BUTTON_RECOGNITION, LPCTSTR("Recognize Character"));
    GetDlgItem(IDC_BUTTON_RECOGNITION)->SetFont(&testfont);
    GetDlgItem(IDC_BUTTON_RECOGNITION)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDC_STATIC_RESULT_TIP
    GetDlgItem(IDC_STATIC_RESULT_TIP)->MoveWindow(
        image_interval * 3 + image_width * 2,
        image_interval * 14,
        static_width,
        static_height);
    SetDlgItemText(IDC_STATIC_RESULT_TIP, LPCTSTR("Result:"));
    GetDlgItem(IDC_STATIC_RESULT_TIP)->SetFont(&testfont);
    GetDlgItem(IDC_STATIC_RESULT_TIP)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDC_STATIC_RESULT_SHOW
    GetDlgItem(IDC_STATIC_RESULT_SHOW)->MoveWindow(
        image_interval * 3 + image_width * 2,
        image_interval * 14,
        static_width,
        static_height * 5);
    SetDlgItemText(IDC_STATIC_RESULT_SHOW, LPCTSTR(" "));
    CFont resultfont;
    resultfont.CreatePointFont(400, "微软雅黑");
    GetDlgItem(IDC_STATIC_RESULT_SHOW)->SetFont(&resultfont);
    GetDlgItem(IDC_STATIC_RESULT_SHOW)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDCANCEL
    GetDlgItem(IDCANCEL)->MoveWindow(
        13 * image_interval + 2 * image_width - static_width - image_interval,
        11 * image_interval + image_height - 3 * image_interval,
        static_width,
        static_height);
    SetDlgItemText(IDCANCEL, LPCTSTR("Close-System"));
    GetDlgItem(IDCANCEL)->SetFont(&testfont);
    GetDlgItem(IDCANCEL)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    // IDC_STATIC_TYPE
    GetDlgItem(IDC_STATIC_TYPE)->MoveWindow(
        0.8 * image_interval,
        3.8 * image_interval + image_height,
        static_width + 0.2 * image_interval,
        static_height * 4 + 0.5 * image_interval);
    SetDlgItemText(IDC_STATIC_TYPE, LPCTSTR("Character-Type"));
    GetDlgItem(IDC_STATIC_TYPE)->SetFont(&testfont);
    // IDC_RADIO_CHAR
    GetDlgItem(IDC_RADIO_CHAR)->MoveWindow(
        1 * image_interval,
        5 * image_interval + image_height,
        static_width * 0.8,
        static_height);
    SetDlgItemText(IDC_RADIO_CHAR, LPCTSTR("Char(A-Z&&0-9)"));
    GetDlgItem(IDC_RADIO_CHAR)->SetFont(&testfont);
    CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_CHAR);
    radio->SetCheck(1);
    // IDC_RADIO_LETTER
    GetDlgItem(IDC_RADIO_LETTER)->MoveWindow(
        1 * image_interval,
        6 * image_interval + image_height,
        static_width * 0.8,
        static_height);
    SetDlgItemText(IDC_RADIO_LETTER, LPCTSTR("Letter(A-Z)"));
    GetDlgItem(IDC_RADIO_LETTER)->SetFont(&testfont);
    // IDC_RADIO_NUM
    GetDlgItem(IDC_RADIO_NUM)->MoveWindow(
        1 * image_interval,
        7 * image_interval + image_height,
        static_width * 0.8,
        static_height);
    SetDlgItemText(IDC_RADIO_NUM, LPCTSTR("Number(0-9)"));
    GetDlgItem(IDC_RADIO_NUM)->SetFont(&testfont);
    // IDC_RADIO_NUM
    GetDlgItem(IDC_STATIC_RATIO)->MoveWindow(
        2 * image_interval + static_width,
        4 * image_interval + image_height,
        static_width,
        static_height * 2);
    SetDlgItemText(IDC_STATIC_RATIO, LPCTSTR("Character-Ratio:\n(for 1 and I)"));
    GetDlgItem(IDC_STATIC_RATIO)->SetFont(&testfont);
    // IDC_RADIO_NUM
    GetDlgItem(IDC_EDIT_RATIO)->MoveWindow(
        2 * image_interval + static_width * 2,
        4 * image_interval + image_height,
        static_width * 0.25,
        static_height);
    SetDlgItemText(IDC_EDIT_RATIO, LPCTSTR("1"));
    GetDlgItem(IDC_EDIT_RATIO)->SetFont(&testfont);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpticalCharacterRecognitionSystemDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// play image to picture handler
void COpticalCharacterRecognitionSystemDlg::PlayImage(Mat& image, int ID, CRect& rect)
{
    // get HDC
    CDC* pDC = GetDlgItem(ID)->GetDC(); // 获得显示控件的 DC
    HDC hDC = pDC ->GetSafeHdc();       // 获取HDC(设备句柄)进行绘图操作
    // MAT TO IplImage
    IplImage img = IplImage(image);
    // IplImage TO CvvImage
    CvvImage cimg;
    cimg.CopyOf(&img);                  // 复制图片
    cimg.DrawToHDC(hDC, &rect);         // 将图片绘制到显示控件的指定区域
    // release CDC
    ReleaseDC(pDC);
}

// read gray image
void COpticalCharacterRecognitionSystemDlg::OnClickedButtonGrayimage()
{
    // TODO: Add your control notification handler code here
    CFileDialog pCFileDialog(true,NULL,NULL,0,"文本文件(*.bmp)|*.bmp");
    //CFileDialog pCFileDialog最后一个参数是打开文件对话框的筛选器内容
    pCFileDialog.m_ofn.lpstrTitle = "打开灰度图像文件";
    if(pCFileDialog.DoModal()!=IDOK)
    {
        return;
    }
    CString FileName = pCFileDialog.GetPathName();
    Mat image_gray = imread(FileName.GetString(), CV_8UC1);
    if (image_gray.data == NULL) {
        AfxMessageBox("can't read image:" + FileName);
    } else {
        ocr.setImageGray(image_gray);
        PlayImage(image_gray, IDC_IMAGE_GRAY, rect_image_gray);
    }
    // read binary image if name different only for 'gray' and 'bw'
    CString newFileName = FileName;
    int pos = newFileName.Find(LPCTSTR("gray"));
    if (pos != -1) {
        newFileName.Replace(LPCTSTR("gray"), LPCTSTR("bw"));
        Mat image_binary = imread(newFileName.GetString(), CV_8UC1);
        if (image_binary.data != NULL) {
            ocr.setImageBinary(image_binary);
            PlayImage(image_binary, IDC_IMAGE_BINARY, rect_image_binary);
        }
#ifdef _DEBUG
        TRACE("Pos = %d\n", pos);
#endif
    }

}

// read binary image
void COpticalCharacterRecognitionSystemDlg::OnClickedButtonBinaryimage()
{
    // TODO: Add your control notification handler code here
    CFileDialog pCFileDialog(true,NULL,NULL,0,"文本文件(*.bmp)|*.bmp");
    //CFileDialog pCFileDialog最后一个参数是打开文件对话框的筛选器内容
    pCFileDialog.m_ofn.lpstrTitle = "打开二值图像文件";
    if(pCFileDialog.DoModal()!=IDOK)
    {
        return;
    }
    CString FileName = pCFileDialog.GetPathName();
    Mat image_binary = imread(FileName.GetString(), CV_8UC1);
    if (image_binary.data == NULL) {
        AfxMessageBox("can't read image:" + FileName);
    } else {
        ocr.setImageBinary(image_binary);
        PlayImage(image_binary, IDC_IMAGE_BINARY, rect_image_binary);
    }
}

// generate binary image by gray image
void COpticalCharacterRecognitionSystemDlg::OnClickedButtonBinaryGenerate()
{
    // TODO: Add your control notification handler code here
    Mat image_gray;
    image_gray = ocr.getImageGray(image_gray);
    if (image_gray.data != NULL) {
        double otsu = threshold(image_gray, image_gray, 0, 255, THRESH_OTSU);
        threshold(image_gray, image_gray, otsu, 255, THRESH_BINARY);
        ocr.setImageBinary(image_gray);
        PlayImage(image_gray, IDC_IMAGE_BINARY, rect_image_binary);
    }
}

// get result
void COpticalCharacterRecognitionSystemDlg::OnClickedButtonRecognition()
{
    // TODO: Add your control notification handler code here
    // get character type
    CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_CHAR);
    int state = pBtn->GetCheck();
    if (state == 1) {
        ocr.setCharacterType(ocr.CHAR);
    } else {
        pBtn = (CButton*)GetDlgItem(IDC_RADIO_LETTER);
        state = pBtn->GetCheck();
        if (state == 1) {
            ocr.setCharacterType(ocr.LETTER);
        } else {
            CButton* pBtn = (CButton*)GetDlgItem(IDC_RADIO_NUM);
            state = pBtn->GetCheck();
            if (state == 1) {
                ocr.setCharacterType(ocr.NUMBER);
            } else {
                ocr.setCharacterType(-1);
            }
        }
    }
    // get character radio
    CString str;
    GetDlgItem(IDC_EDIT_RATIO)->GetWindowText(str);
    double ratio = _tstoi(str);
    ocr.setCharacterRatio(ratio);
#ifdef _DEBUG
    TRACE(" setCharacterType = %d\n", state);
    TRACE(" setCharacterRatio = %d\n", ratio);
#endif
    // detect if binary image exist
    Mat image_binary;
    image_binary = ocr.getImageBinary(image_binary);
    int sum = 0;
    for (int i = 0; i < image_binary.rows; i++) {
    	uchar* p = image_binary.ptr<uchar>(i);
        for (int j = 0; j < image_binary.cols; j++) {
        	sum += *(p + j);
        }
    }
    if (sum == 0) {
        image_binary = ocr.getImageGray(image_binary);
        if (image_binary.data != NULL) {
            double otsu = threshold(image_binary, image_binary, 0, 255, THRESH_OTSU);
            threshold(image_binary, image_binary, otsu, 255, THRESH_BINARY);
            ocr.setImageBinary(image_binary);
            PlayImage(image_binary, IDC_IMAGE_BINARY, rect_image_binary);
        }
    }
    // recognition
    char result = ocr.getRecognitionResult();
    // show result
    CString result_str = CString(result);
    CFont resultfont;
    resultfont.CreatePointFont(350, "微软雅黑");
    GetDlgItem(IDC_STATIC_RESULT_SHOW)->SetFont(&resultfont);
    GetDlgItem(IDC_STATIC_RESULT_SHOW)->ModifyStyle(SS_LEFT|SS_RIGHT,SS_CENTER,TRUE);
    GetDlgItem(IDC_STATIC_RESULT_SHOW)->SetWindowTextA(result_str);
}

