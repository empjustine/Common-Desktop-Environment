/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $XConsortium: chresc.c /main/3 1995/11/01 18:41:33 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*         THIS IS PROPRIETARY SOURCE CODE LICENSED BY          *
*                          AT&T CORP.                          *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*                     All Rights Reserved                      *
*                                                              *
*           This software is licensed by AT&T Corp.            *
*       under the terms and conditions of the license in       *
*       http://www.research.att.com/orgs/ssr/book/reuse        *
*                                                              *
*               This software was created by the               *
*           Software Engineering Research Department           *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                     gsf@research.att.com                     *
*                                                              *
***************************************************************/

/* : : generated by proto : : */

#if !defined(__PROTO__)
#if defined(__STDC__) || defined(__cplusplus) || defined(_proto) || defined(c_plusplus)
#if defined(__cplusplus)
#define __MANGLE__	"C"
#else
#define __MANGLE__
#endif
#define __STDARG__
#define __PROTO__(x)	x
#define __OTORP__(x)
#define __PARAM__(n,o)	n
#if !defined(__STDC__) && !defined(__cplusplus)
#if !defined(c_plusplus)
#define const
#endif
#define signed
#define void		int
#define volatile
#define __V_		char
#else
#define __V_		void
#endif
#else
#define __PROTO__(x)	()
#define __OTORP__(x)	x
#define __PARAM__(n,o)	o
#define __MANGLE__
#define __V_		char
#define const
#define signed
#define void		int
#define volatile
#endif
#if defined(__cplusplus) || defined(c_plusplus)
#define __VARARG__	...
#else
#define __VARARG__
#endif
#if defined(__STDARG__)
#define __VA_START__(p,a)	va_start(p,a)
#else
#define __VA_START__(p,a)	va_start(p)
#endif
#endif
#include <ast.h>

int
chresc __PARAM__((const char* s, char** p), (s, p)) __OTORP__(const char* s; char** p;){
	const char*	q;
	int		c;

	switch (c = *s++)
	{
	case 0:
		s--;
		break;
	case '\\':
		switch (c = *s++)
		{
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			c -= '0';
			q = s + 2;
			while (s < q) switch (*s)
			{
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
				c = (c << 3) + *s++ - '0';
				break;
			default:
				q = s;
				break;
			}
			break;
		case 'a':
			c = '\007';
			break;
		case 'b':
			c = '\b';
			break;
		case 'f':
			c = '\f';
			break;
		case 'n':
			c = '\n';
			break;
		case 'r':
			c = '\r';
			break;
		case 's':
			c = ' ';
			break;
		case 't':
			c = '\t';
			break;
		case 'v':
			c = '\013';
			break;
		case 'x':
			c = 0;
			q = s;
			while (q) switch (*s)
			{
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
				c = (c << 4) + *s++ - 'a' + 10;
				break;
			case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
				c = (c << 4) + *s++ - 'A' + 10;
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				c = (c << 4) + *s++ - '0';
				break;
			default:
				q = 0;
				break;
			}
			break;
		case 'E':
			c = '\033';
			break;
		case 0:
			s--;
			break;
		}
		break;
	}
	if (p) *p = (char*)s;
	return(c);
}
