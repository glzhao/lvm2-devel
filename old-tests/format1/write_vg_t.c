/*
 * Copyright (C) 2001-2004 Sistina Software, Inc. All rights reserved.
 * Copyright (C) 2004 Red Hat, Inc. All rights reserved.
 *
 * This file is part of LVM2.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions
 * of the GNU General Public License v.2.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "log.h"
#include "format1.h"
#include "dbg_malloc.h"
#include "pool.h"
#include "pretty_print.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	struct io_space *ios;
	struct volume_group *vg;
	struct pool *mem;

	if (argc != 2) {
		fprintf(stderr, "usage: read_vg_t <vg_name>\n");
		exit(1);
	}

	init_log(stderr);
	init_debug(_LOG_INFO);

	if (!dev_cache_init()) {
		fprintf(stderr, "init of dev-cache failed\n");
		exit(1);
	}

	if (!dev_cache_add_dir("/dev/loop")) {
		fprintf(stderr, "couldn't add /dev to dir-cache\n");
		exit(1);
	}

	if (!(mem = pool_create(10 * 1024))) {
		fprintf(stderr, "couldn't create pool\n");
		exit(1);
	}

	ios = create_lvm1_format("/dev", mem, NULL);

	if (!ios) {
		fprintf(stderr, "failed to create io_space for format1\n");
		exit(1);
	}

	vg = ios->vg_read(ios, argv[1]);

	if (!vg) {
		fprintf(stderr, "couldn't read vg %s\n", argv[1]);
		exit(1);
	}

	if (!ios->vg_write(ios, vg)) {
		fprintf(stderr, "couldn't write vg\n");
		exit(1);
	}

	ios->destroy(ios);

	pool_destroy(mem);
	dev_cache_exit();
	dump_memory();
	fin_log();
	return 0;
}
