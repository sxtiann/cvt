#ifndef CVTPAINTEVENT_H
#define CVTPAINTEVENT_H

#include <cvt/gui/event/Event.h>
#include <cvt/util/Rect.h>

namespace cvt {
	class PaintEvent : Event
	{
		public:
			PaintEvent( int x, int y, int width, int height ) : Event( EVENT_PAINT ), rect( x, y, width, height ) {};
			void getSize( int& width, int& height ) const { width = rect.width; height = rect.height;  };
			void getPosition( int& x, int& y ) const { x = rect.x; y = rect.y; };
			void getRect( Recti& r ) const { r = rect; };

		private:
			Recti rect;
	};
};

#endif