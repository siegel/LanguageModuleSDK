#ifndef BBLMTEXTITERATOR_h
#define BBLMTEXTITERATOR_h 1

#include <stddef.h>
#include <ctype.h>
#include <string.h>

#include "BBLMInterface.h"

class BBLMTextIterator
{
	private:
		
		UniChar*	fTextPtr;
		size_t		fTextLen;
		UniChar*	fGapLoc;
		size_t		fGapLen;
		UniChar*	fTextStart;
		UniChar*	fTextEnd;
		
		UniChar* AddOffset(const int32_t offset)
			{
				bool		wasPreGap	= (fTextPtr < fGapLoc);
				UniChar*	result		= fTextPtr + offset;
				
				if (offset < 0)
				{
					if (!wasPreGap && result < (fGapLoc + fGapLen))
						result -= fGapLen;
				}
				else
				{
					if (wasPreGap && result >= fGapLoc)
						result += fGapLen;
				}
				
				return result;
			}
		
	public:
		
		BBLMTextIterator(const BBLMParamBlock& params)
			{
				fTextPtr		= params.fText;
				fTextLen		= params.fTextLength;
				fGapLoc			= fTextPtr + params.fTextGapLocation;
				fGapLen			= params.fTextGapLength;
				fTextStart		= fTextPtr;
				fTextEnd		= fTextStart + fTextLen;
			
				if (fTextStart >= fGapLoc)
					fTextStart += fGapLen;
			
				if (fTextEnd >= fGapLoc)
					fTextEnd += fGapLen;
				
				fTextPtr = fTextStart;
			}

		BBLMTextIterator(const BBLMParamBlock& params, const int32_t offset)
			{
				fTextPtr		= params.fText;
				fTextLen		= params.fTextLength;
				fGapLoc			= fTextPtr + params.fTextGapLocation;
				fGapLen			= params.fTextGapLength;
				fTextStart		= fTextPtr;
				fTextEnd		= fTextStart + fTextLen;
			
				if (fTextStart >= fGapLoc)
					fTextStart += fGapLen;
			
				if (fTextEnd >= fGapLoc)
					fTextEnd += fGapLen;
				
				fTextPtr = fTextStart;
				fTextPtr = AddOffset(offset);
			}
		
		BBLMTextIterator(const BBLMParamBlock& params, const int32_t offset, const int32_t textLength)
			{
				fTextPtr		= params.fText;
				fTextLen		= textLength;
				fGapLoc			= fTextPtr + params.fTextGapLocation;
				fGapLen			= params.fTextGapLength;
				fTextStart		= fTextPtr;
				fTextEnd		= fTextStart + (fTextLen + offset);
			
				if (fTextStart >= fGapLoc)
					fTextStart += fGapLen;
			
				if (fTextEnd >= fGapLoc)
					fTextEnd += fGapLen;
				
				fTextPtr = fTextStart;
				fTextPtr = AddOffset(offset);
			}
		
		BBLMTextIterator(const BBLMTextIterator& iter)
			: fTextPtr  (iter.fTextPtr),   fTextLen(iter.fTextLen),
			  fGapLoc   (iter.fGapLoc),    fGapLen    (iter.fGapLen),
			  fTextStart(iter.fTextStart), fTextEnd   (iter.fTextEnd)
			{ /*...*/ }
		
		BBLMTextIterator(const BBLMTextIterator& iter, const int32_t offset)
			: fTextPtr  (iter.fTextPtr),   fTextLen(iter.fTextLen),
			  fGapLoc   (iter.fGapLoc),    fGapLen    (iter.fGapLen),
			  fTextStart(iter.fTextStart), fTextEnd   (iter.fTextEnd)
			{ fTextPtr = AddOffset(offset); }

		
		UniChar operator*()
			{
				if ((fTextPtr >= fTextEnd) || (fTextPtr < fTextStart))
					return 0;

				return(*fTextPtr);
			}

#if __LP64__
		inline
		UniChar operator[](const CFIndex index)
			{
				UniChar*	result = AddOffset(static_cast<int32_t>(index));
				
				if ((result >= fTextEnd) || (result < fTextStart))
					return 0;
				
				return(*result);
			}

		inline
		UniChar operator[](const UInt32 index)
			{
				UniChar*	result = AddOffset(index);
				
				if ((result >= fTextEnd) || (result < fTextStart))
					return 0;
				
				return(*result);
			}
#endif

		inline
		UniChar operator[](const int32_t index)
			{
				UniChar*	result = AddOffset(index);
				
				if ((result >= fTextEnd) || (result < fTextStart))
					return 0;
				
				return(*result);
			}
		
		void operator ++(int)
			{
				fTextPtr++;
				if (fTextPtr == fGapLoc)
					fTextPtr += fGapLen;
			}
		
		BBLMTextIterator& operator +=(const int32_t delta)
			{ fTextPtr = AddOffset(delta); return *this; }
		
		BBLMTextIterator operator +(const int32_t delta)
			{ return BBLMTextIterator(*this, delta); }
		
		void operator --(int)
			{
				if (fTextPtr == (fGapLoc + fGapLen))
					fTextPtr -= fGapLen;
					
				fTextPtr--;
			}
		
		BBLMTextIterator& operator -=(const int32_t delta)
			{ fTextPtr = AddOffset(-delta); return *this; }
		
		BBLMTextIterator operator -(const int32_t delta)
			{ return BBLMTextIterator(*this, -delta); }
		
		const UniChar* Address(void) const
			{ return fTextPtr; }
		
		int32_t Offset(void) const
			{
				int32_t result = static_cast<int32_t>(fTextPtr - fTextStart);
				
				if (fTextPtr >= fGapLoc && fTextStart < fGapLoc)
					result -= fGapLen;
				
				return result;
			}
		
		void SetOffset(const int32_t newPos)
			{
				int32_t delta = (0 - Offset()) + newPos;
				
				fTextPtr = AddOffset(delta);
			}
		
		size_t CharsLeft(void) const
			{
				//
				//	NB: we can't use fTextLen here because that's the length of the
				//	text in the container. We have to rely on the specified bounds
				//	of the iterator (fTextEnd and fTextStart) and account for the gap
				//	when we do the math.
				//
				int32_t	len = static_cast<int32_t>(fTextEnd - fTextStart);
				int32_t result = 0;
				
				if ((fTextEnd >= fGapLoc) && (fTextStart < fGapLoc))
					len -= fGapLen;
				
				result = len - Offset();
				if (result < 0)
					result = 0;
				
				return result;
			}
		
		bool InBounds()
			{ return (fTextPtr >= fTextStart && fTextPtr < fTextEnd); }
		
		UniChar GetNextChar()
			{
				if (fTextPtr >= fTextEnd)
					return 0;
				
				UniChar result = **this;
				
				(*this)++;
				
				return result;
			}
		
		UniChar GetPrevChar()
			{
				(*this)--;
				
				if (fTextPtr <= fTextStart)
					return '\r';
				
				return (*this)[-1];
			}
		
		template <class CharXX>
		size_t strlen(const CharXX *str)
			{
				size_t len = 0;
				
				str--;
				
				while (*++str != 0)
					len++;
				
				return(len);
			}


		// DRSWAT: function for sanitizing comparison results down to an int that is precisely -1, 0, or 1.
		// Necessary for 64-bit to deal with precision loss compiler errors.
		template <class _signedIntT>
		static inline int MakeComparisonResult(_signedIntT inDelta)
		{
			return (static_cast<int>(inDelta > 0) - static_cast<int>(inDelta < 0));
		}

		template <class CharXX>
		int strcmp(const CharXX *str, size_t n)
			{
				BBLMTextIterator	p = *this;
				unsigned long			c1, c2;
				
				str--;
				n++;
				
				while (--n && fTextPtr < fTextEnd)
				{
					c1 = p.GetNextChar();
					c2 = *++str;
					
					if (c1 != c2)
					{
						long delta = c1 - c2;
						return MakeComparisonResult(delta);
					}
				}
				
				return(0);
			}

		template <class CharXX>
		int strcmp(const CharXX *str)
			{
				return strcmp(str, strlen(str));
			}
		
		template <class CharXX>
		int stricmp(const CharXX *str, size_t n)
			{
				BBLMTextIterator	p = *this;
				unsigned long			c1, c2;
				
				str--;
				n++;
				
				while (--n && fTextPtr < fTextEnd)
				{
					c1 = p.GetNextChar();
					c2 = *++str;
					
					if ((c1 & ~0x7FU) == 0)
						c1 = tolower(static_cast<int>(c1));
					
					if ((c2 & ~0x7FU) == 0)
						c2 = tolower(static_cast<int>(c2));
					
					if (c1 != c2)
					{
						long delta = c1 - c2;
						return MakeComparisonResult(delta);
					}
				}
				
				return(0);
			}
		
		template <class CharXX>
		int stricmp(const CharXX *str)
			{
				return stricmp(str, strlen(str));
			}
};

#endif	// BBLMTEXTITERATOR_h
