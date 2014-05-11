
// OpticalCharacterRecognitionSystemDlg.h : header file
// 

// header file
#include "Header.h"

#pragma once


// COpticalCharacterRecognitionSystemDlg dialog
class COpticalCharacterRecognitionSystemDlg : public CDialogEx
{
// Construction
public:
    COpticalCharacterRecognitionSystemDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    enum { IDD = IDD_OPTICALCHARACTERRECOGNITIONSYSTEM_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:
    CRect rect_image_gray;
    CRect rect_image_binary;
    int image_height;
    int image_width;
    int image_interval;
    Cocr ocr;
    void PlayImage(Mat& image, int ID, CRect& rect);
public:
    afx_msg void OnClickedButtonGrayimage();
    afx_msg void OnClickedButtonBinaryimage();
    afx_msg void OnClickedButtonRecognition();
    afx_msg void OnClickedButtonBinaryGenerate();
};
