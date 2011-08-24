#include <cvt/cl/CLContext.h>
#include <cvt/cl/CLImage2D.h>

namespace cvt {
	/**
	  Create CLImage2D object with CLContext
	 */
	CLImage2D::CLImage2D( const CLContext& context, size_t width, size_t height, const CLImageFormat& format,
						  cl_mem_flags flags, size_t stride, void* host_ptr)
		: _width( width ), _height( height ), _format( format )
	{
		cl_int err;
		_object = ::clCreateImage2D( context, flags, ( cl_image_format* ) &format, width, height, stride, host_ptr, &err );
		if( err != CL_SUCCESS )
			throw CLException( err );
	}


	/**
	  Use default context to create CLImage2D object
	 */
	CLImage2D::CLImage2D( size_t width, size_t height, const CLImageFormat& format, cl_mem_flags flags )
		: _width( width ), _height( height ), _format( format )
	{
		cl_int err;
		_object = ::clCreateImage2D( *CL::defaultContext(), flags, ( cl_image_format* ) &format, width, height, 0, NULL, &err );
		if( err != CL_SUCCESS )
			throw CLException( err );
	}


	/**
	  Use default context to create CLImage2D from Image
	 */
/*	CLImage2D::CLImage2D( const Image& img )
		: _width( width ), _height( height ), _format( format )
	{
		//TODO
	}*/

	void* CLImage2D::map( size_t* stride )
	{
		 return CL::defaultQueue()->enqueueMapImage( *this, CL_MAP_READ | CL_MAP_WRITE, 0, 0, _width, _height, stride );
	}

	const void* CLImage2D::map( size_t* stride ) const
	{
		 return ( const void* ) CL::defaultQueue()->enqueueMapImage( *this, CL_MAP_READ, 0, 0, _width, _height, stride );
	}

	void CLImage2D::unmap( const void* ptr ) const
	{
		CL::defaultQueue()->enqueueUnmap( *( ( CLMemory* )this ), ptr );
	}
}
