//------------------------------------------------------------------------------
/**
 *	@file	itexturemap.h
 *	@author	Authors name
 *	@brief	Brief description of the file contents
 *
 *	Last change by:		$Author: pgregory $
 *	Last change date:	$Date: 2002/05/07 22:33:50 $
 */
//------------------------------------------------------------------------------


#ifndef	___itexturemap_Loaded___
#define	___itexturemap_Loaded___


#include	<valarray>

START_NAMESPACE( Aqsis )


//----------------------------------------------------------------------
/** \enum EqMapType
 * Enum defining the various image map types.
 */

enum	EqMapType
{
    MapType_Invalid = 0,

    MapType_Texture = 1,  		///< Plain texture map.
    MapType_Environment,  	///< Cube face environment map.
    MapType_Bump,  			///< Bump map (not used).
    MapType_Shadow,  			///< Shadow map.
    MapType_LatLong
};


/** \enum EqWrapMode
 * Enum defining the various modes of handling texture access outside of the normal range.
 */
enum	EqWrapMode
{
    WrapMode_Black = 0,  		///< Return black.
    WrapMode_Periodic,  		///< Wrap round to the opposite side.
    WrapMode_Clamp,  			///< Clamp to in range.
};


/** \enum EqTexFormat
 * Enum defining the possible storage types for image maps.
 */
enum EqTexFormat
{
    TexFormat_Plain = 0,  		///< Plain TIFF image.
    TexFormat_MIPMAP = 1,  		///< Aqsis MIPMAP format.
};




//----------------------------------------------------------------------
/** \struct IqTextureMap
 * Interface for access to texture map objects.
 */

struct IqTextureMap
{
	virtual	~IqTextureMap()	{}

	/** Get the horizontal resolution of this image.
	 */
	virtual TqUint	XRes() const = 0;
	/** Get the vertical resolution of this image.
	 */
	virtual TqUint	YRes() const = 0;
	/** Get the number of samples per pixel.
	 */
	virtual TqInt	SamplesPerPixel() const = 0;
	/** Get the storage format of this image.
	 */
	virtual	EqTexFormat	Format() const = 0;
	/** Get the image type.
	 */
	virtual	EqMapType	Type() const = 0;
	/** Open this image ready for reading.
	 */
	virtual	void	Open() = 0;
	/** Close this image file.
	 */
	virtual	void	Close() = 0;
	/** Determine if this image file is valid, i.e. has been found and opened successfully.
	 */
	virtual bool	IsValid() const = 0;

	virtual	void	SampleMap( TqFloat s1, TqFloat t1, TqFloat swidth, TqFloat twidth, TqFloat sblur, TqFloat tblur,
		                                std::valarray<TqFloat>& val ) = 0;
	virtual	void	SampleMap( TqFloat s1, TqFloat t1, TqFloat s2, TqFloat t2, TqFloat s3, TqFloat t3, TqFloat s4, TqFloat t4,
		                                TqFloat sblur, TqFloat tblur,
		                                std::valarray<TqFloat>& val ) = 0;
	virtual	void	SampleMap( CqVector3D& R, CqVector3D& swidth, CqVector3D& twidth, TqFloat sblur, TqFloat tblur,
		                                std::valarray<TqFloat>& val ) = 0;
	virtual	void	SampleMap( CqVector3D& R1, CqVector3D& R2, CqVector3D& R3, CqVector3D& R4,
		                                TqFloat sblur, TqFloat tblur,
		                                std::valarray<TqFloat>& val ) = 0;

};



//-----------------------------------------------------------------------

END_NAMESPACE( Aqsis )


#endif	//	___itexturemap_Loaded___
