#include "stdafx.h"
#include "Digitizer.h"
#include "ShapeEditor.h"
#include "EditorHelper.h"
#include "ShapefileHelper.h"

// ************************************************************
//		Start
// ************************************************************
void Digitizer::StartNewBoundShape(CShapeEditor* editor, IShapefile* sf, long layerHandle)
{
	if (!editor || !sf || layerHandle == -1) return;

	ShpfileType shpType;
	sf->get_ShapefileType(&shpType);

	editor->Clear();
	editor->put_ShapeType(shpType);
	editor->put_LayerHandle(layerHandle);
	editor->put_EditorState(esDigitize);

	CComPtr<IShapeDrawingOptions> options = NULL;
	sf->get_DefaultDrawingOptions(&options);
	editor->CopyOptionsFrom(options);
	return;
}

// ************************************************************
//		OnMouseDown
// ************************************************************
bool Digitizer::OnMouseDown(CShapeEditor* editor, double projX, double projY, bool ctrl)
{
	if (!editor) return false;

	// add another point
	editor->HandleProjPointAdd(projX, projY);
	editor->SetRedrawNeeded(rtShapeEditor);

	// for point layer save the new shape at once
	if (EditorHelper::GetShapeType2D(editor) == SHP_POINT)
	{
		return editor->TryStop();
	}
    else if (ctrl)
    {
        // if an attempt to finish a multipoint shape
        return editor->TryStop();
    }

	return true;
}