#include <stdlib.h>
#include <stdio.h>

#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"
#include "murmur3/murmur3.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return (0);
}

VCL_STRING
vmod_id(const struct vrt_ctx *ctx, VCL_STRING key, VCL_INT shards)
{
	char *p;
	unsigned u, v;
	uint32_t hash[4];
	uint32_t seed = 69;

	u = WS_Reserve(ctx->ws, 0); /* Reserve some work space */
	p = ctx->ws->f;		/* Front of workspace area */

	MurmurHash3_x64_128(key, strlen(key), seed, hash);
	v = snprintf(p, u, "%d", (int) (hash[0] % shards));
	v++;
	if (v > u) {
		/* No space, reset and leave */
		WS_Release(ctx->ws, 0);
		return (NULL);
	}

	/* Update work space with what we've used */
	WS_Release(ctx->ws, v);
	return (p);
}
