#ifndef CVT_SLIDER_H
#define CVT_SLIDER_H

#include <cvt/gui/Widget.h>
#include <cvt/util/Signal.h>

namespace cvt {
	template<typename T>
	class Slider : public Widget {
		public:
			Slider( T min, T max, T value );
			void setMinimum( T min );
			T	 minimum() const;
			void setMaximum( T max );
			T	 maximum() const;
			void setValue( T value );
			T	 value() const;

			Signal<T> valueChanged;
		protected:
			void paintEvent( PaintEvent* e, GFX* g );
			void mousePressEvent( MousePressEvent* event );
			void mouseMoveEvent( MouseMoveEvent* event );
//			void mouseReleaseEvent( MouseReleaseEvent* event );

		private:
			void xToValue( int x );

			T _min, _max, _value;
	};

	template<typename T>
	inline Slider<T>::Slider( T min = 0, T max = 1, T value = 0 ) : _min( min ), _max( max ), _value( value )
	{
	}

	template<typename T>
	inline void Slider<T>::setMinimum( T min )
	{
		_min = min;
	}

	template<typename T>
	inline void Slider<T>::setMaximum( T max )
	{
		_max = max;
	}

	template<typename T>
	inline void Slider<T>::setValue( T val )
	{
		if( _value == val )
			return;
		_value = val;
		valueChanged.notify( _value );
		update();
	}

	template<typename T>
	inline T Slider<T>::minimum() const
	{
		return _min;
	}

	template<typename T>
	inline T Slider<T>::maximum() const
	{
		return _max;
	}

	template<typename T>
	inline T Slider<T>::value() const
	{
		return _value;
	}

	template<typename T>
	inline void Slider<T>::paintEvent( PaintEvent*, GFX* gfx )
	{
		int w, h;
		size( w, h );
		gfx->color().set( 0.5f, 0.5f, 0.5f, 1.0f );
		gfx->fillRoundRect( 0, 0, w, h, 0.5f * ( float ) h );
		float pos = ( float ) ( w - h ) * ( float  ) ( _value - _min ) / ( float ) ( _max - _min );
		gfx->color().set( 0.2f, 0.2f, 0.2f, 1.0f );
		gfx->fillRoundRect( ( int ) pos, 0, h, h, 0.5f * ( float ) h );

/*		char buf[ 200 ];
		sprintf( buf, "%f", ( float ) _value );
		gfx->color().set( 1.0f, 1.0f, 1.0f, 1.0f );
		gfx->drawText( 0, 10, buf );*/
	}

	template<typename T>
	void Slider<T>::mousePressEvent( MousePressEvent* event )
	{
		if( event->button() == 1 ) {
			xToValue( event->x );
		}
	}

	template<typename T>
	void Slider<T>::mouseMoveEvent( MouseMoveEvent* event )
	{
		if( event->buttonMask() & 1 ) {
			xToValue( event->x );
		}
	}

	template<typename T>
	inline void Slider<T>::xToValue( int x )
	{
		int w, h;
		size( w, h );
		float pos = ( float ) ( x - h / 2 ) / ( float ) ( w - h );
		T value =  Math::clamp<T>( ( T ) ( pos * ( float )( _max - _min ) ) + _min, _min, _max );
		setValue( value );
	}


}


#endif