// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_renderer.h"

namespace tb {

// == TBRenderer ========================================================================

void TBRenderer::InvokeContextLost()
{
	TBLinkListOf<TBRendererListener>::Iterator iter = m_listeners.IterateForward();
	while (TBRendererListener *listener = iter.GetAndStep())
		listener->OnContextLost();
}

void TBRenderer::InvokeContextRestored()
{
	TBLinkListOf<TBRendererListener>::Iterator iter = m_listeners.IterateForward();
	while (TBRendererListener *listener = iter.GetAndStep())
		listener->OnContextRestored();
}

}; // namespace tb
