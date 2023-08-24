/*================================================================================================*/
/*
 *	Copyright 2009-2015, 2018-2019, 2023 Avid Technology, Inc.
 *	All rights reserved.
 *	
 *	CONFIDENTIAL: this document contains confidential information of Avid. Do
 *	not disclose to any third party. Use of the information contained in this
 *	document is subject to an Avid SDK license.
 */

/**  
 *	\file   DemoGain_GUI_VST.h
 *
 */ 
/*================================================================================================*/
#pragma once
#ifndef DEMOGAIN_GUI_JUCE_H
#define DEMOGAIN_GUI_JUCE_H

#include "AAX_CEffectGUI_VST.h"

class DemoGain_SliderVST;

enum EDemoGain_ControlIndex {
	eControl_Bypass = 0,
	eControl_GainSlider,
	eControl_GainText
};

class DemoGain_View : public VSTGUI_ContentView, public VSTGUI::IControlListener
{
public: ///////////////////////////// constructor/destructor
	DemoGain_View(void *pSystemWindow, AAX_IEffectParameters* pParams, VSTGUI::VSTGUIEditorInterface *pEditor, AAX_IViewContainer* inViewContainer);
	~DemoGain_View() override;

public: ///////////////////////////// DemoGain_View
	static void LoadViewResources();
	
	void updateGain();
	void highliteGain(AAX_CBoolean iIsHighlighted, AAX_EHighlightColor iColor);

public: ///////////////////////////// VSTGUI::IControlListener
	void valueChanged (VSTGUI::CControl* pControl) override;
	void controlBeginEdit (VSTGUI::CControl* pControl) override;
	void controlEndEdit (VSTGUI::CControl* pControl) override;
	
private: //////////////////////////// DemoGain_View
	static std::auto_ptr<VSTGUI::CBitmap>	m_hPIBackground;
	static std::auto_ptr<VSTGUI::CBitmap>	m_hSliderBack;					
	static std::auto_ptr<VSTGUI::CBitmap>	m_hSliderHandle;
	static std::auto_ptr<VSTGUI::CBitmap>	m_hSliderHandleRed;
	static std::auto_ptr<VSTGUI::CBitmap>	m_hSliderHandleBlue;
	static std::auto_ptr<VSTGUI::CBitmap>	m_hSliderHandleGreen;
	static std::auto_ptr<VSTGUI::CBitmap>	m_hSliderHandleYellow;

	DemoGain_SliderVST*	m_hSliderCtrl;
	VSTGUI::CTextEdit* m_hGainText;
	
	AAX_IViewContainer* mViewContainer;
};

//==============================================================================
class DemoGain_GUI : public AAX_CEffectGUI_VST
{
public:
	static AAX_IEffectGUI *		AAX_CALLBACK Create ( void );

	DemoGain_GUI();
	AAX_DEFAULT_DTOR_OVERRIDE(DemoGain_GUI);
	
protected:
	void			CreateViewContents () AAX_OVERRIDE;
	void			CreateEffectView (void *inSystemWindow) AAX_OVERRIDE;
	AAX_Result		ParameterUpdated ( AAX_CParamID iParameterID ) AAX_OVERRIDE;

	AAX_Result		SetControlHighlightInfo (AAX_CParamID iParameterID, AAX_CBoolean iIsHighlighted, AAX_EHighlightColor iColor) AAX_OVERRIDE;
		
	AAX_CBoolean	m_bSliderIsHighlighted;
	AAX_EHighlightColor	m_SliderColor;			// current slider handle color
};


#endif // DEMOGAIN_GUI_JUCE_H
