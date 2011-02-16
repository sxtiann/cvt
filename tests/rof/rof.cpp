#include <iostream>

#include <cvt/gfx/Image.h>
#include <cvt/gfx/IKernel.h>
#include <cvt/gfx/ifilter/ROFDenoise.h>
#include <cvt/io/ImageIO.h>
#include <cvt/gfx/Color.h>
#include <cvt/util/Exception.h>

#include <string>

int main()
{
	std::string dataFolder(DATA_FOLDER);
	std::string inputFile(dataFolder + "/lena.png");
	
	try {
		// RGBA UBYTE IMAGE
		cvt::Image img;
		cvt::Image out, tmp;
		cvt::ImageIO::loadPNG(img, inputFile);
		
		out.reallocate( img.width(), img.height(), cvt::IFormat::floatEquivalent( img.format() ) );
		tmp.reallocate( out );
		img.convert( tmp );

		cvt::ROFDenoise rof;
		rof.apply( out, tmp, 0.05f, 5 );

		cvt::ImageIO::savePNG(out, "out.png");

		cvt::Image x( tmp );
		x.sub( out );
		x.mul( 1.5f );
		out.add( x );
		cvt::ImageIO::savePNG( out, "out2.png");
		
	} catch( cvt::Exception e ) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
