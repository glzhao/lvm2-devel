/*
 * Copyright (C) 2003-2004 Sistina Software, Inc. All rights reserved. 
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

#include "tools.h"

int dumpconfig(struct cmd_context *cmd, int argc, char **argv)
{
	const char *file = NULL;

	if (argc == 1)
		file = argv[0];

	if (argc > 1) {
		log_error("Please specify one file for output");
		return EINVALID_CMD_LINE;
	}

	if (!write_config_file(cmd->cft, file))
		return ECMD_FAILED;

	return ECMD_PROCESSED;
}
