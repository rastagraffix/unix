/*
 * Copyright (c) 1987, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if 0
#ifndef lint
static char sccsid[] = "@(#)print.c	8.3 (Berkeley) 4/2/94";
#endif
#endif

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: release/10.0.0/usr.bin/ctags/print.c 216370 2010-12-11 08:32:16Z joel $");

#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#include "atags.h"
#include "atags.h"

/*
 * inputline --
 *	get the line the token of interest occurred on,
 *	prepare it for printing.
 */
void
inputline(void)
{
	long	saveftell;
	int	c;
	int	cnt;
	char	*cp;

	saveftell = ftell(inf);
	(void)fseek(inf, lineftell, L_SET);
	/*
	 * do all processing here, so we don't step through the
	 * line more than once; means you don't call this routine
	 * unless you're sure you've got a keeper.
	 */
	for (cnt = 0, cp = lbuf; GETC(!=, EOF) && cnt < ENDLINE; ++cnt) {
		if (c == '\\') {		/* backslashes */
			if (cnt > ENDLINE - 2)
				break;
			*cp++ = '\\'; *cp++ = '\\';
			++cnt;
		}
#ifdef SEARCH
		else if (c == (int)searchar) {	/* search character */
			if (cnt > ENDLINE - 2)
				break;
			*cp++ = '\\'; *cp++ = c;
			++cnt;
		}
#endif
		else if (c == '\n') {	/* end of keep */
#ifdef SEARCH
			*cp++ = '$';		/* can find whole line */
#endif
			break;
		}
		else
			*cp++ = c;
	}
	*cp = EOS;
	(void)fseek(inf, saveftell, L_SET);
}

/*
 * put_entries --
 *	write out the tags
 */
void
put_entries(NODE *node)
{

#if 0
	fprintf(stderr, "*** NODE ***  %p [%p %p]\n", node, node->left, node->right);
#endif
	if (node->left)
		put_entries(node->left);
	if (vflag)
		printf("%s %s %d\n",
		    node->entry, node->file, (node->lno + 63) / 64);
	else
#ifdef SEARCH
		fprintf(outf, "%22s\t%22s:%d\t%c^%s%c\n",
		    node->entry, node->file, node->lno, searchar, node->pat, searchar);
#else
		fprintf(outf, "%22s\t%22s:%d\t%.20s\n",
		    node->entry, node->file, node->lno, node->pat);
#endif
	if (node->right)
		put_entries(node->right);
}
