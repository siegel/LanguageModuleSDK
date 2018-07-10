#include <string.h>

#include "BBLMInterface.h"

#define kMaxLineLength	256

static OSErr add_fold_range(const BBLMCallbackBlock *bblmCallbacks, BBLMProcInfo procInfo)
{
	OSStatus	status = noErr;
	SInt32		funcNameLength = procInfo.fSelEnd - procInfo.fFunctionStart;
	SInt32		foldRangeStart = procInfo.fFunctionStart + (2 * funcNameLength) + 2;
	SInt32		foldRangeLength = procInfo.fFunctionEnd - foldRangeStart - 1;
	
	if (foldRangeLength > 0)
		status = bblmAddFoldRange(bblmCallbacks, foldRangeStart, foldRangeLength, kBBLMGenericAutoFold);
		
	return status;
}

static
OSErr	_ScanForFunctions(const UniChar *text,
							BBLMParamBlock &params,
							const BBLMCallbackBlock *bblmCallbacks)
{
	OSErr			result = noErr;
	UInt32			extent = params.fTextLength;
	UInt32			ix = 0;
	UInt32			count = 0;
	bool			hasTitle = false;
	const UniChar	*curChar = text;
	UniChar			lastLine[kMaxLineLength] = { 0 };
	UniChar			curLine[kMaxLineLength] = { 0 };
	SInt16			lastLength 	= 0;
	SInt16			curLength 	= 0;
	SInt32			lastStart 	= 0;
	SInt32			cur_start 	= 0;
	
	lastLine[lastLength] 	= '\0';
	curLine[curLength]	= '\0';
	
	while ( ( ix < extent ) && ( result == noErr ) )
	{
		curLength = 0;
		cur_start = ix;
		
		while ( ( ix < extent ) && ((! BBLMCharacterIsLineBreak(*curChar))) )
		{
			if ( curLength < ( kMaxLineLength - 1 ) )
				curLine[curLength++] = *curChar;
			curChar++;
			ix++;
		}
		
		curLine[curLength] = 0;
		
		if ((curLength > 0) && (curLength == lastLength))
		{
			//	possible section break
			int		i;
			UniChar	match = ((curLine[0] == '=') ? '=' : '-');
			
			for (i = 0; i < curLength; i++)
			{
				if (curLine[i] != match)
					break;
			}
			
			if ( ( count == 0 ) && ( match == '=' ) )
				hasTitle = true;
			
			//	if all of the characters were '-', then it's a subhead
			//	and we can add it.
			
			if (i == curLength)
			{
				BBLMProcInfo	procInfo = { 0 };
				UInt32			index = 0;

				procInfo.fFunctionStart = lastStart;
				procInfo.fFunctionEnd = procInfo.fFunctionStart + lastLength;
				procInfo.fSelStart = lastStart;
				procInfo.fSelEnd = procInfo.fSelStart + lastLength;
				procInfo.fFirstChar = lastStart;
				
				if ( hasTitle && ( match == '-' ) )
					procInfo.fIndentLevel = 1;
					
				procInfo.fKind = kBBLMFunctionMark;
				procInfo.fFlags = 0;
				procInfo.fNameStart = 0;
				procInfo.fNameLength = lastLength;

				result = bblmAddTokenToBuffer(bblmCallbacks, params.fFcnParams.fTokenBuffer,
												text + lastStart, lastLength,
												&procInfo.fNameStart);
												
				if ( result == noErr )
					result = bblmAddFunctionToList(bblmCallbacks, params.fFcnParams.fFcnList, procInfo, &index);
				count++;
					
				// fix up the previous function entry to get the
				// function range right.
				
				if ((index > 0) && (lastStart > 0))
				{
					BBLMProcInfo	prev_proc;
					
					if ((bblmGetFunctionEntry(bblmCallbacks, params.fFcnParams.fFcnList, index - 1, prev_proc) == noErr) &&
						((! hasTitle) || (prev_proc.fIndentLevel > 0)))
					{
						prev_proc.fFunctionEnd = lastStart - 1;
						
						bblmUpdateFunctionEntry(bblmCallbacks, params.fFcnParams.fFcnList, index - 1, prev_proc);
						add_fold_range(bblmCallbacks, prev_proc);
					}
				}
			}
		}
		
		memmove(lastLine, curLine, curLength + 1);
		lastLength = curLength;
		lastStart = cur_start;
		
		curChar++;
		ix++;
	}
	
	//	tie off the last function entry.
	
	if (count > 0)
	{
		BBLMProcInfo	prev_proc;
		
		if ((bblmGetFunctionEntry(bblmCallbacks, params.fFcnParams.fFcnList, count - 1, prev_proc) == noErr) &&
			((! hasTitle) || (prev_proc.fIndentLevel > 0)))
		{
			prev_proc.fFunctionEnd = extent;
			
			bblmUpdateFunctionEntry(bblmCallbacks, params.fFcnParams.fFcnList, count - 1, prev_proc);
			add_fold_range(bblmCallbacks, prev_proc);
		}
	}
	
	return result;
}

static
OSErr	_ScanForFunctions(BBLMParamBlock &params, const BBLMCallbackBlock *bblmCallbacks)
{
	OSErr	result = noErr;
	
	// we assume that this is zero because the app sets it so
	// for function scanner calls
	require_action(0 == params.fTextGapLength, EXIT, result = paramErr);
	
	require_noerr(result = bblmResetTokenBuffer(bblmCallbacks, params.fFcnParams.fTokenBuffer), EXIT);

	require_noerr(result = bblmResetProcList(bblmCallbacks, params.fFcnParams.fFcnList), EXIT);

	require_noerr(result = _ScanForFunctions(params.fText, params, bblmCallbacks), EXIT);

EXIT:
	return result;
}

#pragma mark -

extern "C"
{

OSErr	SetextMachO(BBLMParamBlock &params, const BBLMCallbackBlock &bblmCallbacks);

OSErr	SetextMachO(BBLMParamBlock &params, const BBLMCallbackBlock &bblmCallbacks)
{
	OSErr	result = noErr;
	
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
		{
			result = noErr;	// nothing to do
			break;
		}
		
		case kBBLMScanForFunctionsMessage:
		{
			result = _ScanForFunctions(params, &bblmCallbacks);
			break;
		}
		
		case kBBLMAdjustRangeMessage:
		case kBBLMCalculateRunsMessage:
		case kBBLMAdjustEndMessage:
		case kBBLMSetCategoriesMessage:
		case kBBLMEscapeStringMessage:
		{
			result = userCanceledErr;
			break;
		}
			
		default:
		{
			result = paramErr;
			break;
		}
	}
	
	return result;
}
}
