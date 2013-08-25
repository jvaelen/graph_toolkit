#include "toolstate.h"
#include <assert.h>

ToolState::ToolState(const string& title, const string& toolTip, const string& iconPath)
{
    _title = title;
    _toolTip = toolTip;
    _iconPath = iconPath;
    // prevent dangling pointers
    _graph = NULL;
    _toolPM = NULL;
}
