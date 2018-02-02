//	-*- tab-width: 2; -*-

#include "TeXModule.h"

static SInt32			origIndex;
static BBLMRunRec	origRun;

static void AdjustRange(			BBLMParamBlock    &params,
												const BBLMCallbackBlock& /*callbacks*/)
{
	origIndex = params.fAdjustRangeParams.fOrigStartIndex;
	
	if (origIndex >= 0)
		origRun = params.fAdjustRangeParams.fOrigStartRun;
}

static void AdjustEnd(			BBLMParamBlock    &params,
											const BBLMCallbackBlock &callbacks)
{
	SInt32 runCount = bblmRunCount(&callbacks);
	
	if (origIndex >= 0 && origIndex < runCount)
	{
		BBLMRunRec s;
		
		bblmGetRun(&callbacks, origIndex, s.language, s.runKind, s.startPos, s.length);
		
		if (origRun.language == s.language	&&
				[origRun.runKind isEqualToString: s.runKind] &&
				origRun.startPos == s.startPos	&&
				origRun.length   == s.length)
			{
				long	sel_start, sel_end;
				long	first_char;

#warning
//				bbxtGetSelection((&bbxt_callbacks), &sel_start, &sel_end, &first_char);
				
				params.fAdjustEndParams.fEndOffset = sel_end;
			}
	}
}

static void match_keyword(BBLMParamBlock &params)
{
#warning
/*
	params.fMatchKeywordWithCFStringParams.fKeywordMatched =
		((NULL != params.fMatchKeywordWithCFStringParams.fToken) &&
			(CFStringGetLength(params.fMatchKeywordWithCFStringParams.fToken) > 1) &&
			('\\' == CFStringGetCharacterAtIndex(params.fMatchKeywordWithCFStringParams.fToken, 0)) &&
			(! isdigit(CFStringGetCharacterAtIndex(params.fMatchKeywordWithCFStringParams.fToken, 1))));
*/
}

static	void	CanSpellCheckRun(BBLMParamBlock &params)
{
	params.fCanSpellCheckRunParams.fRunCanBeSpellChecked =
		(kBBLMRunIsLineComment != params.fCanSpellCheckRunParams.fRunKind);
}

static void escape_char(BBLMParamBlock &params)
{
	bblmEscCharParams&	esc = params.fEscapeCharParams;
	UInt8*							s = esc.fOutputString;
	UniChar							i = *params.fText;
	
	static const UInt8 hex[] = "0123456789ABCDEF";
	
	if ( i > 0xFF )
	{
		*s++ = 5;
		*s   = '$';
		s   += 4;
	}	
	else
	{
		*s++ = 3;
		*s   = '$';
		s   += 2;
	}
	
	while (s > (esc.fOutputString + 1))
	{
		*s-- = hex[i & 0x000F];
		i >>= 4;
	}
}

extern "C"
{

OSErr TeXMachO(BBLMParamBlock		&params,
						const BBLMCallbackBlock	&bblm_callbacks)
{
	OSErr	err = noErr;
	
	//
	//	a language module must always make sure that the parameter block
	//	is valid by checking the signature, version number, and size
	//	of the parameter block. Note also that version 2 is the first
	//	usable version of the parameter block; anything older should
	//	be rejected.
	//

	//
	//	RMS 010925 the check for params.fVersion > kBBLMParamBlockVersion
	//	is overly strict, since there are no structural changes that would
	//	break backward compatibility; only new members are added.
	//
		
	if ((params.fSignature != kBBLMParamBlockSignature) ||
			(params.fVersion < kBBLMMinimumCompatibleParamBlockVersion))
	{
		return paramErr;
	}
	
	switch (params.fMessage)
	{
		case kBBLMInitMessage:
		case kBBLMDisposeMessage:
			break;
		
		case kBBLMScanForFunctionsMessage:
			ParseTeX(params, bblm_callbacks);
			break;
			
		case kBBLMAdjustRangeMessage:
			
			AdjustRange(params, bblm_callbacks);
			break;
		
		case kBBLMCalculateRunsMessage:
		{
			scan_tex(params, bblm_callbacks);
						
			break;
		}
		
		case kBBLMAdjustEndMessage:
			
			AdjustEnd(params, bblm_callbacks);
			break;
			
		case kBBLMSetCategoriesMessage:
		{
			SInt8*	cat = params.fCategoryParams.fCategoryTable;
			
			cat[(int)'\\'] = '<';
			break;
		}
		
		case kBBLMRunKindForWordMessage:
		{
			match_keyword(params);
			break;
		}
		
		case kBBLMEscapeStringMessage:
			
			escape_char(params);
			break;
		
		case kBBLMCanSpellCheckRunMessage:
			CanSpellCheckRun(params);
			break;
			
		default:
			
			err = paramErr;
			break;
	}
	
	return err;
}
}
