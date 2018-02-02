#pragma once

/*
 *  BBLMToken.h
 *  Generic token class for language parsing in BBEdit Language Modules
 *
 *  Created by Seth Dillingham on 7/18/06.
 *  Copyright 2006 Macrobyte Resources. All rights reserved.
 *
 */

#ifndef BBLMToken_h
#define BBLMToken_h 1

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "BBLMTextIterator.h"

class BBLMToken
{
public:

#pragma mark -
#pragma mark Public
#pragma mark -

#pragma mark De-/Constructors
	
	// default constructor
	BBLMToken()									
		:m_start( 0 ),
		 m_length( 0 )
	{}
	
	// current position
	BBLMToken( BBLMTextIterator& current_position )
		:m_start( current_position.Offset() ),
		 m_length( 0 )
	{}
	
	// current position, length
	BBLMToken( BBLMTextIterator& current_position, SInt32 tokLength )
		:m_start( current_position.Offset() - tokLength ),
		 m_length( tokLength )
	{}
	
	// start offset, length
	BBLMToken( SInt32 tokStart, SInt32 tokLength )
		:m_start( tokStart ),
		 m_length( tokLength )
	{}
	
	BBLMToken( const BBLMToken * originalTok )
		:m_start( originalTok->start() ),
		 m_length( originalTok->length() )
	{}
	
	BBLMToken( const BBLMToken& originalTok )
		:m_start( originalTok.start() ),
		 m_length( originalTok.length() )
	{}
	
	~BBLMToken() { }
	
#pragma mark -
#pragma mark Member Functions
	
	SInt32				start() const {
		return m_start;
	}
	
	
	SInt32				length() const {
		return m_length;
	}
	
	SInt32				end() const {
		return ( ( m_start + m_length > 0 ) ? ( m_start + m_length ) - 1 : -1 );
	}
	
	void				reset() {
		m_start = m_length = 0;
	}
	
	NSRange				range() const {
		return NSMakeRange( m_start, m_length );
	}



protected:

#pragma mark -
#pragma mark Protected
#pragma mark -

	SInt32						m_start;
	
	SInt32						m_length;

private:

	// BBLMToken( const BBLMToken& );  // disallowed
};
#endif
