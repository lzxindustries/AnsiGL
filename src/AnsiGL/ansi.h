#ifndef __ANSIGL_ANSI_H__
#define __ANSIGL_ANSI_H__

/*
 * ansi.h
 *
 * ANSI definitions.
 */


#include <list>
#include <memory>
#include <string>
#include <vector>

#include "defines.h"


namespace AnsiGL
{
	//
	// ANSI constants
	//
	extern const char *ANSI_CODE_START;		// The escape sequence to start ANSI codes
	extern const char ANSI_CODE_END;		// THe ANSI code sequence terminator
	extern const char ANSI_CODE_SEPARATOR;	// THe ANSI code sequence separator character
	extern const int ANSI_BG_OFFSET;		// The offset between foreground and background colors


	//
	// ANSI codes of interest, enumerated
	//
	enum ENUM_ANSICodes
	{
		ANSI_First = 0,

		ANSI_Default = ANSI_First,		// 0
		ANSI_BoldOn,
		ANSI_FaintOn,
		ANSI_ItalicsOn,
		ANSI_UnderlineOn,
		ANSI_BlinkSlow,				// 5
		ANSI_BlinkFast,
		ANSI_InverseOn,
		ANSI_ConcealOn,
		ANSI_CrossedOut,
		ANSI_PrimaryFont,			// 10
		ANSI_AlternateFont1,
		ANSI_AlternateFont2,
		ANSI_AlternateFont3,
		ANSI_AlternateFont4,
		ANSI_AlternateFont5,			// 15
		ANSI_AlternateFont6,
		ANSI_AlternateFont7,
		ANSI_AlternateFont8,
		ANSI_AlternateFont9,
		ANSI_Fraktur,				// 20
		ANSI_BoldOff,
		ANSI_NormalIntensity,
		ANSI_ItalicsOff,
		ANSI_UnderlineOff,
		ANSI_BlinkOff,				// 25
		ANSI_Reserved1,
		ANSI_InverseOff,
		ANSI_ConcealOff,
		ANSI_CrossedOutOff,
		ANSI_FG_Black,				// 30
		ANSI_FG_Red,
		ANSI_FG_Green,
		ANSI_FG_Yellow,
		ANSI_FG_Blue,
		ANSI_FG_Magenta,			// 35
		ANSI_FG_Cyan,
		ANSI_FG_White,
		ANSI_FG_256Color,
		ANSI_FG_Default,
		ANSI_BG_Black,				// 40
		ANSI_BG_Red,
		ANSI_BG_Green,
		ANSI_BG_Yellow,
		ANSI_BG_Blue,
		ANSI_BG_Magenta,			// 45
		ANSI_BG_Cyan,
		ANSI_BG_White,
		ANSI_BG_256Color,
		ANSI_BG_Default,
		ANSI_Reserved2,				// 50
		ANSI_Framed,
		ANSI_Encircled,
		ANSI_Overlined,
		ANSI_FrameAndCircleOff,
		ANSI_OverlineOff,			// 55

		ANSI_Max,

		ANSI_FG_Start = 30,
		ANSI_FG_End = 39,
		ANSI_BG_Start = 40,
		ANSI_BG_End = 49
	};


	enum ENUM_ANSISystemColors
	{
		ANSISysColor_First,

		ANSISysColor_Black = ANSISysColor_First,
		ANSISysColor_Red,
		ANSISysColor_Green,
		ANSISysColor_Yellow,
		ANSISysColor_Blue,
		ANSISysColor_Magenta,
		ANSISysColor_Cyan,
		ANSISysColor_White,
		ANSISysColor_BoldBlack,
		ANSISysColor_BoldRed,
		ANSISysColor_BoldGreen,
		ANSISysColor_BoldYellow,
		ANSISysColor_BoldBlue,
		ANSISysColor_BoldMagenta,
		ANSISysColor_BoldCyan,
		ANSISysColor_BoldWhite,

		ANSISysColor_Max,

		// Default is white text on a black background
		ANSISysColor_Default = ANSISysColor_White,
		ANSISysColor_BGDefault = ANSISysColor_First,
	};


	//
	// Though not technically an ANSI specification, this is the most logical place to put this...especially since we need it as a function parameter at times
	//
	enum ENUM_ColorDepth
	{
		ColorDepth_First = 0,

		ColorDepth_6Bit = ColorDepth_First,	// 64 total color combinations, 8 foreground and 8 background
		ColorDepth_7Bit,					// 128 total color combinations, 16 foreground and 8 background
		ColorDepth_8Bit,					// 256 color combinations for each the foreground and background

		ColorDepth_Max,

		ColorDepth_Default = ColorDepth_7Bit
	};


	//
	// Forward declaration of ANSIColorDef so ANSICodeList can accept ANSIColorDef's as member function parameters
	//
	class ANSIColorDef;


	//
	// ANSICodeList is simply a managed std::list of ANSI codes.
	//
	class ANSICodeList
	{
	public:
		ANSIGL_POINTERS( ANSICodeList )

	protected:
		int	_CodesL;			// I'm sure there's a more portable way to do this...but babysteps for now
		int	_CodesH;

	public:
		ANSICodeList():
			_CodesL(0),
			_CodesH(0)
		{
		}

		bool operator==( const ANSICodeList &right ) const
		{
			return (_CodesL == right._CodesL && _CodesH == right._CodesH);
		}
		bool operator!=( const ANSICodeList &right ) const
		{
			return !(*this == right);
		}

		bool empty() const
		{
			return (!_CodesL && !_CodesH);
		}
		void clear()
		{
			_CodesL = _CodesH = 0;
		}

		void Add( ENUM_ANSICodes code )
		{
			if ( code < 32 )
				_CodesL |= (1 << code);
			else
				_CodesH |= (1 << (code - 32));
		}
		void Add( const ANSICodeList &codes )
		{
			_CodesL |= codes._CodesL;
			_CodesH |= codes._CodesH;
		}

		bool Has( ENUM_ANSICodes code ) const
		{
			if ( code < 32 )
				return (_CodesL & (1 << code));
			else
				return (_CodesH & (1 << (code - 32)));
		}
		bool HasAll( const ANSICodeList &codes ) const
		{
			for ( int i = ANSI_First; i < ANSI_Max; ++i )
			{
				if ( codes.Has((ENUM_ANSICodes)i) && !Has((ENUM_ANSICodes)i) )
					return false;
			}

			return true;
		}

		void Remove( ENUM_ANSICodes code )
		{
			if ( code < 32 )
				_CodesL &= ~(1 << code);
			else
				_CodesH &= ~(1 << (code - 32));
		}
		void Remove( const ANSICodeList &codes )
		{
			_CodesL &= ~(codes._CodesL);
			_CodesH &= ~(codes._CodesH);
		}

		std::string Render( ENUM_ColorDepth desiredDepth = ColorDepth_Default, bool background = false ) const;	// Renders the ANSI codes with separaters between them if needed, but nothing else
	};


	//
	// The default name for a new ANSIColorDef
	//
	const std::string DEFAULT_ANSICOLOR_NAME( "NewColor" );


	//
	// ANSIColorDef is a definition of ANSI color codes specifically
	//
	class ANSIColorDef
	{
	public:
		ANSIGL_POINTERS( ANSIColorDef )

	protected:
		ANSICodeList			_ANSI;					// The actual ANSI codes associated with our color
		unsigned char			_Index;					// The computed 0-255 index for 8Bit colors

		ENUM_ANSISystemColors	_SystemColor;			// The first 16 ANSI colors (well, the first 8, and then again bold)

		unsigned char			_R;						// Range 0-5	RxGxB 6x6x6
		unsigned char			_G;						// Range 0-5    215 colors
		unsigned char			_B;						// Range 0-5

		unsigned char			_Grayscale;				// Range 0-23	24 colors

	public:
		std::string				Name;					// A human-readable "common name" for this color

	public:
		ANSIColorDef():
			_Index(-1),
			_SystemColor(ANSISysColor_Default),
			_R(0),
			_G(0),
			_B(0),
			_Grayscale(0),
			Name(DEFAULT_ANSICOLOR_NAME)
		{
		}

		ANSIColorDef( const ANSIColorDef &color ):
			_Index(-1),
			_SystemColor(ANSISysColor_Default),
			_R(0),
			_G(0),
			_B(0),
			_Grayscale(0),
			Name(DEFAULT_ANSICOLOR_NAME)
		{
			_Index = color._Index;
			_SystemColor = color._SystemColor;
			_R = color._R;
			_G = color._G;
			_B = color._B;
			_Grayscale = color._Grayscale;
			Name = color.Name;

			_ANSI.Add( color._ANSI );
		}

		ANSIColorDef( const std::string &name, ENUM_ANSISystemColors color ):
			_Index(-1),
			_SystemColor(ANSISysColor_Default),
			_R(0),
			_G(0),
			_B(0),
			_Grayscale(0),
			Name(name)
		{
			SystemColor( color );
		}

		ANSIColorDef( const std::string &name, unsigned char r, unsigned char g, unsigned char b ):
			_Index(-1),
			_SystemColor(ANSISysColor_Default),
			_R(r),
			_G(g),
			_B(b),
			_Grayscale(0),
			Name(name)
		{
			calculateIndexFromRGB();
		}

		ANSIColorDef( const std::string &name, unsigned char grayscale ):
			_Index(-1),
			_SystemColor(ANSISysColor_Default),
			_R(0),
			_G(0),
			_B(0),
			_Grayscale(grayscale),
			Name(name)
		{
			calculateIndexFromGrayscale();
		}

		ANSIColorDef( ENUM_ANSISystemColors color ):
			_Index(-1),
			_SystemColor(ANSISysColor_Default),
			_R(0),
			_G(0),
			_B(0),
			_Grayscale(0),
			Name(DEFAULT_ANSICOLOR_NAME)
		{
			SystemColor( color );
		}

		ANSIColorDef( unsigned char r, unsigned char g, unsigned char b ):
			_Index(-1),
			_SystemColor(ANSISysColor_Default),
			_R(r),
			_G(g),
			_B(b),
			_Grayscale(0),
			Name(DEFAULT_ANSICOLOR_NAME)
		{
			calculateIndexFromRGB();
		}

		ANSIColorDef( unsigned char grayscale ):
			_Index(-1),
			_SystemColor(ANSISysColor_Default),
			_R(0),
			_G(0),
			_B(0),
			_Grayscale(grayscale),
			Name(DEFAULT_ANSICOLOR_NAME)
		{
			calculateIndexFromGrayscale();
		}

		bool operator==( const ANSIColorDef &right ) const;
		bool operator!=( const ANSIColorDef &right ) const;

		const ANSICodeList &ANSI() const
		{
			return _ANSI;
		}

		unsigned char Index() const
		{
			return _Index;
		}

		ENUM_ANSISystemColors SystemColor() const;
		void SystemColor( ENUM_ANSISystemColors color );

		void GetRGB( unsigned char *r, unsigned char *g, unsigned char *b ) const
		{
			if ( r )
				*r = _R;

			if ( g )
				*g = _G;

			if ( b )
				*b = _B;
		}
		void SetRGB( unsigned char r, unsigned char g, unsigned char b );	// Each value ranges from 0-5

		unsigned char Grayscale() const										// Returns 0 (black) if the index is not in the grayscale range
		{
			return _Grayscale;
		}
		void Grayscale( unsigned char grayscaleGradient );					// Ranges from 0-23, 0 is black, 23 is white

		bool IsSysColor() const												// Returns true if we're using a standard system color
		{
			return (_Index != -1 && _Index <= 15);
		}

		bool IsRGB() const													// Returns true if we're using RGB values
		{
			return (_Index != -1 && _Index >= 16 && _Index <= 231);
		}

		bool IsGrayscale() const											// Returns true if we're using Grayscale values
		{
			return (_Index != -1 && _Index >= 232);
		}

		void Clear()
		{
			_ANSI.clear();
			_Index = -1;
			_SystemColor = ANSISysColor_Default;
			_R = 0;
			_G = 0;
			_B = 0;
			_Grayscale = 0;
		}

		std::string Render( ENUM_ColorDepth desiredDepth = ColorDepth_Default, bool background = false ) const;	// Renders the color as a background color, if set

	protected:
		void calculateIndexFromRGB();						// Calculates the index from the RGB values
		void calculateIndexFromGrayscale();					// Calculates the index from the Grayscale value
	};


	class ANSIColorPalette
	{
	public:
		ANSIGL_POINTERS( ANSIColorPalette )

		typedef std::vector< ANSIColorDef::Ptr >::iterator			iterator;
		typedef std::vector< ANSIColorDef::Ptr >::const_iterator		const_iterator;
		typedef std::vector< ANSIColorDef::Ptr >::reverse_iterator		reverse_iterator;
		typedef std::vector< ANSIColorDef::Ptr >::const_reverse_iterator	const_reverse_iterator;

		static ANSIColorPalette::Ptr						Master;				// The master reference color palette.   NOTE: This master palette is initialized upon the first creation of a custom user palette (which will happen upon the creation of any Surface!), or prior to that by the developer in order to create a customized "master" palette.  The master palette will only be constructed if one does not exist currently.

		static void InitMasterPalette();					// Initalize the master color palette

	protected:
		std::vector< ANSIColorDef::Ptr >	_Colors;

	public:
		ANSIColorPalette()
		{
		}

		ANSIColorDef::Ptr &operator[]( size_t index );
		const ANSIColorDef::Ptr &operator[]( size_t index ) const;

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;

		bool empty() const;
		size_t size() const;

		void push_back( ANSIColorDef::Ptr color );

		int FindIndex( const ANSIColorDef &color ) const;
		int FindIndex( const std::string &colorName ) const;
		int FindIndex( ENUM_ANSISystemColors systemColor ) const;
		int FindIndex( unsigned char r, unsigned char g, unsigned char b ) const;
		int FindIndex( unsigned char grayscale ) const;

		ANSIColorDef::Ptr FindColor( const std::string &colorName ) const;
		ANSIColorDef::Ptr FindColor( ENUM_ANSISystemColors systemColor ) const;
		ANSIColorDef::Ptr FindColor( unsigned char r, unsigned char g, unsigned char b ) const;
		ANSIColorDef::Ptr FindColor( unsigned char grayscale ) const;
	};


	// Sends the VT100(IIRC) CLS code
	std::string CLS();
}


#endif // __ANSIGL_ANSI_H__


// vim: tabstop=4 shiftwidth=4
// astyle: --indent=tab=4 --style=ansi --indent-namespaces --indent-cases --indent-switches --pad-oper


