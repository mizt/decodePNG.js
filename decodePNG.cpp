#import "emscripten.h"
#import "math.h"
#import "stdio.h"
#import "spng.h"

extern "C" {
	
	EMSCRIPTEN_KEEPALIVE int decodePNG(unsigned char *dst, int w, int h, unsigned char *bytes, int length) {
		spng_ctx *ctx = spng_ctx_new(0);
		spng_set_png_buffer(ctx,bytes,length);
		struct spng_ihdr ihdr;
		spng_get_ihdr(ctx,&ihdr);
		if(ihdr.width==w&&ihdr.height==h&&ihdr.bit_depth==8) {
			if(ihdr.color_type==SPNG_COLOR_TYPE_TRUECOLOR_ALPHA) {
				size_t out_size;
				spng_decoded_image_size(ctx,SPNG_FMT_RGBA8,&out_size);
				spng_decode_image(ctx,dst,out_size,SPNG_FMT_RGBA8,0);
				spng_ctx_free(ctx);
				return 1;
			}
		}
		spng_ctx_free(ctx);
		return 0;
	}
}