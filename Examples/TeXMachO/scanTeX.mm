//	-*- tab-width: 2; -*-

#include "TeXModule.h"

void scan_tex(			BBLMParamBlock    &params,
							const BBLMCallbackBlock &callbacks,
							const BBXTCallbackBlock& /*bbxt_callbacks*/,
										bool							colorMathStrings)
{
	UInt16	c;
	long		start, pos, end;
	int			runKind;
	
	BBLMTextIterator p(params);
	
	start = params.fCalcRunParams.fStartOffset;
	end = start;
	
	p += start;
	
	runKind = kBBLMRunIsCode;
	c       = '\r';
	
	for (;;)
	{
		switch (runKind)
		{
			case kBBLMRunIsCode:
			continueCCode:

					do
						c = p.GetNextChar();
					while (c && c != '\\' && c != '%' && c != '$');
				
				if (!c)
				{
					if (p.InBounds())
						goto continueCCode;
					end = p.Offset();
				}
				else if (c == '\\')
				{
					c = p.GetNextChar();
					goto continueCCode;
				}
				else if (c == '$')
				{
					if (! colorMathStrings)
						goto continueCCode;

					runKind = kBBLMRunIsSingleString;
					end = p.Offset() - 1;
				}
				else if (c == '%')
				{
					pos = p.Offset();
					if ((pos > 1) && (p[-2] == '\\'))
						goto continueCCode;
						
					runKind = kBBLMRunIsLineComment;
					end = pos - 1;
				}
				
				if (end != start && !bblmAddRun(&callbacks, params.fLanguage, kBBLMRunIsCode, start, end - start))
					goto Exit;
				
				start = end;
				
				break;
			

		case kBBLMRunIsLineComment:
			continueCSlashComment:
			
				do
					c = p.GetNextChar();
				while (c && c != '\r');
				
				if (!c)
				{
					if (p.InBounds())
						goto continueCSlashComment;
				}
				
				pos = p.Offset();
				
				if (!bblmAddRun(&callbacks, params.fLanguage, kBBLMRunIsLineComment, start, pos - start))
					goto Exit;
				
				runKind = kBBLMRunIsCode;
				start   = pos;
				
				break;

			case kBBLMRunIsSingleString:
			{
				Boolean is_double;
				
				c = p.GetNextChar();
				
				if (!(is_double = (c == '$')))
					c = p.GetPrevChar();
				
			continueCSingleString:
				
				do
					c = p.GetNextChar();
				while (c && c != '$' && c != '\\');
				
				if (!c)
				{
					if (p.InBounds())
						goto continueCSingleString;
				}
				
				if (c == '\\')
				{
					c = p.GetNextChar();
					goto continueCSingleString;
				}
				
				if (is_double)
				{
					c = p.GetNextChar();
					if (c && (c != '$'))
					{
						c = p.GetPrevChar();
						goto continueCSingleString;
					}
				}
				
				pos = p.Offset();
				
				if (!bblmAddRun(&callbacks, params.fLanguage, kBBLMRunIsSingleString, start, pos - start))
					goto Exit;
				
				runKind = kBBLMRunIsCode;
				start   = pos;
				
				break;
			}

		}
		
		if (!p.InBounds())
			break;
	}
	
Exit: ;
}
