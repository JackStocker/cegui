/***********************************************************************
    created:    25/05/2009
    author:     Paul Turner
 *************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2009 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include "CEGUI/LeftAlignedRenderedString.h"
#include "CEGUI/RenderedString.h"
#include "CEGUI/Sizef.h"

namespace CEGUI
{
//----------------------------------------------------------------------------//
LeftAlignedRenderedString::LeftAlignedRenderedString(
        const RenderedString& string) :
    FormattedRenderedString(string)
{
}

//----------------------------------------------------------------------------//
void LeftAlignedRenderedString::format(const Window* /*ref_wnd*/,
                                       const Sizef& /*area_size*/)
{
}

//----------------------------------------------------------------------------//
std::vector<GeometryBuffer*> LeftAlignedRenderedString::createRenderGeometry(
    const Window* ref_wnd,
    const glm::vec2& position,
    const ColourRect* mod_colours,
    const Rectf* clip_rect) const
{
    std::vector<GeometryBuffer*> geomBuffers;

    glm::vec2 draw_pos(position);
    for (size_t i = 0; i < d_renderedString->getLineCount(); ++i)
    {
        auto currGeom = d_renderedString->createRenderGeometry(ref_wnd, i, draw_pos, mod_colours, clip_rect, 0.0f);
        geomBuffers.insert(geomBuffers.end(), currGeom.begin(), currGeom.end());

        draw_pos.y += d_renderedString->getLineExtent(ref_wnd, i).d_height;
    }

    return geomBuffers;
}

//----------------------------------------------------------------------------//
size_t LeftAlignedRenderedString::getFormattedLineCount() const
{
    return d_renderedString->getLineCount();
}

//----------------------------------------------------------------------------//
float LeftAlignedRenderedString::getHorizontalExtent(const Window* ref_wnd) const
{
    float w = 0.0f;
    for (size_t i = 0; i < d_renderedString->getLineCount(); ++i)
    {
        const float this_width = d_renderedString->getLineExtent(ref_wnd, i).d_width;
        if (this_width > w)
            w = this_width;
    }

    return w;
}

//----------------------------------------------------------------------------//
float LeftAlignedRenderedString::getVerticalExtent(const Window* ref_wnd) const
{
    float h = 0.0f;
    for (size_t i = 0; i < d_renderedString->getLineCount(); ++i)
        h += d_renderedString->getLineExtent(ref_wnd, i).d_height;

    return h;
}

//----------------------------------------------------------------------------//
    
} // End of  CEGUI namespace section
