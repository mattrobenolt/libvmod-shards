#include <stdlib.h>
#include <string.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"
#include "murmur3/murmur3.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return (0);
}

const char *
vmod_id(struct sess *sp, const char *key, const int shards)
{
	char *p;
	unsigned u, v;
	uint32_t hash[4];
	uint32_t seed = 69;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	u = WS_Reserve(sp->wrk->ws, 0);  /* Reserve some work space */
	p = sp->wrk->ws->f;              /* Front of workspace area */

	MurmurHash3_x64_128(key, strlen(key), seed, hash);
	v = snprintf(p, u, "%d", hash[0] % shards);
	v++;
	if (v > u) {
		/* No space, reset and leave */
		WS_Release(sp->wrk->ws, 0);
		return (NULL);
	}
	WS_Release(sp->wrk->ws, v);
	return (p);
}
