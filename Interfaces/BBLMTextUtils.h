/*
 *  BBLMTextUtils.h
 *
 *  Created by Seth Dillingham on 2/14/2008.
 *  Copyright 2008 Macrobyte Resources.
 *
 *  Generic, UniChar-based, utility functions for language modules.
 *  To use it, a language module has to subclass BBLMTextUtils,
 *  such as with YAMLTextUtils or ScalaTextUtils.
 *
 *  Most text-processing methods use a BBLMTextIterator, which is shared
 *  with another object (such as a Tokenizer). So, for example, calling 
 *  skipInlineWhitespace() will cause the "host's" text iterator to be 
 *  incremented so that it points to the first non-inline-whitespace
 *  character that is found at or after the iterator's current position.
 *
 *  HOWEVER, any method whose name ends with "ByIndex" does NOT increment
 *  the TextIterator. Instead, they accept a reference to an offset from the
 *  BBLMTextIterator's current position, and update that offset (the index)
 *  before returning. For an example, see ::skipLineByIndex
 *
 *
 *  NOTE that this class was originally written for the YAML module, and 
 *  and may still have some non-generic stuff that needs to be either 
 *  refactored or moved to a subclass.
 */
 
#ifndef BBLMTextUtils_h
#define BBLMTextUtils_h

#include "BBLMInterface.h"
#include "BBLMTextIterator.h"

#define isByte(c)			( ( (c) & ~0xFF ) == 0 )
#define isBracket(c)		( ( (c) == '(' ) || ( (c) == '{' ) || ( (c) == '[' ) || ( (c) == ']' ) || ( (c) == '}' ) || ( (c) == ')' ) )
#define isHexChar(c)    	( isByte(c) &&											\
                        	  ( ( ( (c) >= '0' ) && ( (c) <= '9' ) ) ||				\
                        		( ( (c) >= 'a' ) && ( (c) <= 'f' ) ) ||				\
                        		( ( (c) >= 'A' ) && ( (c) <= 'F' ) ) ) )

class BBLMTextUtils
{

#pragma mark -
#pragma mark public
public:
	BBLMTextUtils(			BBLMParamBlock &	params,
					const	BBLMCallbackBlock &	bblm_callbacks,
							BBLMTextIterator &	p )
		:m_params( params ),
		 m_bblm_callbacks( bblm_callbacks ),
		 m_p( p ),
		 m_inlineWhiteCharSet( NULL ),
		 m_breakCharSet( NULL ),
		 m_EOLCharSet( NULL )
	{
		m_inlineWhiteCharSet = CFCharacterSetCreateMutable( kCFAllocatorDefault );
		
		m_breakCharSet = CFCharacterSetCreateMutable( kCFAllocatorDefault );
		
		m_EOLCharSet = CFCharacterSetCreateMutable( kCFAllocatorDefault );
		
		this->initEOLChars();
		this->initWhitespace();
	}
	
	virtual ~BBLMTextUtils()
	{
		if ( NULL != m_inlineWhiteCharSet )
		{
			CFRelease( m_inlineWhiteCharSet );
			
			m_inlineWhiteCharSet = NULL;
		}
		
		if ( NULL != m_breakCharSet )
		{
			CFRelease( m_breakCharSet );
			
			m_breakCharSet = NULL;
		}
		
		if ( NULL != m_EOLCharSet )
		{
			CFRelease( m_EOLCharSet );
			
			m_EOLCharSet = NULL;
		}
	}
	
	
			bool			isBreakChar( UniChar );
	
			bool			isInlineWhiteChar( UniChar );
			
			bool			isEOLChar( UniChar );
			
	inline	UniChar			LowerChar( UniChar c ) {
								return ( ( c >= 'A' ) && ( c <= 'Z' ) ) ? c + ( 'a' - 'A' ) : c;
							}

	
	
	#pragma mark -
	#pragma mark Skippers
	
			bool			skipWhitespace();
			
			
			bool			skipInlineWhitespace();
			
			bool			skipInlineWhitespace( SInt32 & );
			
			bool			skipInlineWhitespace( BBLMTextIterator & p );
			
			bool			skipInlineWhitespace( SInt32 &, BBLMTextIterator & );
			
			
			bool			skipInlineWhitespaceByIndex( SInt32 & index ) {
								return this->skipInlineWhitespaceByIndex( m_p, index );
							}
			
			bool			skipInlineWhitespaceByIndex( BBLMTextIterator &, SInt32 & index );
			
			
			void			skipPreviousInlineWhitespace();
			
			void			skipPreviousInlineWhitespaceByIndex( SInt32 & index ) {
								return this->skipPreviousInlineWhitespaceByIndex( m_p, index );
							}
			
			void			skipPreviousInlineWhitespaceByIndex( BBLMTextIterator &, SInt32 & );
			
	
			bool			skipLine() {
								return this->skipLine( m_p );
							}
			
			bool			skipLine( BBLMTextIterator & );
			
	inline	bool			skipLineByIndex( SInt32 & index ) {
								return this->skipLineByIndex( m_p, index );
							}
			
			bool			skipLineByIndex( BBLMTextIterator &, SInt32 & );
			
			bool			skipLineWithMaxIndexByIndex( SInt32 &, SInt32 );
			
	inline	bool			skipToEOL() {
								return this->skipToEOL( m_p );
							}
			
			bool			skipToEOL( BBLMTextIterator & p );
			
			SInt32			findLineEndBeforeIndex( SInt32 );
			
			SInt32			findLineEndAfterIndex( SInt32 );
			
	virtual	bool			skipWord() = 0;
			
	virtual	bool			skipWordByIndex( SInt32 & ) = 0;
	
			bool			matchChars( const char * );
			
			bool			imatchChars( const char * );
			
	virtual	bool			matchWord( const char * pat ) = 0;
	
	virtual	bool			imatchWord( const char * pat ) = 0;
			
			bool			skipToCharByIndex( UniChar, SInt32 &, bool );
			
			bool			skipToCharSameLineByIndex( UniChar, SInt32 & );
			
	inline	bool			skipGroupByIndexCountingLines( SInt32 & index, const UniChar breakChar, SInt32 & ctLines ) {
								return this->skipGroupByIndexCountingLines( m_p, index, breakChar, ctLines );
							}
	
			bool			skipGroupByIndexCountingLines( BBLMTextIterator &, SInt32 &, const UniChar, SInt32 & );
			
			bool			rightTrimByIndex( SInt32, SInt32 );
			
	virtual	bool			skipDelimitedStringByIndex( SInt32 & ) = 0;
			
			bool			skipDelimitedStringByIndex( SInt32 & /* index */, bool /* flAllowEOL */,
							                            bool /* flAllowEscape */, bool /* flAllowEscapedEOL */ );
			
			SInt32			copyCollapsedRangeToBuffer( SInt32 &, SInt32 &, UniChar *, NSUInteger );
			
			CFStringRef		createCFStringFromOffsets( SInt32 &, SInt32 &, SInt32 );
			
			CFStringRef		createCFStringFromOffsetsWithPrefix( SInt32 &, SInt32 &, SInt32, CFStringRef );
			
			UInt32			countLinesInRange( UInt32 rangeStart, UInt32 rangeEnd, UInt32 maxLinesToFind);
	
	
	typedef enum BBLMTUNumberType {
		kBBLMTUUnknown,
		kBBLMTULong,
		kBBLMTUOctal,
		kBBLMTUBinary,
		kBBLMTUHex,
		kBBLMTUFloat,
		kBBLMTUScientific,
		kBBLMTUImaginary
	} BBLMTUNumberType;
	
	inline	bool			skipBinary() {
								BBLMTUNumberType nt = kBBLMTUUnknown;
								
								return this->skipBinary( nt );
							}
			
			bool			skipBinary( BBLMTUNumberType & );
			
	
	inline	bool			skipHex() {
								BBLMTUNumberType nt = kBBLMTUUnknown;
								
								return this->skipHex( nt );
							}
			
			bool			skipHex( BBLMTUNumberType & );
			
	
	inline	bool			skipFloat() {
								BBLMTUNumberType nt = kBBLMTUUnknown;
								
								return this->skipFloat( nt );
							}
			
			bool			skipFloat( BBLMTUNumberType & );
			
			
	inline	bool			skipOctal() {
								BBLMTUNumberType nt = kBBLMTUUnknown;
								
								return this->skipOctal( nt );
							}
			
			bool			skipOctal( BBLMTUNumberType & );
			
			
	inline	bool			skipNumber() {
								BBLMTUNumberType nt = kBBLMTUUnknown;
								
								return this->skipNumber( nt );
							}

			bool			skipNumber( BBLMTUNumberType & );
			

#pragma mark -
#pragma mark protected
protected:

			BBLMParamBlock &			m_params;
	
	const	BBLMCallbackBlock &			m_bblm_callbacks;
	
			BBLMTextIterator &			m_p;
	
	#pragma mark -
	#pragma mark Character Tests
	
			void			addBreakChar( UniChar c );
			
			void			addBreakChars( CFStringRef );
	
			void			clearBreakChar( UniChar );
			
			void			clearBreakChars( CFStringRef );
						
	virtual	void			initBreaks() = 0;
			
private:
			void			addCharsToSet( CFStringRef, CFMutableCharacterSetRef );
			void			addCharToSet( UniChar, CFMutableCharacterSetRef );
			
			void			removeCharsFromSet( CFStringRef, CFMutableCharacterSetRef );
			void			removeCharFromSet( UniChar, CFMutableCharacterSetRef );
	

			void			initWhitespace();
			void			initEOLChars();
			
#pragma mark -
#pragma mark private
private:
			
			CFMutableCharacterSetRef	m_inlineWhiteCharSet;
			
			CFMutableCharacterSetRef	m_breakCharSet;
			
			CFMutableCharacterSetRef	m_EOLCharSet;
};

#endif  // BBLMTextUtils_h
