// teqser.cpp : Defines the entry point for the console application.
//

#include	<stdio.h>


#ifdef	AQSIS_SYSTEM_WIN32
#include	<conio.h>
#pragma warning (disable : 4100)
#endif // AQSIS_SYSTEM_WIN32

#include	"aqsis.h"
#include	"version.h"
#include	"argparse.h"
#include	"ri.h"

TqBool	g_version = TqFalse;
TqBool	g_help = TqFalse;
TqBool	g_envcube = TqFalse;
TqBool	g_envlatl = TqFalse;
TqBool	g_shadow = TqFalse;

ArgParse::apstring	g_swrap = "black";
ArgParse::apstring	g_twrap = "black";
ArgParse::apstring	g_wrap = "";
ArgParse::apstring g_filter = "box";
ArgParse::apstring g_resize = "up";
ArgParse::apfloat g_swidth = 1.0;
ArgParse::apfloat g_twidth = 1.0;
ArgParse::apfloat g_fov = 90.0;
ArgParse::apfloat g_width = -1.0;
ArgParse::apstring g_compress = "none";
ArgParse::apfloat g_quality = 70.0;
ArgParse::apfloat g_bake = 64.0;


void version( std::ostream& Stream )
{
#if defined(AQSIS_SYSTEM_WIN32) || defined(AQSIS_SYSTEM_MACOSX)
    Stream << "teqser version " << VERSION_STR << std::endl;
#else
    Stream << "teqser version " << VERSION << std::endl;
#endif
}


int main( int argc, const char** argv )
{
    ArgParse ap;
    RtFilterFunc filterfunc;

    ap.usageHeader( ArgParse::apstring( "Usage: " ) + argv[ 0 ] + " [options] outfile" );
    ap.argFlag( "help", "\aprint this help and exit", &g_help );
    ap.argFlag( "version", "\aprint version information and exit", &g_version );
    ap.argString( "compression", "=string\a[none|lzw|packbits|deflate]", &g_compress );
    ap.argFlag( "envcube", " px nx py ny pz nz\aproduce a cubeface environment map from 6 images.", &g_envcube );
    ap.argFlag( "envlatl", "\aproduce a latlong environment map from an image file.", &g_envlatl );
    ap.argFlag( "shadow", "\aproduce a shadow map from a z file.", &g_shadow );
    ap.argString( "swrap", "=string\as wrap [black|periodic|clamp]", &g_swrap );
    ap.argString( "smode", "=string\a(equivalent to swrap for BMRT compatibility)", &g_swrap );
    ap.argString( "twrap", "=string\at wrap [black|periodic|clamp]", &g_twrap );
    ap.argString( "tmode", "=string\a(equivalent to twrap for BMRT compatibility)", &g_swrap );
    ap.argString( "wrap", "=string\awrap s&t [black|periodic|clamp]", &g_wrap );
    ap.argString( "mode", "=string\as (equivalent to wrap for BMRT compatibility)", &g_swrap );
    ap.argString( "filter", "=string\a[box|bessel|catmull-rom|disk|gaussian|sinc|triangle]", &g_filter );
    ap.argFloat( "fov(envcube)", "=float\a[>=0.0f]", &g_fov );
    ap.argFloat( "swidth", "=float\as width [>0.0f]", &g_swidth );
    ap.argFloat( "twidth", "=float\at width [>0.0f]", &g_twidth );
    ap.argFloat( "width", "=float\awidth [>0,0f] set both swidth and twidth", &g_width );
    ap.argFloat( "quality", "=float\a[>=1.0f && <= 100.0f]", &g_quality );
    ap.argFloat( "bake", "=float\a[>=2.0f && <= 2048.0f]", &g_bake );
    ap.argString( "resize", "=string\a[up|down|round|up-|down-|round-]\n\aNot used, for BMRT compatibility only!", &g_resize );


    if ( argc > 1 && !ap.parse( argc - 1, argv + 1 ) )
    {
        std::cerr << ap.errmsg() << std::endl << ap.usagemsg();
        exit( 1 );
    }

    if ( g_version )
    {
        version( std::cout );
        exit( 0 );
    }

    if ( g_help || ap.leftovers().size() <= 1 )
    {
        std::cout << ap.usagemsg();
        exit( 0 );
    }

    if ( g_envcube && g_shadow )
    {
        std::cout << "Specify only one of envcube or shadow" << std::endl;
        exit( 1 );
    }


    /* find the pixel's filter function */
    filterfunc = RiBoxFilter;
    if ( g_filter == "box" )
        filterfunc = RiBoxFilter;
    else if ( g_filter == "sinc" )
        filterfunc = RiSincFilter;
    else if ( g_filter == "catmull-rom" )
        filterfunc = RiCatmullRomFilter;
    else if ( g_filter == "disk" )
        filterfunc = RiDiskFilter;
    else if ( g_filter == "bessel" )
        filterfunc = RiBesselFilter;
    else if ( g_filter == "triangle" )
        filterfunc = RiTriangleFilter;
    else if ( g_filter == "gaussian" )
        filterfunc = RiGaussianFilter;



    /* protect the s,t width */
    if ( g_swidth < 1.0 )
    {
        std::cerr << "g_swidth is smaller than 1.0." << " 1.0 will be used instead." << std::endl;
        g_swidth = 1.0;
    }
    if ( g_twidth < 1.0 )
    {
        std::cerr << "g_twidth is smaller than 1.0." << " 1.0 will be used instead." << std::endl;
        g_twidth = 1.0;
    }

    /* protect the s,t wrap mode */
    if ( !( ( g_swrap == "black" ) || ( g_swrap == "periodic" ) || ( g_swrap == "clamp" ) ) )
    {
        std::cerr << "Unknown s wrap mode: " << g_swrap << ". black will be used instead." << std::endl;
        g_swrap = "black";
    }
    if ( !( ( g_twrap == "black" ) || ( g_twrap == "periodic" ) || ( g_twrap == "clamp" ) ) )
    {
        std::cerr << "Unknown t wrap mode: " << g_twrap << ". black will be used instead." << std::endl;
        g_twrap = "black";
    }
    if ( !( ( g_wrap == "" ) || ( g_wrap == "black" ) || ( g_wrap == "periodic" ) || ( g_wrap == "clamp" ) ) )
    {
        std::cerr << "Unknown wrap mode: " << g_wrap << ". black will be used instead." << std::endl;
        g_wrap = "black";
    }
    
	/* If wrap is specified, it overrides both s and t */
	if( g_wrap != "" )
	{
		g_twrap = g_wrap;
		g_swrap = g_wrap;
	}
	
	/* Need to set both st width ? */
    if ( g_width > 0.0 )
    {
        g_twidth = g_swidth = g_width;
    }

    /* protect the compression mode */
    if ( !( ( g_compress == "deflate" ) ||
            ( g_compress == "lzw" ) ||
            ( g_compress == "none" ) ||
            ( g_compress == "packbits" )
          )
       )
    {
        std::cerr << "Unknown compression mode: " << g_compress << ". none." << std::endl;
        g_compress = "none";
    }

    /* protect the quality mode */
    if ( g_quality < 1.0f ) g_quality = 1.0;
    if ( g_quality > 100.0f ) g_quality = 100.0;

    /* protect the bake mode */
    if ( g_bake < 2.0f ) g_bake = 2.0;
    if ( g_bake > 2048.0f ) g_bake = 2048.0;

    char *compression = ( char * ) g_compress.c_str();
    float quality = ( float ) g_quality;


    RiBegin( "teqser" );

    if ( g_envcube )
    {
        if ( ap.leftovers().size() != 7 )
        {
            std::cerr << "Need 6 images for cubic environment map" << std::endl;
            return ( -1 );
        }

        printf( "CubeFace Environment %s %s %s %s %s %s ----> %s \n\t\"fov\"= %4.1f\n\t\"filter\"= %s \n\t\"swidth\"= %4.1f\n\t\"twidth\"= %4.1f\n\t\"compression\" = %s\n",
                ( char* ) ap.leftovers() [ 0 ].c_str(),
                ( char* ) ap.leftovers() [ 1 ].c_str(),
                ( char* ) ap.leftovers() [ 2 ].c_str(),
                ( char* ) ap.leftovers() [ 3 ].c_str(),
                ( char* ) ap.leftovers() [ 4 ].c_str(),
                ( char* ) ap.leftovers() [ 5 ].c_str(),
                ( char* ) ap.leftovers() [ 6 ].c_str(),
                g_fov,
                g_filter.c_str(),
                g_swidth,
                g_twidth,
                ( char* ) g_compress.c_str()
              );

        RiMakeCubeFaceEnvironment( ap.leftovers() [ 0 ].c_str(), ap.leftovers() [ 1 ].c_str(), ap.leftovers() [ 2 ].c_str(),
                                   ap.leftovers() [ 3 ].c_str(), ap.leftovers() [ 4 ].c_str(), ap.leftovers() [ 5 ].c_str(), ap.leftovers() [ 6 ].c_str(),
                                   g_fov,
                                   filterfunc, ( float ) g_swidth, ( float ) g_twidth, "compression", &compression, "quality", &quality, RI_NULL );
    }
    else if ( g_shadow )
    {
        printf( "Shadow %s ----> %s \n\t\"compression\" = %s\n",
                ( char* ) ap.leftovers() [ 0 ].c_str(),
                ( char* ) ap.leftovers() [ 1 ].c_str(),
                ( char* ) g_compress.c_str() );



        RiMakeShadow( ( char* ) ap.leftovers() [ 0 ].c_str(), ( char* ) ap.leftovers() [ 1 ].c_str(), ( float ) g_twidth, "compression", &compression, "quality", &quality, RI_NULL );
    }
    else if ( g_envlatl )
    {
        printf( "LatLong Environment %s ----> %s \n\t\"compression\" = %s \n",
                ( char* ) ap.leftovers() [ 0 ].c_str(),
                ( char* ) ap.leftovers() [ 1 ].c_str(),
                ( char* ) g_compress.c_str() );



        RiMakeLatLongEnvironment( ( char* ) ap.leftovers() [ 0 ].c_str(), ( char* ) ap.leftovers() [ 1 ].c_str(), filterfunc,
                                  ( float ) g_swidth, ( float ) g_twidth, "compression", &compression, "quality", &quality, RI_NULL );
    }
    else
    {

        printf( "Texture %s ----> %s \n\t\"swrap\"= %s \n\t\"twrap\"= %s \n\t\"filter\"= %s \n\t\"swidth\"= %4.1f\n\t\"twidth\"= %4.1f\n\t\"compression\" = %s\n",
                ( char* ) ap.leftovers() [ 0 ].c_str(),
                ( char* ) ap.leftovers() [ 1 ].c_str(),
                ( char* ) g_swrap.c_str(),
                ( char* ) g_twrap.c_str(),
                ( char* ) g_filter.c_str(),
                g_swidth,
                g_twidth,
                compression
              );


        if (strstr(ap.leftovers() [ 0 ].c_str(), ".bake"))
        {
            static char envbake[80];
            int bake = (int) g_bake;

            sprintf(envbake, "BAKE=%d", bake);
            putenv(envbake);
        }
        RiMakeTexture( ( char* ) ap.leftovers() [ 0 ].c_str(), ( char* ) ap.leftovers() [ 1 ].c_str(),
                       ( char* ) g_swrap.c_str(), ( char* ) g_twrap.c_str(), filterfunc,
                       ( float ) g_swidth, ( float ) g_twidth, "compression", &compression, "quality", &quality, RI_NULL );

    }

    RiEnd();

    return ( 0 );
}
