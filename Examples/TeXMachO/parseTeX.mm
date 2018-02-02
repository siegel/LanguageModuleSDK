#include	<setjmp.h>

#include	"TeXModule.h"

#define 		kMaxTokLen			256

static			BBLMParamBlock*		params;
static const	BBLMCallbackBlock*	callbacks;
static 			BBLMTextIterator*	iter;
static 			UInt16				curr_char;
static 			SInt32				line_start;
static			jmp_buf				jmp_eof;

static void GetNextChar()
{
	(*iter)++;
	
	if (iter->InBounds())
	{
		curr_char = **iter;
		
		if (curr_char == '\r')
			line_start = iter->Offset() + 1;
	}
	else
		longjmp(jmp_eof, 1);
}

static void Skip(int n)
{
	for (int i = 0; i < n; i++)
		GetNextChar();
}

static void SkipWS()
{
	while ((curr_char & 0xFF00) == 0 && isspace(curr_char))
		GetNextChar();
}

static void memcpy16to8(UInt8* dst, const UInt16* src, size_t n)
{
	for (src--, dst--, n++; --n;)
		*++dst = *++src;
}

static bool add_token(UInt16* tok, int len, BBLMProcInfo info)
{
	bool ok;
	
	ok = (bblmAddTokenToBuffer(callbacks, params->fFcnParams.fTokenBuffer,
									tok, len, &info.fNameStart) == noErr);

	if (ok)
		ok = (bblmAddFunctionToList(callbacks, params->fFcnParams.fFcnList, info, nil) == noErr); 
	
	return ok;
}

static void comment(void)
{
	while (curr_char != '\r')
		GetNextChar();
}

static void expr(void)
{
	Boolean	is_double = false;

	GetNextChar();
	
	if (curr_char == '$')
	{
		is_double = true;
		GetNextChar();
	}
	
top:
	
	while (curr_char != '$')
		GetNextChar();
	
	if (is_double)
	{
		GetNextChar();
		if (curr_char != '$')
			goto top;
	}
}

static bool section(char sub)
{
	bool ok = true;
	
	SkipWS();
	
	if (curr_char == '*')
		GetNextChar();
	
	if (curr_char == '[')
	{
		while (curr_char != ']')
		{
			if (curr_char == '\\')
				GetNextChar();
			
			GetNextChar();
		}
		
		GetNextChar();
	}
		
	if (curr_char == '{')
	{
		UInt16	tok[kMaxTokLen];
		int		len = 0;
		
		GetNextChar();
		
		BBLMProcInfo info;
		
		memset(&info, 0, sizeof(info));
		info.fFunctionStart =
		info.fSelStart = iter->Offset();
		info.fFirstChar = line_start;
		
		while (len < kMaxTokLen - 3 && curr_char != '}')
		{
			if (curr_char == '\r')
				tok[len++] = ' ';
			else
				tok[len++] = curr_char;
				
			if (curr_char == '$')
			{
				tok[len++] = 0xC9;	//	MacRoman ellipsis
				tok[len++] = '$';
				expr();
			}
			
			GetNextChar();
		}
		
		while (curr_char != '}')
		{
			if (curr_char == '$')
				expr();
			
			GetNextChar();
		}
		
		info.fNameLength = len;
		info.fIndentLevel = sub;
		info.fFunctionEnd = iter->Offset() + 1;
		info.fSelEnd = iter->Offset();
		
		if (!add_token(tok, len, info))
			ok = false;
	}

	return ok;
}

static bool begin(void)
{
	bool ok = true;
	int	len = 0;
	
	SkipWS();
	
	if (curr_char == '{')
	{
		UInt16	tok[kMaxTokLen];
		
		GetNextChar();
		
		BBLMProcInfo info;
		
		memset(&info, 0, sizeof(info));
		info.fFunctionStart =
		info.fSelStart = iter->Offset();
		info.fFirstChar = line_start;
		
		while (len < kMaxTokLen && curr_char != '}')
		{
			tok[len++] = curr_char;
			GetNextChar();
		}
		
		while (curr_char != '}')
			GetNextChar();
		
		info.fNameLength = len;
		info.fFunctionEnd =
		info.fFunctionEnd = iter->Offset() + 1;
		info.fSelEnd = iter->Offset();
		info.fFlags = kBBLMIsPrototype;
		
		if (!add_token(tok, len, info))
			ok = false;
	}
	
	return ok;
}

void	ParseTeX(BBLMParamBlock &bblm_params, const BBLMCallbackBlock &bblm_callbacks)
{
	BBLMTextIterator loc_iter(bblm_params);
	
	params		= &bblm_params;
	callbacks	= &bblm_callbacks;
	iter		= &loc_iter;
	line_start	= iter->Offset();
	
	if (iter->InBounds())
		curr_char = **iter;
	else
		curr_char = 0;
	
	if (0 == setjmp(jmp_eof))
	{
		bool ok = true;
	
		while (ok)
		{
			SkipWS();
			
			switch (curr_char)
			{
				case '\\':
					
					GetNextChar();
					
					if (iter->stricmp("section") == 0)
					{
						Skip(7);
						ok = section(0);
					}
					else if (iter->strcmp("chapter") == 0)
					{
						Skip(7);
						ok = section(0);
					}
					else if (iter->strcmp("paragraph") == 0)
					{
						Skip(9);
						ok = section(1);
					}
					else if (iter->strcmp("sub") == 0)
					{
						char	sub = 0;
						
						while (iter->strcmp("sub") == 0)
						{
							sub++;
							Skip(3);
						}
						
						if (iter->strcmp("chapter") == 0)
						{
							Skip(7);
							ok = section(sub);
						}
						else if (iter->strcmp("paragraph") == 0)
						{
							Skip(9);
							ok = section(sub + 1);
						}
						else if (iter->strcmp("section") == 0)
						{
							Skip(7);
							ok = section(sub);
						}
					}
					else if ((iter->stricmp("begin") == 0) &&
								((params->fFcnParams.fOptionFlags & kBBLMShowPrototypes) != 0))
					{
						Skip(5);
						ok = begin();
					}
					
					break;
				
				case '$':
					expr();
					break;
					
				case '%':
					comment();
					break;
			}
			
			GetNextChar();
		}
	}
}
