#ifndef __ANSIGL_TEXT_H__
#define __ANSIGL_TEXT_H__

/*
 * text.h
 *
 * A content object that represents a text field.
 */


#include "content.h"


namespace AnsiGL
{
	class Text : public Content
	{
	public:
		ANSIGL_POINTERS( Text )

		typedef astring::iterator				iterator;
		typedef astring::const_iterator			const_iterator;
		typedef astring::reverse_iterator		reverse_iterator;
		typedef astring::const_reverse_iterator	const_reverse_iterator;

	public:
		bool			AutoHeight;					// Automatically adjusts the height based on the formatted text
		bool			TransparentSpaces;

	public:
		Text():
			AutoHeight( true ),
			TransparentSpaces( false ),
			_Text( "" ),
			_Alignment( TxtAlign_Default ),
			_ColorDepth( ColorDepth_Default ),
			_LastLineLength( 0 )
		{
			this->Resize( Area2D(1, 1) );
			this->Format();
		}

		Text( tSizeType width,						// A width of 0 is unlimited
			  ENUM_TxtAlign alignment		= TxtAlign_Default,
			  ENUM_ColorDepth colorDepth	= ColorDepth_Default,
			  bool transparentSpaces		= false,
			  bool autoHeight				= true ):
			AutoHeight( autoHeight ),
			TransparentSpaces( transparentSpaces ),
			_Text( "" ),
			_Alignment( alignment ),
			_ColorDepth( colorDepth ),
			_LastLineLength( 0 )
		{
			this->Width( width );
			this->Format();
		}

		Text( const astring &text,
			  tSizeType width				= 0,	// A width of 0 is unlimited
			  ENUM_TxtAlign alignment		= TxtAlign_Default,
			  ENUM_ColorDepth colorDepth	= ColorDepth_Default,
			  bool transparentSpaces		= false,
			  bool autoHeight				= true ):
			AutoHeight( autoHeight ),
			TransparentSpaces( transparentSpaces ),
			_Text( text ),
			_Alignment( alignment ),
			_ColorDepth( colorDepth ),
			_LastLineLength( 0 )
		{
			if ( width == 0 )
				this->Width( text.length() );
			else
				this->Width( width );

			this->Format();
		}

		Text( const ustring &text,
			  tSizeType width				= 0,		// A width of 0 is unlimited
			  ENUM_TxtAlign alignment		= TxtAlign_Default,
			  ENUM_ColorDepth colorDepth	= ColorDepth_Default,
			  bool transparentSpaces		= false,
			  bool autoHeight				= true ):
			AutoHeight( autoHeight ),
			TransparentSpaces( transparentSpaces ),
			_Text( astring(text) ),
			_Alignment( alignment ),
			_ColorDepth( colorDepth ),
			_LastLineLength( 0 )
		{
			if ( width == 0 )
				this->Width( text.length() );
			else
				this->Width( width );

			this->Format();
		}

		Text( const std::string &text,
			  tSizeType width				= 0,	// A width of 0 is unlimited
			  ENUM_TxtAlign alignment		= TxtAlign_Default,
			  ENUM_ColorDepth colorDepth	= ColorDepth_Default,
			  bool transparentSpaces		= false,
			  bool autoHeight				= true ):
			AutoHeight( autoHeight ),
			TransparentSpaces( transparentSpaces ),
			_Text( astring(text) ),
			_Alignment( alignment ),
			_ColorDepth( colorDepth ),
			_LastLineLength( 0 )
		{
			if ( width == 0 )
				this->Width( text.length() );
			else
				this->Width( width );

			this->Format();
		}

		virtual ~Text()
		{
		}

		iterator begin()
		{
			return _Text.begin();
		}

		const_iterator begin() const
		{
			return _Text.begin();
		}

		reverse_iterator rbegin()
		{
			return _Text.rbegin();
		}

		const_reverse_iterator rbegin() const
		{
			return _Text.rbegin();
		}

		iterator end()
		{
			return _Text.end();
		}

		const_iterator end() const
		{
			return _Text.end();
		}

		reverse_iterator rend()
		{
			return _Text.rend();
		}

		const_reverse_iterator rend() const
		{
			return _Text.rend();
		}

		virtual void Format();
		tSizeType LastLineLength() const;			// Returns the length of the last line in the formatted text

		const astring &Value() const;
		const astring &FormattedValue() const;
		void Value( const astring &text );
		void Value( const ustring &text );
		void Value( const std::string &text );

		void Append( const astring &text );
		void Append( const ustring &text );
		void Append( const std::string &text );
		void Append( const achar &ch );

		bool empty() const;
		void push_back( const achar &ch );
		void pop_back();

		void Clear();

		ENUM_TxtAlign Align() const;
		void Align( ENUM_TxtAlign align );

		virtual tSizeType Length() const;			// Length of the string, rather than the width of the window

		virtual const tSizeType Width() const;
		virtual void Width( tSizeType width );
		virtual const tSizeType Height() const;
		virtual void Height( tSizeType height );
		virtual void Resize( const Area2D &size );

		virtual std::string str();
		virtual std::string Render() const;
		virtual void RenderToSurface( Surface::Ptr dest, const Point2D &pos = Point2D() ) const;

		Text &operator<<( void *val );
		Text &operator<<( bool val );
		Text &operator<<( char val );
		Text &operator<<( unsigned char val );
		Text &operator<<( short val );
		Text &operator<<( unsigned short val );
		Text &operator<<( int val );
		Text &operator<<( unsigned int val );
		Text &operator<<( long val );
		Text &operator<<( unsigned long val );
		Text &operator<<( float val );
		Text &operator<<( double val );
		Text &operator<<( const char *right );
		Text &operator<<( const std::string &right );
		Text &operator<<( const ustring &right );
		Text &operator<<( const achar &right );
		Text &operator<<( const astring &right );

	protected:
		astring			_Text;
		astring			_FormattedText;

		ENUM_TxtAlign	_Alignment;
		ENUM_ColorDepth	_ColorDepth;

		tSizeType		_LastLineLength;

	protected:
		template <typename tDataType>
		Text &addToStream( tDataType val )
		{
			std::stringstream Buffer("");
			Buffer << val;
			this->Append( Buffer.str() );
			return (*this);
		}
	};
}


#endif // __ANSIGL_TEXT_H__


// vim: tabstop=4 shiftwidth=4
// astyle: --indent=tab=4 --style=ansi --indent-namespaces --indent-cases --indent-switches --pad-oper


