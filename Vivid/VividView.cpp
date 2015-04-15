// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// VividView.cpp : implementation of the CVividView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Vivid.h"
#endif

#include "VividDoc.h"
#include "VividView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVividView

IMPLEMENT_DYNCREATE(CVividView, CView)

BEGIN_MESSAGE_MAP(CVividView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVividView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_RENDERING_REND, &CVividView::OnRenderingRend)
END_MESSAGE_MAP()

// CVividView construction/destruction

CVividView::CVividView()
{
	// TODO: add construction code here

}

CVividView::~CVividView()
{
}

BOOL CVividView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVividView drawing

void CVividView::OnDraw(CDC* pDC)
{
	CVividDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_pApp != NULL) DrawFrameBuffer(pDC);
}


// CVividView printing


void CVividView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CVividView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVividView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVividView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVividView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVividView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVividView diagnostics

#ifdef _DEBUG
void CVividView::AssertValid() const
{
	CView::AssertValid();
}

void CVividView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVividDoc* CVividView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVividDoc)));
	return (CVividDoc*)m_pDocument;
}
#endif //_DEBUG


// CVividView message handlers

void CVividView::OnRenderingRend()
{
	if (m_pApp != NULL)
		m_pApp->Render();
	else
		return;

	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);

	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 100, 100, x_offset + m_pApp->Width, y_offset + m_pApp->Height, NULL);

	Invalidate(true);
}

void CVividView::DrawFrameBuffer(CDC *pDC)
{
	if (m_pApp->FrameBuffer == NULL)
	{
		return;
	}

	if (!m_pApp->render_->IsOpen())
	{
		AfxMessageBox(L"Renderer was not opened\n");
		return;
	}

	HDC hdc;
	hdc = ::CreateCompatibleDC(pDC->m_hDC);
	HBITMAP m_bitmap;

	// Display the current image
	char buffer[sizeof(BITMAPINFO)];
	BITMAPINFO* binfo = (BITMAPINFO*)buffer;
	memset(binfo, 0, sizeof(BITMAPINFOHEADER));
	binfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

	// Create the bitmap
	BITMAPINFOHEADER* bih = &binfo->bmiHeader;
	bih->biBitCount = 3 * 8;
	bih->biWidth = m_pApp->Width;
	bih->biHeight = m_pApp->Height;
	bih->biPlanes = 1;
	bih->biCompression = BI_RGB;
	bih->biSizeImage = 0;

	m_bitmap = CreateDIBSection(hdc, binfo, 0, 0, 0, DIB_RGB_COLORS);

	int colors = DIB_RGB_COLORS;

	::SelectObject(hdc, m_bitmap);
	binfo->bmiHeader.biBitCount = 0;
	GetDIBits(hdc, m_bitmap, 0, 0, 0, binfo, colors);
	binfo->bmiHeader.biBitCount = 24;
	binfo->bmiHeader.biHeight = -abs(binfo->bmiHeader.biHeight);
	SetDIBits(hdc, m_bitmap, 0, m_pApp->Height, m_pApp->FrameBuffer, binfo, colors);

	::SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
	CRect client;
	GetClientRect(&client);
	::BitBlt(pDC->m_hDC, 0, 0, m_pApp->Width, m_pApp->Height, hdc, 0, 0, SRCCOPY);
	::DeleteDC(hdc);
	DeleteObject(m_bitmap);
}