//	-*- tab-width: 2; -*-

#ifndef TEXMODULE_h
#define TEXMODULE_h 1

#include "BBLMInterface.h"
#include "BBLMTextIterator.h"

void	scan_tex(BBLMParamBlock    &params,
						const BBLMCallbackBlock &callbacks);

void	ParseTeX(BBLMParamBlock    &bblm_params,
						const BBLMCallbackBlock &bblm_callbacks);

extern "C"
{

OSErr	TeXMachO(BBLMParamBlock		&params,
						const BBLMCallbackBlock	&bblm_callbacks);

}

#endif	// TEXMODULE_h
