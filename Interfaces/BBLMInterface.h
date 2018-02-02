//	-*- mode: objective-c++; coding: utf-8; -*-

#ifndef BBLMINTERFACE_h
#define BBLMINTERFACE_h 1

#ifndef __ASSERTMACROS__
#define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES	1
#include <AssertMacros.h>
#endif

enum
{
	kBBLMCurrentCallbackVersion = 0x00000007
};

typedef	enum
{
	kBBLMFunctionMark,
	kBBLMTypedef,
	kBBLMPragmaMark,
	kBBLMInclude,
	kBBLMSysInclude,
	
	//
	//	the following collection of function types is for comments with specific
	//	"callout" formations. If you have a formation that doesn't fit one of these,
	//	use kBBLMNoteCallout.
	//
	kBBLMFixMeCallout,		//	example: /* FIXME: this won't work in Y2K */
	kBBLMToDoCallout,		//	example: /* TODO: add support for blargh */
	kBBLMReviewCallout,		//	example: /* REVIEW for correctness */
	kBBLMQuestionCallout,	//	example: /* ???:correia:20080717 what should the final value really be here? */
	kBBLMWarningCallout,	//	example: /* !!!:siegel: this looks wrong to me */
	kBBLMNoteCallout,		//	example: /* NOTE: You should always check for NULL here */
	
	kBBLMURLInclude,
	kBBLMSiteRelativeInclude,
	
	kBBLMFunctionEnumDeclaration,
	kBBLMFunctionStructDeclaration,
	kBBLMFunctionUnionDeclaration,
	kBBLMFunctionClassDeclaration,
	kBBLMFunctionProtocolDeclaration,
	kBBLMFunctionClassInterface,
	kBBLMFunctionClassImplementation,
	kBBLMFunctionInstanceVariable,
	kBBLMFunctionMethod,
	kBBLMFunctionPropertyDeclaration,
	kBBLMFunctionPropertySynthesis,
	kBBLMFunctionSGMLNamedID,
	kBBLMFunctionHTMLNamedAnchor,
	kBBLMFunctionHTMLHeading1,
	kBBLMFunctionHTMLHeading2,
	kBBLMFunctionHTMLHeading3,
	kBBLMFunctionHTMLHeading4,
	kBBLMFunctionHTMLHeading5,
	kBBLMFunctionHTMLHeading6,
	
	kBBLMLastUsedFunctionKind,	//	do not change or use this value; it should always
								//	occur after the last factory defined value
	kBBLMLastCoreFunctionKind = 31,
	kBBLMReservedFunctionKind,		//	do not generate any function entries with this kind!
	kBBLMFirstUserFunctionKind,
    
    // moved from HTMLFunctionScanner because they were used in a switch statement, and LLVM 4 noticed they weren't "real" BBLMFunctionKinds
    kHTMLFunctionJavascriptRun = 255,
    kHTMLFunctionPHPRun = 254,
    kHTMLFunctionCSSRun	= 253,
    kHTMLFunctionJSPRun = 252,
    kHTMLFunctionASPRun = 251,
    kHTMLFunctionRubyRun = 250

} BBLMFunctionKinds;

#define	kBBLMFunctionTypeGeneral				@"com.barebones.bblm.function-type.function"
#define	kBBLMFunctionTypeTypedef				@"com.barebones.bblm.function-type.typedef"
#define	kBBLMFunctionTypeNamedMark				@"com.barebones.bblm.function-type.named-mark"
#define	kBBLMFunctionTypeInclude				@"com.barebones.bblm.function-type.include"
#define	kBBLMFunctionTypeSystemInclude			@"com.barebones.bblm.function-type.include.system"
#define	kBBLMFunctionTypeFIXMECallout			@"com.barebones.bblm.function-type.callout.fixme"
#define	kBBLMFunctionTypeTODOCallout			@"com.barebones.bblm.function-type.callout.to-do"
#define	kBBLMFunctionTypeREVIEWCallout			@"com.barebones.bblm.function-type.callout.review"
#define	kBBLMFunctionTypeQuestionCallout		@"com.barebones.bblm.function-type.callout.question"
#define	kBBLMFunctionTypeWarningCallout			@"com.barebones.bblm.function-type.callout.warning"
#define	kBBLMFunctionTypeNoteCallout			@"com.barebones.bblm.function-type.callout.note"
#define kBBLMFunctionTypeClassDeclaration		@"com.barebones.bblm.function-type.class-declaration"
#define	kBBLMFunctionTypeProtocolDeclaration	@"com.barebones.bblm.function-type.protocol-declaration"
#define	kBBLMFunctionTypeClassInterface			@"com.barebones.bblm.function-type.class-interface"
#define	kBBLMFunctionTypeClassImplementation	@"com.barebones.bblm.function-type.class-implementation"
#define	kBBLMFunctionTypeInstanceVariable		@"com.barebones.bblm.function-type.ivar"
#define	kBBLMFunctionTypeMethod					@"com.barebones.bblm.function-type.method"
#define	kBBLMFunctionTypePropertyDeclaration	@"com.barebones.bblm.function-type.property.declaration"
#define	kBBLMFunctionTypePropertySynthesis		@"com.barebones.bblm.function-type.property.synthesis"
#define	kBBLMFunctionTypeEnumeration			@"com.barebones.bblm.function-type.enumeration"
#define	kBBLMFunctionTypeStructureDeclaration	@"com.barebones.bblm.function-type.structure"
#define	kBBLMFunctionTypeUnionDeclaration		@"com.barebones.bblm.function-type.union"
#define	kBBLMFunctionTypeSGMLNamedID			@"com.barebones.bblm.function-type.sgml-named-id"
#define	kBBLMFunctionTypeHTMLNamedAnchor		@"com.barebones.bblm.function-type.html-named-anchor"
#define	kBBLMFunctionTypeHTMLHeading1			@"com.barebones.bblm.function-type.html-named-heading-1"
#define	kBBLMFunctionTypeHTMLHeading2			@"com.barebones.bblm.function-type.html-named-heading-2"
#define	kBBLMFunctionTypeHTMLHeading3			@"com.barebones.bblm.function-type.html-named-heading-3"
#define	kBBLMFunctionTypeHTMLHeading4			@"com.barebones.bblm.function-type.html-named-heading-4"
#define	kBBLMFunctionTypeHTMLHeading5			@"com.barebones.bblm.function-type.html-named-heading-5"
#define	kBBLMFunctionTypeHTMLHeading6			@"com.barebones.bblm.function-type.html-named-heading-6"

typedef	enum
{
	kBBLMIsPrototype		=	0x00000001,
	kBBLMIsForwardDecl		=	0x00000002
} BBLMFunctionFlags;

typedef	enum
{
	//
	//	Beginning with BBEdit 9.2, these three bits are always set;
	//	you should always generate entries for prototypes, includes,
	//	and callouts when appropriate.
	//
	
	kBBLMShowPrototypes		=	0x00000001,
	kBBLMShowIncludes		=	0x00000002,
	kBBLMShowCommentCallouts=	0x00000004
} BBLMFcnOptionFlags;

//
//    You are encouraged to generate runs with these run kinds wherever
//    possible. Do *not* add your own run kinds that begin with
//    "com.barebones"; instead, use your own reverse-domain-name space
//    (starting with your bundle ID) for your custom run kinds. The
//    language module documentation contains complete information.
//

#define	kBBLMCodeRunKind					@"com.barebones.bblm.code"
#define	kBBLMPreprocessorRunKind			@"com.barebones.bblm.preprocessor"
#define	kBBLMPostPreprocessorRunKind		@"com.barebones.bblm.postpreprocessor"
#define	kBBLMCommentRunKind					@"com.barebones.bblm.comment"			//	use for languages that don't distinguish between...
#define	kBBLMLineCommentRunKind				@"com.barebones.bblm.line-comment"		//		...a "rest of line" comment, e.g. "//" in C or "#" in Ruby
#define	kBBLMBlockCommentRunKind			@"com.barebones.bblm.block-comment"		//		...a begin/end delimited comment, e.g. /*...*/ in C
#define	kBBLMStringRunKind					@"com.barebones.bblm.string"			//	use for languages that don't distinguish between...
#define	kBBLMSingleQuotedStringRunKind		@"com.barebones.bblm.single-string"		//		...a single-quoted string, e.g. 'a' in C
#define	kBBLMDoubleQuotedStringRunKind		@"com.barebones.bblm.double-string"		//		...a double-quoted string, e.g. "hello world" in C
#define	kBBLMHereDocStringRunKind			@"com.barebones.bblm.heredoc-string"	//		...a "here doc" string as used in many scripting languages
#define	kBBLMNumberRunKind					@"com.barebones.bblm.number"
#define	kBBLMFileIncludeRunKind				@"com.barebones.bblm.file-include"
#define	kBBLMVariableRunKind				@"com.barebones.bblm.variable"
#define	kBBLMKeywordRunKind					@"com.barebones.bblm.keyword"
#define kBBLMSyntaxErrorRunKind				@"com.barebones.bblm.syntax-error"
#define	kBBLMPredefinedSymbolRunKind		@"com.barebones.bblm.predefined-symbol"
#define	kBBLMIndexedSymbolRunKind			@"com.barebones.bblm.indexed-symbol"
#define	kBBLMSGMLCDATARunKind				@"com.barebones.bblm.sgml-cdata"		//	SGML unparsed character data (i.e. inside of a <![CDATA...]> block)
#define	kBBLMSGMLPCDATARunKind				@"com.barebones.bblm.sgml-pcdata"		//	SGML parsed character data (i.e. things not in tags)
#define	kBBLMSGMLEntityRunKind				@"com.barebones.bblm.sgml-entity"		//	an SGML/HTML/XML entity (named or numeric)
#define	kBBLMSGMLDeclarationRunKind			@"com.barebones.bblm.sgml-decl"			//	<! ... > (not including comments)
#define	kBBLMSGMLTagRunKind					@"com.barebones.bblm.sgml-tag"			//	singleton SGML/HTML tags, e.g. <br>
#define	kBBLMSGMLOpenTagRunKind				@"com.barebones.bblm.sgml-open-tag"		//	openers such as <ul>
#define	kBBLMSGMLCloseTagRunKind			@"com.barebones.bblm.sgml-close-tag"	//	closers for openers (e.g. </ul>)
#define kBBLMXMLPIRunKind					@"com.barebones.bblm.xml-pi"			//	processing instructions: <?...>
#define	kBBLMXMLEmptyTagRunKind				@"com.barebones.bblm.xml-empty"			//	empty XML tags e.g. <hr />

#define	kBBLMEmbeddedLanguageStartRunKind	@"com.barebones.bblm.embedded-start"	// zero-length runs, marking start or end
#define	kBBLMEmbeddedLanguageEndRunKind		@"com.barebones.bblm.embedded-end"		// of languages, such as javascript in html

enum
{
	//
	//	these are values for the result from
	//	kBBLMGuessLanguageMessage. Note that you should not return a
	//	value greater than kBBLMGuessDefiniteYes, or else guessing
	//	will not work correctly.
	//
	
	kBBLMGuessDefiniteNo,
	kBBLMGuessMaybe			=	127,
	kBBLMGuessDefiniteYes	=	255
};

enum
{
	kBBLMManualFold				=  0,
	kBBLMGenericAutoFold		=  1,
	kBBLMModuleAutoFold			=  2,
	kBBLMClassAutoFold			=  3,
	kBBLMFunctionAutoFold		=  4,
	kBBLMDataAutoFold			=  5,
	kBBLMBlockCommentAutoFold	=  6,
	kBBLMHereDocAutoFold		=  7,
	
	kBBLMLastFoldKind			= 31
};

typedef	UInt32	BBLMFoldKind;

typedef	SInt8	BBLMCategoryTable[256];
typedef	SInt8	BBLMUnicodeCategoryTable[65536];

typedef	enum
{
	kBBLMNullMessage,						//	reserved
	
	kBBLMInitMessage,						//	the language module should perform any global initializations
	kBBLMDisposeMessage,					//	the language module is being shut down forever; time to clean up

	kBBLMScanForFunctionsMessage,			//	generate a list of functions in the supplied text.
											//	relevant parameters are in fFcnParams of the BBLMParamBlock
											
	kBBLMAdjustRangeMessage,				//	adjust indices of first and last language run to be rescanned
	
	kBBLMCalculateRunsMessage,				//	generate a list of language runs in the supplied text
											//	relevant parameters are in fCalcRunParams of the BBLMParamBlock
											
	kBBLMAdjustEndMessage,					//	adjust offset to last character in text that needs to be redrawn
	
	kBBLMSetCategoriesMessage,				//	configure character categories
	
	kBBLMEscapeStringMessage,				//	escape a string
		
	kBBLMGuessLanguageMessage,				//	figure out whether the provided text is in our language
	
	kBBLMWordLeftStringMessage,				// 	return a PCRE pattern C-string ptr for a word-left search
	
	kBBLMWordRightStringMessage,			// 	return a PCRE pattern C-string ptr for a word-right search
	
	kBBLMScanForFoldRangesMessage,			//	generate a list of text ranges that may be of interest
											//	for folding purposes

	kBBLMCanSpellCheckRunMessage,			//	return whether the given run of text can be spell checked

	kBBLMScanSubrangeForFunctionsMessage,	//	like kBBLMScanForFunctionsMessage, but takes a range of text
											//	to scan rather than requiring examination of the whole file

	kBBLMCreateSupportedLanguagesDictionary,//	if the module has a skeleton bblm info that indicates that it
											//	should be asked for the supported languages dictionary, it
											//	will get called with this message. Note that this call is
											//	a "create"; your module should either return a copy or retain
											//	the value that it's about to return, because the application will
											//	release it when it's done.

	kBBLMFindEndOfEmbeddedLanguageMessage,	//	ask a "parent" language's module to find the end of an embedded
											//	language (essentially, the start of the "closing" delimiter)
											//	so that we'll know how to set the fTextLength when we send the 
											//	kBBLMCalculateRunsMessage to the embedded language's module
											
	kBBLMAdjustRangeForTextCompletion,		//	if kBBLMSupportsTextCompletion is set, this message may
											//	be sent to ask the module to adjust the proposed character
											//	range prior to being sent a kBBLMCreateTextCompletionArray
											//	message

	kBBLMFilterRunForTextCompletion,		//	if kBBLMSupportsTextCompletion is set, this message may
											//	be sent to ask the module if tokens in the given run of
											//	text may be considered for completion (based on the run
											//	kind and any other contextual information that the module
											//	cares to use).
											
	kBBLMSetCategoriesForTextCompletionMessage,
											//	if kBBLMSupportsTextCompletion is set, this message may
											//	be sent to return a custom category table to be used for
											//	computing tokens during text completion. If you receive
											//	this message, you may either handle it as though you had
											//	received a kBBLMSetCategoriesMessage, or you may return
											//	a custom category table.
											//
											
	kBBLMCreateTextCompletionArray,			//	if kBBLMSupportsTextCompletion is set, this message may
											//	be sent to ask the module to return an array of possible
											//	completions

	kBBLMCreateURLByResolvingIncludeFileMessage,
											//	if kBBLMCanResolveIncludeFiles is set, this message will be
											//	sent to ask the module to return a URL to the included
											//	file on disk (or elsewhere)
	
	kBBLMRunKindForWordMessage,				//	If the module has BBLMSupportsWordLookup = YES, this
											//	message will be sent to ask the module for the run kind
											//	corresponding to a particular word. (This replaces
											//	kBBLMMatchKeywordWithCFStringMessage and 
											//	kBBLMMatchPredefinedNameMessage from the old API.)

	kBBLMAutoPairMessage,					//	When called, the editor is considering auto-pairing
											//	a typed character.
											
	kBBLMLastMessage
} BBLMMessage;

#if (! __LP64__)
#pragma pack(push, 2)
#endif

//	BBLMProcInfo - generated and used by the function scanner

typedef	struct BBLMProcInfo
{
	UInt32	fFunctionStart;	//	char offset in file of first character of function
	UInt32	fFunctionEnd;	//	char offset of last character of function
	
	UInt32	fSelStart;		//	first character to select when choosing function
	UInt32	fSelEnd;		//	last character to select when choosing function
	
	UInt32	fFirstChar;		//	first character to make visible when choosing function
	
	UInt32	fIndentLevel;	//	indentation level of token
	UInt32	fKind;			//	token kind (see BBLMFunctionKinds for core kinds)
	UInt32	fFlags;			//	token flags (see BBLMFunctionFlags)
	UInt32	fNameStart;		//	char offset in token buffer of token name
	SInt32	fNameLength;	//	length of token name
} BBLMProcInfo;

//
//	BBLMRunRec - generated and used by the syntax coloring machinery
//

#if __LP64__

typedef struct
{
	OSType			language;
	NSString		*runKind /* this value is neither retained nor released */;
	SInt32			startPos;
	SInt32			length;
	UInt16			depth;
} BBLMRunRec;

#else

#pragma pack(push, 1)
typedef struct
{
	OSType			language;
	NSString		*runKind /* this value is neither retained nor released */;
	SInt32			startPos;
	unsigned int	length : 24;
	unsigned int	depth : 8;
} BBLMRunRec;
#pragma pack(pop)

#endif

//
//	Dictionary keys for the array returned by kBBLMCreateSymbolCompletionArray message
//

#define	kBBLMCompletionSymbolType				CFSTR("SymbolType")		//	CFStringRef; describes the kind of symbol
//	Recommended values for kBBLMCompletionSymbolType. If you define your own, they should
//	begin with your language module's bundle identifier to eliminate the possibility of
//	conflicts. (Using your bundle ID will also make future UI enhancements possible.)
//	Use kBBLMSymbolTypeGenericIdentifier if all else fails.
#define		kBBLMSymbolTypeCallout				CFSTR("com.barebones.bblm.callout")
#define		kBBLMSymbolTypeClass				CFSTR("com.barebones.bblm.class")
#define		kBBLMSymbolTypeCSSPropertyName		CFSTR("com.barebones.bblm.cssPropertyName")
#define		kBBLMSymbolTypeEnumerationName		CFSTR("com.barebones.bblm.enumName")
#define		kBBLMSymbolTypeEnumerationValue		CFSTR("com.barebones.bblm.enumValue")
#define		kBBLMSymbolTypeExternVariable		CFSTR("com.barebones.bblm.externVar")
#define		kBBLMSymbolTypeFunction				CFSTR("com.barebones.bblm.function")
#define		kBBLMSymbolTypeFunctionPrototype	CFSTR("com.barebones.bblm.prototype")
#define		kBBLMSymbolTypeGenericIdentifier	CFSTR("com.barebones.bblm.identifier")
#define		kBBLMSymbolTypeGlobalVariable		CFSTR("com.barebones.bblm.globalVar")
#define		kBBLMSymbolTypeIncludeFile			CFSTR("com.barebones.bblm.includeFile")
#define		kBBLMSymbolTypeIVar					CFSTR("com.barebones.bblm.ivar")
#define		kBBLMSymbolTypeLanguageKeyword		CFSTR("com.barebones.bblm.keyword")
#define		kBBLMSymbolTypeLocalVariable		CFSTR("com.barebones.bblm.localVar")
#define		kBBLMSymbolTypeMacro				CFSTR("com.barebones.bblm.#define")
#define		kBBLMSymbolTypeMember				CFSTR("com.barebones.bblm.member")
#define		kBBLMSymbolTypeMethod				CFSTR("com.barebones.bblm.method")
#define		kBBLMSymbolTypeNamespace			CFSTR("com.barebones.bblm.namespace")
#define		kBBLMSymbolTypePredefinedSymbol		CFSTR("com.barebones.bblm.predefined")
#define		kBBLMSymbolTypeSGMLAttributeName	CFSTR("com.barebones.bblm.attributeName")
#define		kBBLMSymbolTypeSGMLAttributeValue	CFSTR("com.barebones.bblm.attributeValue")
#define		kBBLMSymbolTypeSGMLElement			CFSTR("com.barebones.bblm.element")
#define		kBBLMSymbolTypeStaticType			CFSTR("com.barebones.bblm.typedef")
#define		kBBLMSymbolTypeStruct				CFSTR("com.barebones.bblm.struct")
#define		kBBLMSymbolTypeUnion				CFSTR("com.barebones.bblm.union")
#define		kBBLMSymbolTypeTextTemplate			CFSTR("com.barebones.bblm.text-template")

#define	kBBLMSymbolCompletionDisplayString		CFSTR("DisplayString")	//	CFStringRef; used in the presentation UI

#define	kBBLMSymbolCompletionText				CFSTR("CompletionText")	//	CFStringRef; inserted upon acceptance
																		//	(and may contain placeholders)

#define	kBBLMSymbolCompletionSortName			CFSTR("SortName")		//	CFStringRef; Optional: if present, is used for sorting the
																		//	list in the GUI. If absent, the display string
																		//	is used for sorting.

#define	kBBLMSymbolCompletionSymbolOffset		CFSTR("SymbolOffset")	//	CFNumberRef; Optional: integer (zero-based) specifying
																		//	the character offset in the text of where this symbol
																		//	was found.

#define	kBBLMSymbolCompletionAutoIndent			CFSTR("AutoIndentCompletionText")
																		//	CFBooleanRef; Optional: if present and YES, indicates
																		//	that the completion text is multi-line and should be
																		//	auto-indented to match the surrounding document content.
																		
//	Flag values for bblmCreateSymbolArrayParams.fOutAdditionalLookupFlags
enum
{
	kBBLMSymbolLookupNoFlags			=	0x00000000,
	
	kBBLMSymbolLookupPredefinedNames	=	0x00000001,
	kBBLMSymbolLookupCurrentFileCtags	=	0x00000002,
	kBBLMSymbolLookupNearbyCtags		=	0x00000004,
	kBBLMSymbolLookupClippings			=	0x00000008,
	kBBLMSymbolLookupWordsInFrontWindow	=	0x00000010,
	kBBLMSymbolLookupWordsInSystemDict	=	0x00000020,
	kBBLMSymbolLookupTagMaker			=	0x00000040,
	kBBLMSymbolLookupTextReplacements	=	0x00000080,
	
	kBBLMSymbolLookupEverywherePossible	=	0xFFFFFFFF
};

//
//	Union members for the BBLMParamBlock structure
//

typedef	struct
{
	void	*fTokenBuffer;					//	token buffer for callbacks
	void	*fFcnList;						//	function list for callbacks
	
	UInt32	fOptionFlags;					//	option flags (see BBLMFcnOptionFlags)
} bblmFcnParams;

typedef	struct
{
	UInt32	fScanStart;						//	where to start scanning (relative to fText)
	UInt32	fScanEnd;						//	where to stop scanning (relative to fText)
	
	void	*fTokenBuffer;					//	token buffer for callbacks
	void	*fFcnList;						//	function list for callbacks
	
	UInt32	fOptionFlags;					//	option flags (see BBLMFcnOptionFlags)
} bblmScanSubrangeForFcnParams;

typedef struct
{
	CFDictionaryRef	fDictionary;			//	fully qualified "com.barebones.bblminfo" dictionary
											//	instance to be returned to the application.
											//	Your module should either return a copy or retain
											//	the value that it's about to return, because the
											//	application will release it when it's done.
} bblmCreateLanguageDictParams;

typedef struct
{
	SInt32		fStartIndex;
	SInt32		fEndIndex;
	SInt32		fOrigStartIndex;
	BBLMRunRec	fOrigStartRun;
}
bblmAdjustRangeParams;

typedef	struct
{
	SInt32		fStartOffset;
	DescType	fLanguage;
} bblmCalcRunParams;

typedef struct
{
	SInt32		fStartOffset;				//	where it should start looking
	SInt32		fLanguageStartOffset;		//	where the embedded language starts
	SInt32		fLanguageEndOffset;			//	where the language ends
	DescType	fLanguage;					//	what language we're checking
	DescType	fParentLanguage;			//	the parent language whose module we're talking to
} bblmFindLanguageEndParams;

typedef struct
{
	SInt32		fEndOffset;
}
bblmAdjustEndParams;

typedef	struct
{
	BBLMCategoryTable	fCategoryTable;
} bblmCategoryParams;

typedef	struct
{
	SInt8		*fToken;
	SInt16		fTokenLength;
	Boolean		fKeywordMatched;
} bblmKeywordParams;

typedef	struct
{
	NSString	*fToken;		//	guaranteed to be non-NIL and non-empty
	NSString	*fRunKind;		//	return NIL if there is no match
} bblmWordLookupParams;

typedef	struct
{
	UInt8		*fOutputString;
	UInt8		fOutputStringSize;
} bblmEscCharParams;

typedef struct
{
	SInt16		fGuessResult;
} bblmGuessLanguageParams;

typedef const UInt8 *BBLMPatternPtr;

typedef	struct
{
	DescType		fLanguage;
	Boolean			fDeleting;
	BBLMPatternPtr	fPatternString;
} bblmWordLeftRightStringParams;

typedef struct
{
	UInt32			fRunLanguage;
	NSString		*fRunKind;
	UInt32			fRunStart;
	UInt32			fRunLength;
	Boolean			fRunCanBeSpellChecked;
} bblmCanSpellCheckRunParams;

typedef struct
{
	CFURLRef		fInDocumentURL;
	CFStringRef		fInPartialSymbol;
	CFRange			fInSelectionRange;
	CFRange			fInProposedCompletionRange;
	BBLMRunRec		fInCompletionRangeStartRun;
	CFRange			fOutAdjustedCompletionRange;
} bblmAdjustCompletionRangeParams;

typedef struct
{
	CFURLRef		fInDocumentURL;
	CFStringRef		fInPartialSymbol;
	CFRange			fInCompletionRange;
	BBLMRunRec		fInCompletionRangeStartRun;
	CFArrayRef		fOutSymbolCompletionArray;
	SInt32			fOutPreferredCompletionIndex;
	UInt32			fOutAdditionalLookupFlags;
} bblmCreateCompletionArrayParams;

typedef struct
{
	BBLMRunRec		fInRunInfo;
	bool			fOutCanCompleteTokensInRun;
} bblmFilterCompletionRunParams;

typedef struct
{
	CFURLRef		fInDocumentURL;				//	may be NULL
	CFStringRef		fInIncludeFileString;
	CFURLRef		fOutIncludedItemURL;
} bblmResolveIncludeParams;

typedef struct
{
	UniChar			fInTypedCharacter;			//	the character that the user typed
	CFRange			fInSelectionRange;			//	the current selection range
	BBLMRunRec		fInRunInfo;					//	if its runKind is not NIL, this is the run in which
												//	typing is occurring
												
	UniChar			fOutPairingCharacter;		//	when called, its value is the proposed pairing character;
												//	change it to zero to suppress auto-pairing, or change its
												//	value to something else to pair with an alternative character
} bblmAutoPairParams;

#define	kBBLMParamBlockSignature	'R*ch'		//	parameter block signature
#define	kBBLMParamBlockVersion		9			//	current parameter block version (BBEdit 12.x)
#define	kBBLMMinimumCompatibleParamBlockVersion \
									8			//	minimum parameter block version
												//	that is compatible with these APIs.
												//	Version 8 corresponds to BBEdit 11.0.
class	CTextStorage;

typedef	struct
{
	OSType					fSignature;			//	must always be kBBLMParamBlockSignature
	UInt32					fVersion;			//	parameter block version
	UInt32					fLength;			//	must always be >= sizeof(BBLMParamBlock)
	
	UInt8					fMessage;			//	input message (see BBLMMessage)
	UInt32					fLanguage;			//	language code
	
	UniChar					*fText;				//	pointer to text to be scanned
	UInt32					fTextLength;		//	length of text to be scanned
	UInt32					fTextGapLocation;	//	location of "gap" in text (zero if text is contiguous)
	UInt32					fTextGapLength;		//	length of text gap (zero if text is contiguous)
	
	union
	{
		bblmFcnParams					fFcnParams;
		bblmAdjustRangeParams			fAdjustRangeParams;
		bblmCalcRunParams				fCalcRunParams;
		bblmAdjustEndParams				fAdjustEndParams;
		bblmCategoryParams				fCategoryParams;
		bblmKeywordParams				fMatchKeywordParams;
		bblmEscCharParams				fEscapeCharParams;
		bblmGuessLanguageParams			fGuessLanguageParams;
		bblmWordLeftRightStringParams	fWordLeftRightStringParams;
		bblmCanSpellCheckRunParams		fCanSpellCheckRunParams;
		bblmWordLookupParams			fWordLookupParams;
		bblmScanSubrangeForFcnParams	fScanSubrangeForFcnParams;
		bblmCreateLanguageDictParams	fCreateLanguageDictParams;
		bblmFindLanguageEndParams		fFindLanguageEndParams;
		bblmAdjustCompletionRangeParams	fAdjustCompletionRangeParams;
		bblmFilterCompletionRunParams	fFilterCompletionRunParams;
		bblmCreateCompletionArrayParams	fCreateCompletionArrayParams;
		bblmResolveIncludeParams		fResolveIncludeParams;
		bblmAutoPairParams				fAutoPairParams;
	};
	
	UInt32					reserved[63];			//	reserved for future expansion
	CTextStorage			*fPrivateTextStorage;	//	used internally
} BBLMParamBlock;

typedef	struct
{
	OSType		fSignature;			//	must always be BBEdit's application signature ("R*ch")
	UInt32		fVersion;			//	reflects current callback version (see kBBLMCurrentCallbackVersion)
	
//	version 1 callbacks

		//
		//	these callbacks are used when messages == kBBLMScanForFunctionsMessage,
		//	and are NIL at all other times.
		//
		
		//
		//	use these callbacks to make the token buffer and proc list empty.
		//	BBEdit will do this for you when your plug-in is called; these
		//	are just for convenience.
		//
		
		OSErr		(*fResetTokenBuffer)(void *tokenBuffer);			// Available in callback version 1 and later
		OSErr		(*fResetProcList)(void *procList);					// Available in callback version 1 and later
		
		//
		//	these callbacks are used in tandem to add a function to the list. When
		//	you've found a function or other item to be added to the function popup,
		//	call fAddTokenToBuffer() to add its name to the token buffer. If successful, the
		//	"offset" parameter will contain a value which should then be passed
		//	as the second argument to fAddFunctionToList(). If you need to change a
		//	entry after adding it to the list, call fUpdateFunctionEntry(), using the
		//	index obtained from a previous fAddFunctionToList() call.
		//
		
		OSErr		(*fAddTokenToBuffer)(void *tokenBuffer,				//	-> token buffer instance passed in fFcnParams
											const UniChar *token,		//	-> points to identifier text (Unicode characters)
											const UInt32 length,		//	-> length of identifier text (in characters)
											UInt32 *offset);			//	<- offset at which token was inserted
																		//
																		// Available in callback version 1 and later
											
		OSErr		(*fAddFunctionToList)(void *procList,				//	-> function list instance passed in fFcnParams
											BBLMProcInfo &info,			//	-> function info record
											UInt32 *index);				//	<- zero-based index of this function's entry
																		//
																		// Available in callback version 1 and later
		
		OSErr		(*fGetFunctionEntry)(void *procList,				//	-> function list instance passed in fFcnParams
											UInt32 index,				//	-> zero-based index of function entry to fetch
											BBLMProcInfo &new_info);	//	<- function info record from list
																		//
																		// Available in callback version 1 and later
											
		OSErr		(*fUpdateFunctionEntry)(void *procList,				//	-> function list instance passed in fFcnParams
											UInt32 index,				//	-> zero-based index of function entry to change
											BBLMProcInfo &new_info);	//	-> function info record containing new information
																		//
																		// Available in callback version 1 and later
																		
	//
	//	these callbacks are used when fMessage is kBBLMAdjustRangeMessage,
	//	kBBLMCalculateRunsMessage, or kBBLMAdjustEndMessage and are NIL at
	//	all other times.
	//
	
	SInt32		(*fRunCount)(void);							//	current number of runs. zero if no runs yet
															//	defined. negative if run list is undefined
															//	(usually a result of an allocation failure).
	
	Boolean		(*fGetRun)(	SInt32 index,					//	get a run
							DescType& language,				//	language code
							NSString* &kind,				//	run kind
							SInt32& charPos,				//	character position of run start
							SInt32& length);				//	number of characters in run
	
	SInt32		(*fFindRun)( SInt32 offset );				//	find run containing char offset
															//	returns -1 if not found
				
	Boolean		(*fAddRun)(									//	add a new run. returns false if no more runs needed
							DescType language,				//	language code
							NSString* kind,					//	run kind
							SInt32 startPos,				//	character position of run start
							SInt32 length,					//	number of characters in run
							bool dontMerge);				//	when updating a run list, don't return false
															//	to stop scanning even if this new run
															//	matches an old one
	
	void		(*fFlushRuns)(void);						//	flush any runs added with fAddRun that may
															//	currently be buffered.

//	version 3 callbacks

	//	this callback is used when messages == kBBLMScanForFunctionsMessage
	
	OSErr		(*fAddCFStringTokenToBuffer)(void *tokenBuffer,	//	-> token buffer instance passed in fFcnParams
											 CFStringRef string,	//	-> string used for identifier text
											 UInt32 *offset);		//	<- offset at which token was inserted
																	//
																	// Available in callback version 3 and later

//	version 4 callbacks

	//	this callback may be used when messages == kBBLMSetCategoriesMessage
	
	void		(*fSetUnicodeCategoryTable)
						(BBLMUnicodeCategoryTable &categoryTable);	//	-> if called, callee makes internal copy of this
																	//		table and ignores table in fCategoryParams
																	//
																	// Available in callback version 4 and later


//	version 5 callbacks

	//	this callback may be used when messages == kBBLMScanForFoldRanges
	//								or messages == kBBLMScanForFunctionsMessage
	
	OSErr		(*fAddFoldRange)(SInt32 startPos,					//	character position of first char to be folded
								 SInt32 length,						//	number of characters to be folded
								 BBLMFoldKind foldKind);			//	type of fold (defaults to kBBLMGenericAutoFold)

//	version 6 callbacks

	//	this callback may be used when messages == kBBLMCalculateRunsMessage
	OSErr		(*fFindEmbeddedLanguageRunsInRange)(const DescType language,
													BBLMParamBlock &myParams,
													const SInt32 startOffset,
													const SInt32 rangeLength,
													bool &continueScanning);
	
	OSErr		(*fFindEmbeddedLanguageFunctionsInRange)(const DescType language,
															BBLMParamBlock &myParams,
															const SInt32 startOffset,
															const SInt32 rangeLength);

} BBLMCallbackBlock;

#if (! __LP64__)
#pragma pack(pop)
#endif

#pragma mark -

#ifdef	__cplusplus

//	these inlines should be used in preference to directly accessing the members of the BBLMCallbackBlock

#pragma mark Function Scanner Callbacks

inline	OSErr	bblmResetTokenBuffer(const BBLMCallbackBlock *callbacks, void *tokenBuffer)
					{ return callbacks->fResetTokenBuffer(tokenBuffer); }

inline	OSErr	bblmResetProcList(const BBLMCallbackBlock *callbacks, void *procList)
					{ return callbacks->fResetProcList(procList); }

inline	OSErr	bblmAddTokenToBuffer(const BBLMCallbackBlock *callbacks,
										void *tokenBuffer,
										const UniChar *token,
										const UInt32 length,
										UInt32 *offset)
{
	return callbacks->fAddTokenToBuffer(tokenBuffer, token, length, offset);
}

inline	OSErr	bblmAddCFStringTokenToBuffer(const BBLMCallbackBlock *callbacks,
											 void *tokenBuffer,
											 CFStringRef string,
											 UInt32 *offset)
{
	if (kBBLMCurrentCallbackVersion >= 3)
		return callbacks->fAddCFStringTokenToBuffer(tokenBuffer, string, offset);
	
	return paramErr;
}

inline	OSErr	bblmAddFunctionToList(const BBLMCallbackBlock *callbacks,
										void *procList,
										BBLMProcInfo &info,
										UInt32 *index)
{
	return callbacks->fAddFunctionToList(procList, info, index);
}

inline	OSErr	bblmGetFunctionEntry(const BBLMCallbackBlock *callbacks,
										void *procList,
										UInt32 index,
										BBLMProcInfo &info)
{
	return callbacks->fGetFunctionEntry(procList, index, info);
}

inline	OSErr	bblmUpdateFunctionEntry(const BBLMCallbackBlock *callbacks,
										void *procList,
										UInt32 index,
										BBLMProcInfo &new_info)
{
	return callbacks->fUpdateFunctionEntry(procList, index, new_info);
}

inline	//	this is one-call alternative to using bblmAddCFStringTokenToBuffer() followed by bblmAddFunctionToList().
OSStatus	bblmAddFunctionToList(const BBLMCallbackBlock *callbacks,
									void *tokenBuffer,
									void *procList,
									CFStringRef name,
									BBLMProcInfo &info,
									UInt32 *index)
{
	OSStatus	err = noErr;
	
	//	basic parameter validation
	require_action(nil != callbacks, EXIT, err = paramErr);
	require_action(nil != tokenBuffer, EXIT, err = paramErr);
	require_action(nil != procList, EXIT, err = paramErr);
	require_action(nil != name, EXIT, err = paramErr);
	
	require_noerr(err = bblmAddCFStringTokenToBuffer(callbacks,
														tokenBuffer,
														name,
														&info.fNameStart),
					EXIT);
	
	require_noerr(err = bblmAddFunctionToList(callbacks,
												procList,
												info,
												index),
					EXIT);
	
EXIT:
	return err;
}

inline	//	this is just the above, with an NSString parameter so that there's no need for a cast.
OSStatus	bblmAddFunctionToList(const BBLMCallbackBlock *callbacks,
									void *tokenBuffer,
									void *procList,
									NSString *name,
									BBLMProcInfo &info,
									UInt32 *index)
{
	return bblmAddFunctionToList(callbacks,
									tokenBuffer,
									procList,
									reinterpret_cast<CFStringRef>(name),
									info,
									index);
}

#pragma mark -
#pragma mark Syntax Coloring Callbacks

inline	SInt32		bblmRunCount(const BBLMCallbackBlock *callbacks)
{
	return callbacks->fRunCount();
}										

inline	bool		bblmGetRun(const BBLMCallbackBlock *callbacks,
								SInt32 index,
								DescType& language,
								NSString* &kind,
								SInt32& charPos,
								SInt32& length)
{
	return callbacks->fGetRun(index, language, kind, charPos, length);
}										

inline	bool		bblmGetRun(const BBLMCallbackBlock *callbacks,
								SInt32 index,
								BBLMRunRec &runInfo)
{
	SInt32	runLength = 0;

	if (bblmGetRun(callbacks, index, runInfo.language, runInfo.runKind, runInfo.startPos, runLength))
	{
		runInfo.depth = 0;
		runInfo.length = runLength;
		
		return true;
	}
	
	return false;
}

inline	SInt32		bblmFindRun(const BBLMCallbackBlock *callbacks,
								SInt32 offset)
{
	return callbacks->fFindRun(offset);
}										

inline	bool		bblmAddRun(const BBLMCallbackBlock *callbacks,
								DescType language,
								NSString *kind,
								SInt32 charPos,
								SInt32 length,
								bool dontMerge = false)
{
	return callbacks->fAddRun(language, kind, charPos, length, dontMerge);
}										

inline	void		bblmFlushRuns(const BBLMCallbackBlock *callbacks)
{
	callbacks->fFlushRuns();
}										

inline	OSErr		bblmSetUnicodeCategoryTable(const BBLMCallbackBlock *callbacks,
													BBLMUnicodeCategoryTable &categoryTable)
{
	OSErr result = noErr;
	
	if (kBBLMCurrentCallbackVersion >= 4)
		callbacks->fSetUnicodeCategoryTable(categoryTable);
	else
		result = paramErr;
	
	return result;
}										

inline	OSErr		bblmAddFoldRange(const BBLMCallbackBlock *callbacks,
										SInt32 startPos,
										SInt32 length,
										BBLMFoldKind foldKind = kBBLMGenericAutoFold)
{
	return callbacks->fAddFoldRange(startPos, length, foldKind);
}										

inline	OSErr		bblmFindEmbeddedLanguageRunsInRange(const BBLMCallbackBlock *callbacks,
														const DescType language,
														BBLMParamBlock &myParams,
														const SInt32 startOffset,
														const SInt32 rangeLength,
														bool &continueScanning)
{
	return callbacks->fFindEmbeddedLanguageRunsInRange(language,
															myParams,
															startOffset,
															rangeLength,
															continueScanning);
}
	
inline	OSErr		bblmFindEmbeddedLanguageFunctionsInRange(const BBLMCallbackBlock *callbacks,
																const DescType language,
																BBLMParamBlock &myParams,
																const SInt32 startOffset,
																const SInt32 rangeLength)
{
	return callbacks->fFindEmbeddedLanguageFunctionsInRange(language,
															myParams,
															startOffset,
															rangeLength);
}

//
//	Use BBLMCharacterIsLineBreak() instead of explicitly testing against \r or \n.
//	This will ensure compatibility with past and future versions of BBEdit and
//	TextWrangler.
//

inline
bool	BBLMCharacterIsLineBreak(const UniChar ch) __attribute__((const, always_inline));

inline
bool	BBLMCharacterIsLineBreak(const UniChar ch)
{
	return ('\r' == ch) || ('\n' == ch);
}

//
//	Use BBLMCharacterIsBlankOrTab() instead of explicitly testing character values.
//	This will ensure compatibility with past and future versions of BBEdit and
//	TextWrangler.
//

inline
bool	BBLMCharacterIsBlankOrTab(const UniChar ch) __attribute__((const, always_inline));

inline
bool	BBLMCharacterIsBlankOrTab(const UniChar ch)
{
	return (' ' == ch) || ('\t' == ch);
}

#else

#error	"Sorry, there is no callback macro support for C."

#endif

#endif // BBLMINTERFACE_h
